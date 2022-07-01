#pragma once
#include <iostream>
#include <nlohmann/json.hpp>

class Configuration {

private:
	std::string configuration_path;

public:
	Configuration(std::string configuration_path);
	nlohmann::json get_configuration();
	void set_configuration(nlohmann::json configuration);
	bool has_configuration();
};