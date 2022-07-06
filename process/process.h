#pragma once
#include <iostream>
#include <vector>
#include <windows.h>

class Process {

public:
	static std::vector<HANDLE> get_process_by_name(std::string process_name);

};