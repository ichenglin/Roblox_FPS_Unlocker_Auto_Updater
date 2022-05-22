#include <iostream>
#include <curl/curl.h>

static size_t buffer_callback_function(void* contents, size_t size, size_t nmemb, void* userp);

std::string get_request(std::string source_url, std::string user_agent) {
	CURL* curl;
	CURLcode response;
	std::string read_buffer;
	curl = curl_easy_init();
	if (!curl) {
		return NULL;
	}
	curl_easy_setopt(curl, CURLOPT_URL, source_url.c_str());
	curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, buffer_callback_function);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
	response = curl_easy_perform(curl);
	if (response != CURLE_OK) {
		return NULL;
	}
	curl_easy_cleanup(curl);
	return read_buffer;
}

static size_t buffer_callback_function(void* contents, size_t size, size_t nmemb, void* userp) {
	// method header parameters directly copied from documentation
	// append incoming buffer chunk to string object
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}