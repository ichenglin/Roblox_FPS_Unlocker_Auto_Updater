#include <iostream>
#include <windows.h>
#include <nlohmann/json.hpp>
#include "configuration/configuration.h"
#include "process/process.h"
#include "get_request/get_request.h"
#include "download/download.h"
#include "uncompress/uncompress.h"
#include "file_system/file_system.h"

std::string get_latest_version(std::string rate_limit_fallback);
nlohmann::json get_default_configuration(std::string latest_version);
void fps_unlocker_launch();
bool get_fps_unlocker_alive();

int main() {
	// check active roblox fps unlocker process
	bool fps_unlocker_alive = get_fps_unlocker_alive();
	if (fps_unlocker_alive) {
		// fps unlocker process found
		printf("Roblox FPS Unlocker is already running,\nplease close it and relaunch this application.\n\n");
		printf("The application is closing in 10 seconds...\n");
		Sleep(10000);
		return 0;
	}
	std::string latest_version = get_latest_version("error");
	if (latest_version == "error") {
		// an error has occured while accessing github api (rate limited or api endpoint update)
		printf("An error has occured while accessing Github api,\nthis might be caused by exceeding the rate limit or Github api endpoint updates.\n\n");
		printf("Update check process cancelled, directly launching latest download in 10 seconds...\n");
		Sleep(10000);
		fps_unlocker_launch();
		return 0;
	}
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
		// download fps unlocker from source
		printf("New version available, downloading from source...\n");
		std::string update_source = "https://github.com/axstin/rbxfpsunlocker/releases/download/" + latest_version + "/rbxfpsunlocker-x64.zip";
		std::string update_folder = "downloads\\" + latest_version;
		std::string update_location = "downloads\\" + latest_version + "\\rbxfpsunlocker.zip";
		FileSystem::directory_create(update_folder);
		download(update_source, update_location);
		uncompress(update_location, "rbxfpsunlocker.exe", "rbxfpsunlocker.exe");
		// update configuration
		configuration["installed_version"] = latest_version;
		configuration_file.set_configuration(configuration);
		// installation process completed
		printf("Download completed.\n");
	} else {
		printf("No update is needed.\n");
	}
	fps_unlocker_launch();
	return 0;
}

std::string get_latest_version(std::string rate_limit_fallback) {
	// json from github api
	std::string version_raw = get_request("https://api.github.com/repos/axstin/rbxfpsunlocker/releases/latest", "Mozilla/5.0");
	nlohmann::json version_json = nlohmann::json::parse(version_raw);
	// fallback if exceeded github api rate limit
	if (!version_json.contains("tag_name")) {
		return rate_limit_fallback;
	}
	return version_json["tag_name"];
}

nlohmann::json get_default_configuration(std::string latest_version) {
	nlohmann::json default_configuration;
	default_configuration["configuration_version"] = 1;
	default_configuration["installed_version"] = latest_version;
	return default_configuration;
}

void fps_unlocker_launch() {
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

bool get_fps_unlocker_alive() {
	// get the running processes of roblox fps unlocker
	std::vector<HANDLE> fpsunlocker_processes = Process::get_process_by_name("rbxfpsunlocker.exe");
	return fpsunlocker_processes.size() > 0;
}