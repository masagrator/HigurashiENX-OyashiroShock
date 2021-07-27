#include "skyline/inlinehook/And64InlineHook.hpp"
#include "skyline/utils/cpputils.hpp"
#include "nn/vi.h"
#include "Higurashi/main_patch.hpp"

#define LINKABLE __attribute__ ((weak))
void nn::vi::Initialize(void) LINKABLE;

uintptr_t TextRegionOffset = 0;

void (*Initialize_original)();
void Initialize_hook()
{
	Initialize_original();
	size_t LV1_8_size = LV1_8.size();
	const char* address[LV1_8_size];
	for (size_t i = 0; i < LV1_8_size; i++) {
		static uint16_t temp = 0;
		address[i] = LV1_8[i].c_str();
		memcpy((void*)(TextRegionOffset + 0x1c3a18 + temp), (const void*)&address[i], 8);
		temp += 8;
	}
	size_t LV0_size = LV0.size();
	const char* address2[LV0_size];
	for (size_t i = 0; i < LV0_size; i++) {
		static uint16_t temp = 0;
		address2[i] = LV0[i].c_str();
		memcpy((void*)(TextRegionOffset + 0x1c9458 + temp), (const void*)&address2[i], 8);
		temp += 8;
	}
	return;
}

void higurashi_main()
{
	TextRegionOffset = (uintptr_t)skyline::utils::getRegionAddress(skyline::utils::region::Text);
	A64HookFunction((void**)&nn::vi::Initialize,
			reinterpret_cast<void*>(Initialize_hook),
			(void**)&Initialize_original);
}
