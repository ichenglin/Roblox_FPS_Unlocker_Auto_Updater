#pragma once
#include <iostream>
#include <vector>

class Utilities {

public:
	static std::vector<std::string> split_string(std::string string, std::string delimiter);
	static std::string join_string(std::vector<std::string> strings, std::string separator);
	static std::vector<std::string> slice_vector(std::vector<std::string> vector, int begin, int end);
	static void print_list(std::vector<std::string> string_list);

};