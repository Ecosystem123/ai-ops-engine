#include<iostream>
#include <spdlog/spdlog.h>
#include "../../data/logs/enginelog_c++/commonlog.hpp"
#include "../../configs/config_manager.hpp"
#include "../files/global.hpp"
using namespace std;
void logHandle1();
void getPods();
int main(){
    makeYaml();
	logHandle1();
	try{
		cout<<"kubernetics details: ";
		getPods();
	}
	catch(const std::exception& e){
		    string  p = __FILE__;
		    string f = p.substr(p.find_last_of("/\\")+1);
		    createLog(f);
		    auto log = spdlog::get("logger");
			log->error(e.what());
	}
    addFile(true);
}
