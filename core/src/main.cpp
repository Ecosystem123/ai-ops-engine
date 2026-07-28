//main.cpp
#include <iostream>
#include <spdlog/spdlog.h>
#include "../../data/logs/enginelog_c++/commonlog.hpp"
using namespace std;
void logHandle();
void getStatus();
void inspectContainer(string containerId);
void startContainer(string containerId);
void stopContainer(string containerId);
int main(){
	try{
		logHandle();
		//getStatus();
		//inspectContainer(d);
		cout<<"Enter the operation(startcontainer or stopcontainer)";
		string f1;
		cin>>f1;
		cout<<"Enter the id for docker: ";
		string d;
		cin>>d;
		if(f1 == "STARTCONTAINER" || f1 == "startcontainer"){
		   startContainer(d); 
		}
		else if(f1 == "STOPCONTAINER" || f1 == "stopcontainer"){
		  stopContainer(d);
		}
		else{
			cout<<"Invalid command";
		}
		
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
