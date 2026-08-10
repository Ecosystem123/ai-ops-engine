//main.cpp
#include <bits/stdc++.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include "../../data/logs/enginelog_c++/commonlog.hpp"
#include "../../configs/config_manager.hpp"
using namespace std;
void logHandle();
void getStatus();
void inspectContainer(string containerId);
void startContainer(string containerId);
void stopContainer(string containerId);
void maintainConnection();
void getPods();
int main(){
    makeYaml();
    logHandle();
   	thread t(maintainConnection);
	try{
		 cout<<"Enter the id for docker: ";
		 string d;
		 cin>>d;
		while(true){
			cout<<"Enter the choice \n 1.startcontainer \n 2.stopcontainer \n 3.inspectcontainer \n 4.get status \n 5.get kubernetic pod details \n";
			int ch;
			cin>>ch;
			switch(ch){
				case 1:
				  startContainer(d);
				  break;
				case 2:
				  stopContainer(d);
				  break;
				case 3:
				  inspectContainer(d);
				  break;
				case 4:
				  getStatus();
				  break;
				case 5:
				  getPods();
				  break;
				default:
				  cout<<"invalid choice";
				  break;		
		}	
	}
	}
	catch(const std::exception& e){
	    string  p = __FILE__;
	    string f = p.substr(p.find_last_of("/\\")+1);
	    createLog(f);
	    auto log = spdlog::get("logger");
		log->error(e.what());
	}
	t.join();
	return 0;
}
