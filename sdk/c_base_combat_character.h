#pragma once

#include "c_base_animating.h"

class c_base_combat_character : public c_base_animating
{
public:
	netvar(get_current_weapon_handle(), c_base_handle, "CBaseCombatCharacter", "m_hActiveWeapon")
	netvar(get_last_shot_time(), float, "CWeaponCSBase", "m_fLastShotTime")
	pnetvar(get_current_weapons(), unsigned, "CBaseCombatCharacter", "m_hMyWeapons")

	datamap(get_next_attack(), float, "m_flNextAttack")
};
