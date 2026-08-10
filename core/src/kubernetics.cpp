#include "../../data/logs/enginelog_c++/commonlog.hpp"
#include "../../configs/config_manager.hpp"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <sstream>
#include "globalvar.h"
using namespace std;
using namespace boost::asio;
using namespace boost::asio::local;
void logHandle() {
	string p = __FILE__;
	string f = p.substr(p.find_last_of("/\\") + 1);
	createLog(f);
}
void getPods(){
	auto log = spdlog::get("logger");
	log->info("program started");
	try{
	    io_context io;
	    stream_protocol::socket client(io);
	    stream_protocol::endpoint0 ad(val["kubernetics"]["endpoint"].as<std::string>());
	    client.connect(ad);
	  	auto local = val["docker_client"]["host"].as<std::string>();
	  	string request = "GET /api/v1/pods HTTP/1.1\r\n"
	  	                 "Host: local\r\n"
	  	                 "Connection: close\r\n"
	  	                 "\r\n";
	    write(endpoint0, buffer(request));
	    vector<char> arr(5000);
	    auto response = endpoint0.read_some(buffer(arr));
	    string res(arr.begin(), arr.begin() + response);
	    cout<<"The kubernetics pod information";
	    cout << res;
	    log->info("Response recived from unix port for the specific id\n\n");
	}
}
