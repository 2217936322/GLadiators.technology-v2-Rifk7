#include "c_rifk.h"
#include "hooks/c_hooks.h"
#include "hooks/idirect3ddevice9.h"
#include "menu/c_menu.h"
#include <thread>


using namespace std::chrono_literals;

__declspec(dllexport) rifk_loader_info loader_info {};

c_rifk::c_rifk()
{
	c_menu::instance();
	c_netvar::instance();
	c_hooks::run();
}

void __zx(void) {
	c_rifk::instance();
}

bool APIENTRY DllMain(const HINSTANCE module, const DWORD dw_reason_for_call, LPVOID lp_reserved)
{
	if (dw_reason_for_call == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)__zx, 0, 0, 0);
	}

	return true;
}
