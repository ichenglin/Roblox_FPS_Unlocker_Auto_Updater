#pragma once
#include <iostream>

class FileSystem {

public:
	static void directory_create(std::string path);
	static bool directory_exist(std::string path);

};