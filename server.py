"""
Simple HTTP server proxies API requests to a running subprocess, communicating
via stdin and stdout.  Requests to non-API routes are served as static files.
"""

import http.server
import subprocess


# Server hostname and port
HOST = "localhost"
PORT = 8000

# Base URL for the API.  All API calls must start with this path.
API_ROOT = "/api"

# Executable that handles API calls.
API_EXE = "./api.exe"


class APIRequestHandler(http.server.SimpleHTTPRequestHandler):
    """
    Python docs
    https://docs.python.org/3.6/library/http.server.html#http.server.SimpleHTTPRequestHandler
    https://docs.python.org/3.6/library/http.server.html?highlight=httprequest#http.server.BaseHTTPRequestHandler
    """

    # Background process is a class variable (like a static member variable in
    # C++ because all instances should share the same subprocess.  Otherwise,
    # the process's datastructures would be "reset" with every request.
    process = None

    def __init__(self, *args, **kwargs):
        """Start the background process that will handle proxied requests."""
        if APIRequestHandler.process is None:
            print("Starting background process {}".format(API_EXE))
            APIRequestHandler.process = subprocess.Popen(
                [API_EXE],
                bufsize=1,
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
            )
        super().__init__(*args, **kwargs)

    def do_GET(self):
        """Handle an HTTP GET request.

        GET requests to API_ROOT are proxied to process stdin.  GET requests to
        all other paths are served as static files.
        """
        if self.path.startswith(API_ROOT):
            # Proxy to process
            self.proxy()
        else:
            # Serve static file
            super().do_GET()

    def do_POST(self):
        """Handle an HTTP POST request by proxying to process stdin."""
        self.proxy()

    def do_DELETE(self):
        """Handle an HTTP DELETE request by proxying to process stdin."""
        self.proxy()

    def proxy(self):
        """Proxy one request to process and proxy one response from process."""
        if not self.path.startswith(API_ROOT):
            self.send_error(
                http.HTTPStatus.METHOD_NOT_ALLOWED,
                "Method not allowed on this path: {}".format(self.path),
            )
            return
        self.proxy_request()
        self.proxy_response()

    def proxy_request(self):
        """Proxy a request from HTTP client to process."""

        # Read body of request from HTTP client
        content_length = int(self.headers.get('content-length', 0))
        host = self.headers.get('host', 'localhost')
        data = self.rfile.read(content_length).decode('utf-8')

        # Remove leading and trailing whitespace from data
        data = data.strip()

        # Build request string, example:
        #
        # GET /api/queue/ HTTP/1.1
        # Host: localhost
        request_str = (
            "{method} {path} {version}\n"
            "Host: {host}\n"
            "Content-Type: application/json; charset=utf-8\n"
            "Content-Length: {content_length}\n"
        ).format(
            method=self.command,
            path=self.path,
            version=self.request_version,
            host=host,
            content_length=len(data),
        )

        # Add data, if any
        if data:
            request_str += "\n"
            request_str += data
            request_str += "\n"

        # Write request to stdin of subprocess
        for line in request_str.split("\n"):
            print("< {}".format(line.strip()))
        APIRequestHandler.process.stdin.write(bytes(str(request_str), 'utf-8'))
        APIRequestHandler.process.stdin.flush()

    def proxy_response(self):
        """Proxy a response from process to HTTP client."""

        # Consume whitespace
        while APIRequestHandler.process.stdout.peek(1).isspace():
            APIRequestHandler.process.stdout.read(1)

        # Parse HTTP Response
        response = BytesHTTPResponse(APIRequestHandler.process.stdout)
        response.begin()
        data = response.read()

        # Print response to debug output
        assert response.version == 11
        print("> HTTP/1.1 {} {}".format(response.status, response.reason))
        print("> Content-Type: {}".format(response.getheader("Content-Type")))
        print("> Content-Length: {}".format(response.getheader("Content-Length")))
        print(">")
        for line in data.decode("utf8").split("\n"):
            print("> {}".format(line.rstrip()))

        # Write response to HTTP client
        self.send_response(response.status)
        self.send_header('Content-type', 'application/json')
        self.end_headers()
        self.wfile.write(data)


class BytesHTTPResponse(http.client.HTTPResponse):
    """Parse an HTTP response from a byte string.

    EXAMPLE:
    response = BytesHTTPResponse(b'''HTTP/1.1 200 OK
    Content-Type: application/json; charset=utf-8
    Content-Length: 161

    {
        "queue_head_url": "http://localhost/queue/head/",
        "queue_list_url": "http://localhost/queue/",
        "queue_tail_url": "http://localhost/queue/tail/"
    }

    ''')
    response.begin())
    print(response.version)
    print(response.status)
    print(response.reason)
    print(response.getheaders())
    print(response.read())
    """

    def __init__(self, response_bytes):
        """Create an HTTP Response using a fake underlying socket."""

        class FakeSocket():
            """Adapt stream of bytes interface to Socket interface."""
            def __init__(self, response_bytes):
                self._file = response_bytes

            def makefile(self, *args, **kwargs):
                return self._file

        # Create a data stream from a byte string.  This data stream will act
        # like a socket via the FakeSocket object.
        sock = FakeSocket(response_bytes)

        # Let super class do the hard work
        super().__init__(sock)

    def _close_conn(self):
        """Never close the connection (does nothing)."""


def main():
    """Start a server."""
    print("Starting server on {}:{}".format(HOST, PORT))
    server = http.server.HTTPServer((HOST, PORT), APIRequestHandler)
    server.serve_forever()


if __name__ == "__main__":
    main()
