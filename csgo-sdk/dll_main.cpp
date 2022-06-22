#include "includes.h"

int init() {
	while (!GetModuleHandleA("serverbrowser.dll"))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	c_modules::get()->init();

	c_interfaces::get()->init();

	return 0u;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reversed) {
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(module);

		if (const auto thread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(init), module, 0, 0))
			CloseHandle(thread);
	}

	return 1u;
}