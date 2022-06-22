#include "modules.h"

void c_modules::init() {
	g_sdk.m_modules.m_client_dll = GetModuleHandleA("client.dll");
	g_sdk.m_modules.m_engine_dll = GetModuleHandleA("engine.dll");
	g_sdk.m_modules.m_tier_dll = GetModuleHandleA("tier0.dll");
	g_sdk.m_modules.m_localize_dll = GetModuleHandleA("localize.dll");
	g_sdk.m_modules.m_file_system_dll = GetModuleHandleA("filesystem_stdio.dll");
	g_sdk.m_modules.m_shader_dll = GetModuleHandleA("shaderapidx9.dll");
	g_sdk.m_modules.m_vgui_dll = GetModuleHandleA("vguimatsurface.dll");
	g_sdk.m_modules.m_vgui2_dll = GetModuleHandleA("vgui2.dll");
	g_sdk.m_modules.m_physics_dll = GetModuleHandleA("vphysics.dll");
	g_sdk.m_modules.m_vstd_dll = GetModuleHandleA("vstdlib.dll");
	g_sdk.m_modules.m_mat_sys_dll = GetModuleHandleA("materialsystem.dll");
	g_sdk.m_modules.m_data_cache_dll = GetModuleHandleA("datacache.dll");
	g_sdk.m_modules.m_studio_render_dll = GetModuleHandleA("studiorender.dll");
	g_sdk.m_modules.m_server_dll = GetModuleHandleA("server.dll");

	// anti cheat update bypass.
	/*constexpr long patch_address = 0x69690004C201B0;
	static std::string sig = ("55 8B EC 56 8B F1 33 C0 57 8B 7D 08");

	LPCWSTR game_modules[] {
		L"client.dll",
		L"engine.dll",
		L"server.dll",
		L"studiorender.dll",
		L"materialsystem.dll",
		L"server.dll"
	};

	for (auto base : game_modules)
		WriteProcessMemory(GetCurrentProcess(), c_utils::get()->find_sig(GetModuleHandleW(base), sig), &patch_address, 5, 0);*/
}