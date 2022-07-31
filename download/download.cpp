#include <iostream>
#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")

bool download(std::string source_url, std::string destination) {
	/* HRESULT S_OK="success" E_OUTOFMEMORY="out of memory" INET_E_DOWNLOAD_FAILURE="invalid url" */
	HRESULT result = URLDownloadToFile(NULL, source_url.c_str(), destination.c_str(), 0, NULL);
	return result == S_OK;
}