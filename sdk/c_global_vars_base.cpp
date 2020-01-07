
#include "c_global_vars_base.h"
#include "../utils/c_memory.h"
#include "../sdk/c_base_entity.h"
#include "../sdk/c_cs_player.h"

namespace g
{
	c_cs_player* pLocalEntity = nullptr;
	int			   CheatType = -1;
	bool           Shot[65];
	bool           Hit[65];
	int            MissedShots[65];

	DWORD CourierNew;
	DWORD Tahoma;
}

c_global_vars_base* c_global_vars_base::get()
{
	static const auto globals = **reinterpret_cast<c_global_vars_base***>(sig("client_panorama.dll", "A1 ? ? ? ? 5E 8B 40 10") + 1);
	return globals;
}
