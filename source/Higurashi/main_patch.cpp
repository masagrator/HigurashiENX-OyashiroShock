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
	size_t array_size = (sizeof(LVOnetoEight))/(sizeof(LVOnetoEight[0]));
	for (size_t i = 0; i < array_size; i++)
		memcpy((void*)(TextRegionOffset + 0x1c3a18 + (i * 8)), (const void*)LVOnetoEight[i], 8);
	array_size = (sizeof(LVZero))/(sizeof(LVZero[0]));
	for (size_t i = 0; i < array_size; i++)
		memcpy((void*)(TextRegionOffset + 0x1c9458 + (i * 8)), (const void*)LVZero[i], 8);
	return;
}

void higurashi_main()
{
	TextRegionOffset = (uintptr_t)skyline::utils::getRegionAddress(skyline::utils::region::Text);
	A64HookFunction((void**)&nn::vi::Initialize,
			reinterpret_cast<void*>(Initialize_hook),
			(void**)&Initialize_original);
}
