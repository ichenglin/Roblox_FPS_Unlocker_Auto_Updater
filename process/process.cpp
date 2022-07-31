#include <windows.h>
#include <tlhelp32.h>
#include "process.h"

std::vector<HANDLE> Process::get_process_by_name(std::string process_name) {
	std::vector<HANDLE> processes;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	size_t count = 0;
	if (Process32First(snapshot, &entry) == TRUE) {
		while (Process32Next(snapshot, &entry) == TRUE) {
			if (_stricmp(entry.szExeFile, process_name.c_str()) == 0) {
				HANDLE match_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				processes.push_back(match_process);
			}
		}
	}
	CloseHandle(snapshot);
	return processes;
}