#include <iostream>
#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")

bool download(std::string source_url, std::string destination) {
	/* HRESULT S_OK="success" E_OUTOFMEMORY="out of memory" INET_E_DOWNLOAD_FAILURE="invalid url" */
	std::wstring source_url_wide = std::wstring(source_url.begin(), source_url.end());
	std::wstring destination_wide = std::wstring(destination.begin(), destination.end());
	LPCWSTR source_url_input = source_url_wide.c_str();
	LPCWSTR destination_input = destination_wide.c_str();
	HRESULT result = URLDownloadToFile(NULL, source_url_wide.c_str(), destination_wide.c_str(), 0, NULL);
	return result == S_OK;
}