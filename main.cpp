#include <iostream>
#include <windows.h>
#include <nlohmann/json.hpp>
#include "configuration.h"
#include "get_request.h"
#include "download.h"
#include "uncompress.h"

std::string get_latest_version();
nlohmann::json get_default_configuration(std::string latest_version);
void launch_fps_unlocker();

int main() {
	std::string latest_version = get_latest_version();
	nlohmann::json configuration;
	bool install_update;
	printf("Found latest version: %s\n", latest_version.c_str());
	// load configuration
	Configuration configuration_file = Configuration("configuration.json");
	if (configuration_file.has_configuration()) {
		// configuration exist, load configuration
		printf("Loaded configuration file.\n");
		configuration = configuration_file.get_configuration();
		install_update = configuration["installed_version"] != latest_version;
	} else {
		// configuration file not exist, create new
		printf("Configuration file not found, generated a new configuration file.\n");
		configuration = get_default_configuration(latest_version);
		configuration_file.set_configuration(configuration);
		install_update = true;
	}
	// install update if available
	if (install_update) {
		printf("New version available, downloading from source...\n");
		std::string update_source = "https://github.com/axstin/rbxfpsunlocker/releases/download/" + latest_version + "/rbxfpsunlocker-x64.zip";
		download(update_source, "rbxfpsunlocker.zip");
		uncompress("rbxfpsunlocker.zip", "rbxfpsunlocker.exe", "rbxfpsunlocker.exe");
		printf("Download completed.\n");
	} else {
		printf("Latest version installed.\n");
	}
	launch_fps_unlocker();
	return 0;
}

std::string get_latest_version() {
	// json from github api
	std::string version_raw = get_request("https://api.github.com/repos/axstin/rbxfpsunlocker/releases/latest", "Mozilla/5.0");
	nlohmann::json version_json = nlohmann::json::parse(version_raw);
	return version_json["tag_name"];
}

nlohmann::json get_default_configuration(std::string latest_version) {
	nlohmann::json default_configuration;
	default_configuration["installed_version"] = latest_version;
	return default_configuration;
}

void launch_fps_unlocker() {
	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	if (CreateProcess(TEXT("rbxfpsunlocker.exe"), NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		// don't wait for rbxfpsunlocker.exe to close
		// WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}
}