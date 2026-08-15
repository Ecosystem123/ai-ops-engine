#include "../../data/logs/enginelog_c++/commonlog.hpp"
#include "../../configs/config_manager.hpp"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <spdlog/spdlog.h>
#include <json/json.h>
#include <sstream>
using namespace std;
using namespace boost::asio;
using namespace boost::asio::local;
using boost::asio::ip::tcp;
void logHandle1() {
	string p = __FILE__;
	string f = p.substr(p.find_last_of("/\\") + 1);
	createLog(f);
}
void getPods(){
  auto log = spdlog::get("logger");
  log->info("program started");
  try{
      io_context io;
      tcp::resolver resolver(io);
      auto endpoint = resolver.resolve("192.168.49.2","8443");
      ssl::context ctx(ssl::context::tls_client);
        ctx.use_certificate_chain_file("/home/abhinandps/.minikube/profiles/minikube/client.crt");
        ctx.use_private_key_file("/home/abhinandps/.minikube/profiles/minikube/client.key",ssl::context::pem);
      ssl::stream<ip::tcp::socket> ssock(io,ctx);
      connect(ssock.lowest_layer(),endpoint);
      ssock.handshake(ssl::stream_base::handshake_type::client);
    	auto local = val["docker_client"]["host"].as<std::string>();
    	string request = "GET /api/v1/pods HTTP/1.0\r\n"
    	                 "Host: local\r\n"
    	                 "Connection: close\r\n"
    	                 "\r\n";
      write(ssock, buffer(request));
      vector<char> arr(50000);
      string res;
      while(true){
       boost::system::error_code ec;
       auto response = read(ssock,buffer(arr),ec);
       res.append(arr.begin(), arr.begin() + response);
       if(ec == boost::asio::error::eof){
       	break;
       }	
      }
      log->info("Response recived from unix port for the specific id\n\n");
      string response1 = res.substr(res.find("{"));
    	Json::Value result1;
    	Json::Reader m;
    	m.parse(response1, result1);
    	Json::Value result(Json::arrayValue);
    	result.append(result1);
    	vector<pair<string, string>> table;
    	cout<<"\n\n============================================\n";
    	cout<<"\n The pod details are \n";
    	cout<<"\n =============================================\n\n";
    	for (int i = 0; i < result.size(); i++) {
    			for (string k : result[i].getMemberNames()) {
    				table.push_back({k, result[i][k].toStyledString()});
    			}
    		}
    		for (int i = 0; i < table.size(); i++) {
    			cout << table[i].first << ":\n";
    			cout << table[i].second << "\n\n";
    		}
    	log->info("parsing done successfully\n\n");
    	log->info("Pods details successfully extracted\n");
    }
    catch (const std::exception& e) {
    	log->error(e.what());
    }
}
