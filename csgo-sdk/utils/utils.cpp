#include "utils.h"

uint8_t* c_utils::find_sig(HMODULE module, const std::string& byte_array) {
	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{};
		const auto start = const_cast<char*>(pattern);
		const auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;

				bytes.push_back(-1);
			}
			else
				bytes.push_back(strtoul(current, &current, 16));
		}

		return bytes;
	};

	const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
	const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module) + dos_header->e_lfanew);

	const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	const auto pattern_bytes = pattern_to_byte(byte_array.c_str());
	const auto scan_bytes = reinterpret_cast<std::uint8_t*>(module);

	const auto s = pattern_bytes.size();
	const auto d = pattern_bytes.data();

	for (auto i = 0ul; i < size_of_image - s; ++i) {
		bool found = true;
		for (auto j = 0ul; j < s; ++j) {
			if (scan_bytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}

		if (found)
			return &scan_bytes[i];
	}

	return nullptr;
}