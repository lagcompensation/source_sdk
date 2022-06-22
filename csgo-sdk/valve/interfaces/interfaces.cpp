#include "interfaces.h"

void* c_interfaces::get_interface(const HMODULE module, const char* interface_name) {
	return reinterpret_cast<create_interface_fn>(GetProcAddress(module, "CreateInterface"))(interface_name, nullptr);
}

void c_interfaces::init() {
	g_sdk.m_interfaces.m_client = static_cast<i_base_client_dll*>(get_interface(g_sdk.m_modules.m_client_dll, "VClient018"));
	g_sdk.m_interfaces.m_engine = static_cast<i_engine*>(get_interface(g_sdk.m_modules.m_engine_dll, "VEngineClient014"));
	g_sdk.m_interfaces.m_panel = static_cast<i_panel*>(get_interface(g_sdk.m_modules.m_vgui2_dll, "VGUI_Panel009"));
	g_sdk.m_interfaces.m_model_info = static_cast<i_model_info*>(get_interface(g_sdk.m_modules.m_engine_dll, "VModelInfoClient004"));

	g_sdk.m_interfaces.m_globals = **reinterpret_cast<i_global_vars_base***>((*(DWORD**)(g_sdk.m_interfaces.m_client))[0] + 0x1F);
}