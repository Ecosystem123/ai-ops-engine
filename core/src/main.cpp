//main.cpp
#include <iostream>
#include <spdlog/spdlog.h>
#include "../../data/logs/enginelog_c++/commonlog.hpp"
using namespace std;
void logHandle();
void getStatus();
void inspectContainer(string containerId);
int main(){
	try{
		logHandle();
		getStatus();
		cout<<"Enter the id for docker: ";
		string d;
		cin>>d;
		inspectContainer(d);
	}
	catch(const std::exception& e){
	    string  p = __FILE__;
	    string f = p.substr(p.find_last_of("/\\")+1);
	    createLog(f);
	    auto log = spdlog::get("logger");
		log->error(e.what());
	}
	spdlog::shutdown();
	return 0;
}
