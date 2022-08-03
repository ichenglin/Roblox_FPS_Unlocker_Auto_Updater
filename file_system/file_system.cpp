#include <iostream>
#include <filesystem>
#include <vector>
#include "file_system.h"
#include "../utilities/utilities.h"

std::vector<std::string> directory_split(std::string path);

void FileSystem::directory_create(std::string path) {
	std::vector<std::string> path_components = directory_split(path);
	for (int component_index = 0; component_index < path_components.size(); component_index++) {
		std::vector<std::string> parent_path_components = Utilities::slice_vector(path_components, 0, component_index);
		std::string parent_path = Utilities::join_string(parent_path_components, "\\");
		bool parent_path_exist = FileSystem::directory_exist(parent_path);
		if (!parent_path_exist) {
			std::filesystem::create_directory(parent_path);
		}
	}
}

bool FileSystem::directory_exist(std::string path) {
	return std::filesystem::exists(path);
}

std::vector<std::string> directory_split(std::string path) {
	return Utilities::split_string(path, "\\");
}