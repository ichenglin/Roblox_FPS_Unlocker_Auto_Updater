#pragma once
#include <iostream>

std::string get_request(std::string source_url, std::string user_agent);
static size_t buffer_callback_function(void* contents, size_t size, size_t nmemb, void* userp);