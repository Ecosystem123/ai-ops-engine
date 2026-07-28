//docker_client
#include <iostream>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <json/json.h>
#include <string.h>
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
     client.connect(ad); //Create a Unix socket endpoint named ad 
     string request ="GET /containers/json HTTP/1.1\r\n"
                      "Host: localhost\r\n"
                      "Connection: close\r\n"
                      "\r\n";
     write(client,buffer(request)); // buffer refers to the memory where data is stored.  
     vector<char> data(5000);
     auto res = client.read_some(buffer(data));	//number of bytes that were read.
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
void inspectContainer(string id){
  auto log = spdlog::get("logger");
  log->info("inspector_container fn started working fine");
  try{
  	io_context io;
  	stream_protocol::socket endpoint1(io);
  	stream_protocol::endpoint ad("/var/run/docker.sock");
  	endpoint1.connect(ad);
  	string r = "GET /containers/"+id+"/json HTTP/1.1\r\n" "Host: localhost\r\n" "Connection: close\r\n" "\r\n";
  	write(endpoint1,buffer(r));
  	vector<char> arr(5000);
  	auto response = endpoint1.read_some(buffer(arr));
  	string res(arr.begin(),arr.begin()+response);
  	cout<<res;
  	log->info("Response recived from unix port for the specific id");
  	string response1 = res.substr(res.find("{"));
  	Json::Value result1;
  	Json::Reader m;
  	m.parse(response1,result1);
  	Json::Value result(Json::arrayValue);
  	result.append(result1);
  	vector<pair<string,string>> array;
  	for(int i=0;i<result.size();i++){
     	for(string k:result[i].getMemberNames()){
     	  array.push_back({k,result[i][k].toStyledString()});
     	}
     }
    for(int i=0;i<array.size();i++){
     	cout << array[i].first << "\n";
     	cout << array[i].second << "\n\n";
     }
    log->info("parsing done successfully");
    }
  catch(const std::exception& e){
     log->error(e.what());
    }
  	
  }
	
