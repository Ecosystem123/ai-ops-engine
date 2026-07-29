//commonlog.cpp
#include <iostream>
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include <string>
using namespace std;
void createLog(string f){
	string file = f+".txt";
	auto log = spdlog::basic_logger_mt("logger","data/logs/enginelog_c++/"+file);
	log->set_level(spdlog::level::trace);
    log->flush_on(spdlog::level::info);
}
