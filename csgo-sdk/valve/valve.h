#pragma once
#include "../includes.h"

#include "../utils/singleton/singleton.h"

#include "interfaces/interfaces.h"
#include "interfaces/list/i_global_vars.h"
#include "interfaces/list/i_client.h"
#include "interfaces/list/i_app_system.h"
#include "interfaces/list/i_panel.h"
#include "interfaces/list/i_model_info.h"
#include "interfaces/list/i_engine_client.h"

#include "math/vector_2d.h"
#include "math/vector_3d.h"
#include "math/qangle.h"
#include "math/vmatrix.h"

#include "utils/recv/recv_table.h"
#include "utils/base_handle/base_handle.h"
#include "utils/base_handle/handle_entity.h"

//#define TIME_TO_TICKS(time) ((int)(0.5f + (float)((time)) / g_sdk.m_interfaces.m_globals->m_interval_per_tick))
//#define TICKS_TO_TIME(tick) (float)((tick ) * g_sdk.m_interfaces.m_globals->m_interval_per_tick)

class c_sdk {
public:
	struct modules_t {
		HMODULE m_client_dll;
		HMODULE m_engine_dll;
		HMODULE m_vgui_dll;
		HMODULE m_vgui2_dll;
		HMODULE m_tier_dll;
		HMODULE m_mat_sys_dll;
		HMODULE m_localize_dll;
		HMODULE m_shader_dll{};
		HMODULE m_data_cache_dll;
		HMODULE m_vstd_dll;
		HMODULE m_physics_dll;
		HMODULE m_file_system_dll;
		HMODULE m_server_dll;
		HMODULE m_studio_render_dll;
	} m_modules;

	struct interfaces_t {
		i_base_client_dll* m_client;
		i_engine* m_engine;
		i_global_vars_base* m_globals;
		i_panel* m_panel;
		i_model_info* m_model_info;
	} m_interfaces;
};

inline c_sdk g_sdk = c_sdk();