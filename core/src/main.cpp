//main.cpp
#include <bits/stdc++.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include "../../data/logs/enginelog_c++/commonlog.hpp"
#include "../../configs/config_manager.hpp"
#include "../files/global.hpp"
using namespace std;
void logHandle();
void getStatus();
void inspectContainer(string containerId);
void startContainer(string containerId);
void stopContainer(string containerId);
void maintainConnection();
int main(){
    makeYaml();
    logHandle();
   	thread t(maintainConnection);
	try{
		 cout<<"\n Enter the id for docker: ";
		 string d;
		 cin>>d;
		while(true){
			cout<<"\n Enter the choice \n 1.startcontainer \n 2.stopcontainer \n 3.inspectcontainer \n 4.get status \n";
			int ch;
			cin>>ch;
			switch(ch){
				case 1:
				  startContainer(d);
				  addFile(false);
				  break;
				case 2:
				  stopContainer(d);
				  addFile(false);
				  break;
				case 3:
				  inspectContainer(d);
				  addFile(false);
				  break;
				case 4:
				  getStatus();
				  addFile(false);
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
