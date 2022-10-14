#pragma comment(lib,"ws2_32.lib")

#include <iostream>
#include <thread>
#include <map>
#include "rapidjson/document.h"

#include "MySocket.h"
using namespace std;

struct GameObject
{
	string name;
	float x, y;
};

void func1() {
	cout << test << endl;
	MySocket s;
	s.Init();
	s.Connect();
	while (true) {
		std::string data = s.Recv();
		std::cout << data << std::endl;
		rapidjson::Document doc;
		doc.Parse(data.c_str());
		if (doc.HasParseError())
		{
			std::cout << "json data parsing failed";
		}

		// C++ 11 이상 문법
		for (auto& v : doc.GetArray())
		{
			GameObject tem;
			tem.name = v["name"].GetString();
			tem.x = v["pos"][0].GetFloat();
			tem.y = v["pos"][1].GetFloat();
		}
	}
}

int main()
{
	std::thread t1(func1);
	t1.join();

	return 0;
}