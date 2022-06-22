#pragma once
#include "../includes.h"

#include "singleton/singleton.h"

#include "minhook/minhook.h"

#include "bit_flags_helper/bit_flags.h"

#include "color/color.h"

#include "modules/modules.h"

#include "vfunc/vfunc.h"

#include "ctx/ctx.h"

class c_utils : public c_singleton<c_utils> {
public:
	uint8_t* find_sig(HMODULE module, const std::string& byte_array);
};