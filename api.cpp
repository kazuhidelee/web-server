#include <iostream>
#include <list>
#include "json.hpp"
using namespace std;
using nlohmann::json;

struct Student
{
	string uniqname;
	string location;
	Student(const string &uniqname_in, const string &location_in)
		: uniqname(uniqname_in), location(location_in) {}
};

class OHQueue
{
public:
	void run()
	{
		while (cin >> request_type >> route)
		{
			read_request();
			if (request_type == "GET")
			{
				if (route == "/api/queue/head/")
				{
					read_first();
				}
				else if (route == "/api/queue/")
				{
					read_positions();
				}
				else if (route == "/api/")
				{
					read_queue();
				}
				else
				{
					bad_request();
				}
			}
			else if (request_type == "POST")
			{
				post_queue();
			}
			else if (request_type == "DELETE")
			{
				delete_queue();
			}
			else
			{
				bad_request();
			}
		}
	}

private:
	std::list<Student> queue;
	string request_type;
	string route;

	void read_request()
	{
		string trash;
		// cin >> request_type >> route;
		int i = 0;
		while (i <= 7)
		{
			cin >> trash;
			i++;
		}
	}
	// GET /api/
	void read_queue()
	{
		json j_out = {
			{"queue_head_url", "http://localhost/queue/head/"},
			{"queue_list_url", "http://localhost/queue/"},
			{"queue_tail_url", "http://localhost/queue/tail/"}};
		string str_out = j_out.dump(4) + "\n";
		cout << "HTTP/1.1 200 OK" << endl;
		cout << "Content-Type: application/json; charset=utf-8" << endl;
		cout << "Content-Length: " << str_out.length()
			 << "\n"
			 << endl;
		cout << str_out;
	}

	// GET /api/queue/
	void read_positions()
	{
		json j_out1;
		json j_out2;
		std::list<Student>::iterator i;
		int pos = 1;
		for (i = queue.begin(); i != queue.end(); ++i)
		{
			json temp = {
				{"location", i->location},
				{"position", pos},
				{"uniqname", i->uniqname},
			};
			j_out2.push_back(temp);
			pos++;
		}

		j_out1 = {{"count", queue.size()}, {"results", j_out2}};

		// Need fix: print out count and results
		string str_out = j_out1.dump(4) + "\n";
		cout << "HTTP/1.1 200 OK" << endl;
		cout << "Content-Type: application/json; charset=utf-8" << endl;
		cout << "Content-Length: " << str_out.length()
			 << "\n"
			 << endl;
		cout << str_out;
	}

	// GET /api/queue/head/
	void read_first()
	{
		json j_out;
		std::list<Student>::iterator i = queue.begin();
		json temp = {
			{"location", i->location},
			{"position", 1},
			{"uniqname", i->uniqname},
		};
		j_out = temp;

		string str_out = j_out.dump(4) + "\n";
		cout << "HTTP/1.1 200 OK" << endl;
		cout << "Content-Type: application/json; charset=utf-8" << endl;
		cout << "Content-Length: " << str_out.length()
			 << "\n"
			 << endl;
		cout << str_out;
	}

	// POST /api/queue/tail/
	void post_queue()
	{
		json j3;
		cin >> j3;
		struct Student s1 = {j3["uniqname"], j3["location"]};
		int pos = queue.size() + 1;
		queue.push_back(s1);

		json j_out;
		json temp = {
			{"location", queue.back().location},
			{"position", pos},
			{"uniqname", queue.back().uniqname},
		};
		j_out = temp;

		string str_out = j_out.dump(4) + "\n";
		cout << "HTTP/1.1 201 Created" << endl;
		cout << "Content-Type: application/json; charset=utf-8" << endl;
		cout << "Content-Length: " << str_out.length()
			 << "\n"
			 << endl;
		cout << str_out;
	}

	// DELETE /api/queue/head/
	void delete_queue()
	{
		queue.pop_front();

		cout << "HTTP/1.1 204 No Content" << endl;
		cout << "Content-Type: application/json; charset=utf-8" << endl;
		cout << "Content-Length: 0"
			 << "\n"
			 << endl;
	}

	// Bad Request
	void bad_request()
	{
		cout << "HTTP/1.1 400 Bad Request" << endl;
		cout << "Content-Type: application/json; charset=utf-8" << endl;
		cout << "Content-Length: 0"
			 << "\n"
			 << endl;
	}
};

int main()
{
	OHQueue ohqueue;
	ohqueue.run();
}