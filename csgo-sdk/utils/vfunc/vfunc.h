#pragma once

template <typename T>
__forceinline T call_vfunc(const void* instance, const size_t index) {
	int* vtable = *(int**)instance;
	int address = vtable[index];
	return (T)(address);
}