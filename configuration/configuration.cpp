#include <iostream>
#include <fstream>
#include "configuration.h"

Configuration::Configuration(std::string configuration_path) {
	this->configuration_path = configuration_path;
}

nlohmann::json Configuration::get_configuration() {
	std::string file_content, line_content;
	std::ifstream disk_file(this->configuration_path);
	if (!disk_file) {
		printf("An error has occured while accessing to configuration.");
	}
	while (std::getline(disk_file, line_content)) {
		file_content.append(line_content);
	}
	disk_file.close();
	return nlohmann::json::parse(file_content);
}

void Configuration::set_configuration(nlohmann::json configuration) {
	std::string json_stringified = configuration.dump();
	std::ofstream disk_file(this->configuration_path);
	if (!disk_file.write(json_stringified.c_str(), json_stringified.size())) {
		printf("An error has occured while writing to configuration.");
	}
	disk_file.close();
}

bool Configuration::has_configuration() {
	std::ifstream disk_file(this->configuration_path);
	return disk_file.good();
}