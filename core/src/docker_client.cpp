//docker_client
#include <iostream>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <json/json.h>
#include <string>
#include "../../data/logs/enginelog_c++/commonlog.hpp"
using namespace std;
using namespace boost::asio;
using namespace boost::asio::local;
void logHandle() {
	string  p = __FILE__;
	string f = p.substr(p.find_last_of("/\\")+1);
	createLog(f);
}
void getStatus(){
    auto log = spdlog::get("logger");
    log->info("program started");
    try{
     io_context io;
     stream_protocol::socket client(io);
     stream_protocol::endpoint ad("/var/run/docker.sock");
     client.connect(ad);
     string request ="GET /containers/json HTTP/1.1\r\n"
                      "Host: localhost\r\n"
                      "Connection: close\r\n"
                      "\r\n";
     write(client,buffer(request));      
     vector<char> data(5000);
     auto res = client.read_some(buffer(data));	
     string response(data.begin(),data.begin()+res);
     log->info("Response recived from unix port");
     string response1 = response.substr(response.find("["));
     cout<<response1;
     Json::Value result1;
     Json::Reader r;
     r.parse(response1,result1);
     vector<pair<string,string>> table;
     for(int i=0;i<result1.size();i++){
     	for(string k:result1[i].getMemberNames()){
     	  table.push_back({k,result1[i][k].toStyledString()});
     	}
     }
     for(int i=0;i<table.size();i++){
     	cout << table[i].first << "\n";
     	cout << table[i].second << "\n\n";
     }
    }
    catch(const std::exception& e){
     log->error(e.what());
    }
}
