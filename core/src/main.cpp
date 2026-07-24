//main.cpp
#include <iostream>
#include <spdlog/spdlog.h>
#include "../../data/logs/enginelog_c++/commonlog.hpp"
using namespace std;
void logHandle(){
	auto log = spdlog::get("logger");
	if (log)
	    cout << "FOUND\n";
	else
	    cout << "NOT FOUND\n";
	log->info("Program started");
	log->info("Working fine");
}
int main(){
   string  p = __FILE__;
   string f = p.substr(p.find_last_of("/\\")+1);
	try{
	    createLog(f);
		logHandle();
	}
	catch(const std::exception& e){
	    auto log = spdlog::get("logger");
		log->error(e.what());
	}
	spdlog::shutdown();
	return 0;
}
