//config_manager.cpp
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <filesystem>
using namespace std;
using namespace filesystem;
YAML::Node val;
void makeYaml(){
	path config = "configs/config_manager.yaml";;
	cout << __FILE__ << '\n';
	val = YAML::LoadFile(config.string());
}
