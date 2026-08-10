//docker_client
#include <iostream>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <json/json.h>
#include <string>
#include <sstream>
#include "globalvar.h"
#include "../../data/logs/enginelog_c++/commonlog.hpp"
#include "../../configs/config_manager.hpp"
using namespace std;
using namespace boost::asio;
using namespace boost::asio::local;
void logHandle() {
	string p = __FILE__;
	string f = p.substr(p.find_last_of("/\\") + 1);
	createLog(f);
}

void getStatus() {
	auto log = spdlog::get("logger");
	log->info("program started");
	try {
		io_context io;
		stream_protocol::socket client(io);
		stream_protocol::endpoint ad(val["docker_client"]["docker_port_path"].as<std::string>());
		client.connect(ad); // Create a Unix socket endpoint named ad 
		auto local = val["docker_client"]["host"].as<std::string>();
		string request = "GET /containers/json HTTP/1.1\r\n"
		                 "Host: local\r\n"
		                 "Connection: close\r\n"
		                 "\r\n";
		write(client, buffer(request)); // buffer refers to the memory where data is stored.  
		vector<char> data(5000);
		auto res = client.read_some(buffer(data)); // number of bytes that were read.
		string response(data.begin(), data.begin() + res);  
		log->info("Response recived from unix port");
		string response1 = response.substr(response.find("["));
		cout << response1;
		Json::Value result1;
		Json::Reader r;
		r.parse(response1, result1);
		vector<pair<string, string>> table;
		for (int i = 0; i < result1.size(); i++) {
			for (string k : result1[i].getMemberNames()) {
				table.push_back({k, result1[i][k].toStyledString()});
			}
		}
		for (int i = 0; i < table.size(); i++) {
			cout << table[i].first << "\n";
			cout << table[i].second << "\n\n";
		}
	}
	catch (const std::exception& e) {
		log->error(e.what());
	}
}

void inspectContainer(string id) {
	auto log = spdlog::get("logger");
	log->info("inspector_container fn started working fine\n\n");
	try {
		io_context io;
		stream_protocol::socket endpoint1(io);
		stream_protocol::endpoint ad(val["docker_client"]["docker_port_path"].as<std::string>());
		endpoint1.connect(ad);
		auto local = val["docker_client"]["host"].as<std::string>();
		string r = "GET /containers/" + id + "/json HTTP/1.1\r\nHost: local\r\nConnection: close\r\n\r\n";
		write(endpoint1, buffer(r));
		vector<char> arr(5000);
		auto response = endpoint1.read_some(buffer(arr));
		string res(arr.begin(), arr.begin() + response);
		cout << res;
		log->info("Response recived from unix port for the specific id\n\n");
		string response1 = res.substr(res.find("{"));
		Json::Value result1;
		Json::Reader m;
		m.parse(response1, result1);
		Json::Value result(Json::arrayValue);
		result.append(result1);
		vector<pair<string, string>> array;
		for (int i = 0; i < result.size(); i++) {
			for (string k : result[i].getMemberNames()) {
				array.push_back({k, result[i][k].toStyledString()});
			}
		}
		for (int i = 0; i < array.size(); i++) {
			cout << array[i].first << "\n";
			cout << array[i].second << "\n\n";
		}
		log->info("parsing done successfully\n\n");
	}
	catch (const std::exception& e) {
		log->error(e.what());
	}
}

void startContainer(string id) {
	auto log = spdlog::get("logger");
	log->info("startContainer fn started working fine\n\n");
	try {
		io_context io;
		stream_protocol::socket endpoint2(io);
		stream_protocol::endpoint ad(val["docker_client"]["docker_port_path"].as<std::string>());
		endpoint2.connect(ad);
		auto local = val["docker_client"]["host"].as<std::string>();
		string r = "POST /containers/" + id + "/start HTTP/1.1\r\nHost: local\r\nConnection: close\r\n\r\n";
		write(endpoint2, buffer(r));
		vector<char> arr(5000);
		auto response = endpoint2.read_some(buffer(arr));
		string res(arr.begin(), arr.begin() + response);
		log->info("Response recived from unix port for the specific id\n\n");
		auto r1 = res.find('{');
		string res1 = res.substr(0, r1);
		cout << res1;
		istringstream val(res1);
		string res2;
		while (val >> res2) {
			if (res2 == "200") {
				cout << "status okay";
				break;
			}
			else if (res2 == "304" || res2 == "204") {
				if (res2 == "304") {
					cout << "Container is already running\n";
				} else {
					cout << "container started successfully\n";
				}
			}
			else if (res2 == "400") {
				cout << "status error";
			}
			else if (res2 == "500") {
				cout << "Internal server error";
			}
		}
	}
	catch (const std::exception& e) {
		log->error(e.what());
	}
}

void stopContainer(string id) {
	auto log = spdlog::get("logger");
	log->info("stopContainer fn started working fine \n\n");
	try {
		io_context io;
		stream_protocol::socket endpoint2(io);
		stream_protocol::endpoint ad(val["docker_client"]["docker_port_path"].as<std::string>());
		endpoint2.connect(ad);
		auto local = val["docker_client"]["host"].as<std::string>();
		string r = "POST /containers/" + id + "/stop HTTP/1.1\r\nHost: local\r\nConnection: close\r\n\r\n";
		write(endpoint2, buffer(r));
		vector<char> arr(5000);
		auto response = endpoint2.read_some(buffer(arr));
		string res(arr.begin(), arr.begin() + response);
		log->info("Response recived from unix port for the specific id \n\n");
		auto r1 = res.find('{');
		string res1 = res.substr(0, r1);
		cout << res1;
		istringstream val(res1);
		string res2;
		while (val >> res2) {
			if (res2 == "200") {
				cout << "status okay";
				break;
			}
			else if (res2 == "304" || res2 == "204") {
				cout << "Container stopped successfully\n";
			}
			else if (res2 == "400") {
				cout << "container not found";
			}
			else if (res2 == "500") {
				cout << "Internal server error";
			}
		}
	}
	catch (const std::exception& e) {
		log->error(e.what());
	}
}

void maintainConnection() {
	auto log = spdlog::get("logger");
	log->info("maintainConnection started working fine conenction. Connection will be open \n\n");
	stream_protocol::endpoint ad(val["docker_client"]["docker_port_path"].as<std::string>());
	endpoint3.connect(ad);
	auto local = val["docker_client"]["host"].as<std::string>();
	request = "GET /events HTTP/1.1\r\n"
	          "Host: local\r\n"
	          "Connection: keep-alive\r\n"
	          "\r\n";
	write(endpoint3, buffer(request));
	while(true){
		    vector<char> arr1(5000);
		    auto response1 = endpoint3.read_some(buffer(arr1));
			string res_str1(arr1.begin(), arr1.begin() + response1);
			log->info("Response recived from unix port \n\n");
			// Parse nested JSON objects by matching balanced depth of curly braces
			size_t i = 0;
			while (i < res_str1.size()) {
				if (res_str1[i] == '{') {
					size_t start = i;
					int depth = 0;
					for (; i < res_str1.size(); ++i) {
						if (res_str1[i] == '{') depth++;
						else if (res_str1[i] == '}') depth--;
						
						if (depth == 0) {
							string json_snippet = res_str1.substr(start, i - start + 1);
							Json::Value result1;
							Json::Reader m;
							if (m.parse(json_snippet, result1)) {
								Json::Value result(Json::arrayValue);
								result.append(result1);
								string action = result1["Action"].asString();
								if (action == "start" ||
								    action == "die" ||
								    action == "stop" ||
								    action == "destroy")
								{
								    log->info("Container event: {}", action);
								}
								
							}
							break;
						}
					}
				}
				i++;
			}

			
		}
			}
