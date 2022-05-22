#pragma once
#include <iostream>
#include <zip.h>

void uncompress(std::string zip_location, std::string unzip_location, std::string file_name);
void write_disk(const char* file_location, char* unzipped_content, zip_uint64_t unzipped_size);