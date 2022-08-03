#include <iostream>
#include <vector>
#include "utilities.h"

std::vector<std::string> Utilities::split_string(std::string string, std::string delimiter) {
	int string_begin = 0;
	std::vector<std::string> string_components;
	while (true) {
		int string_end = string.find(delimiter, string_begin);
		// exit if nothing matches
		if (string_end == std::string::npos) {
			break;
		}
		std::string component = string.substr(string_begin, string_end - string_begin);
		string_components.push_back(component);
		string_begin = string_end + delimiter.length();
	}
	string_components.push_back(string.substr(string_begin));
	return string_components;
}

std::string Utilities::join_string(std::vector<std::string> strings, std::string separator) {
	if (strings.size() <= 0) {
		return "";
	}
	std::string joined_string = strings[0];
	for (int string_index = 1; string_index < strings.size(); string_index++) {
		joined_string += separator + strings[string_index];
	}
	return joined_string;
}

std::vector<std::string> Utilities::slice_vector(std::vector<std::string> vector, int begin, int end) {
	auto vector_begin = vector.begin() + begin;
	auto vector_end = vector.begin() + end + 1;
	std::vector<std::string> slice_result(end - begin + 1);
	std::copy(vector_begin, vector_end, slice_result.begin());
	return slice_result;
}

void Utilities::print_list(std::vector<std::string> string_list) {
	for (std::string element : string_list) {
		std::cout << element << std::endl;
	}
}