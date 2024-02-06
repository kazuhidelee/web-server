# Web Server for Office Hour Queue
Created a web server for an office hours queue.
Made a REST API that reads requests from stdin and writes responses to stout. 
Requests and responses are formatted using a simplified subset of real HTTP
<img width="653" alt="Screenshot 2024-02-06 at 12 17 24 AM" src="https://github.com/kazuhidelee/web-server/assets/122251831/727e7e29-f1c6-4624-b542-46ffdf2df397">

## Process
The client’s web browser sends an HTTP request to the server. The request might look like this:
<img width="434" alt="Screenshot 2024-02-06 at 12 13 26 AM" src="https://github.com/kazuhidelee/web-server/assets/122251831/fc553007-4b77-4799-b7e9-e9b3753c5b7d">
Next, the server receives the request sent by the client. The server acts on the request.
1. Deserialize the JSON data, converting it into a data structure
2. Modify an internal data structure - list
3. Create a response data structure
4. Serialize the response data structure, converting it to JSON
5. Send the response to the client
The example response:
<img width="608" alt="Screenshot 2024-02-06 at 12 14 38 AM" src="https://github.com/kazuhidelee/web-server/assets/122251831/2a2feb62-9312-4783-a17a-4d5190e8b728">
Fianlly, the client receives the response and updates the web page, showing the up-to-date queue.

## Usage
```make test-api ```
<br>
``` make api.exe ```
<br>
``` python3 server.py ```

## What I Learned
- Linked Lists
- Web app Back-end
- API
- JSON files
