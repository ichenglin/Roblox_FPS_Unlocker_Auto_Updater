#include <iostream>
#include <fstream>
#include <zip.h>

void write_disk(const char* file_location, char* unzipped_content, zip_uint64_t unzipped_size);

void uncompress(std::string zip_location, std::string unzip_location, std::string file_name) {
	// open zip file
	int error = 0;
	zip* zip_content = zip_open(zip_location.c_str(), 0, &error);
	// search for file
	struct zip_stat zip_information;
	zip_stat_init(&zip_information);
	zip_stat(zip_content, file_name.c_str(), 0, &zip_information);
	// allocate memory for unzip content
	char* unzipped_content = new char[zip_information.size];
	// read zip file
	zip_file* zip_file = zip_fopen(zip_content, file_name.c_str(), 0);
	const int bytes_read = zip_fread(zip_file, unzipped_content, zip_information.size);
	zip_fclose(zip_file);
	// close zip file
	zip_close(zip_content);
	// write to disk
	write_disk(unzip_location.c_str(), unzipped_content, zip_information.size);
	// delete allocated memory
	delete[] unzipped_content;
}

void write_disk(const char* file_location, char* unzipped_content, zip_uint64_t unzipped_size) {
	std::ofstream disk_file(file_location, std::ofstream::binary);
	if (!disk_file.write(unzipped_content, unzipped_size)) {
		printf("An error has occured while writing to file");
	}
	disk_file.close();
}