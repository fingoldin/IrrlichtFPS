#include "stdafx.h"

#include "EquipmentState.h"

#include "SwitchingState.h"

void EquipmentState::switchWeapons(Character * player, E_SWITCH_WEAPON_TYPE weapon, irr::u32 time)
{
	if (weapon == ESWT_QUICK)
	{
		E_SELECTED_WEAPON prev = player->getPreviousWeapon();
		if (prev != ESW_NONE)
		{
			if (player->setWeapon(prev))
				player->setEState(DBG_NEW SwitchingState(), time);
		}
	}
	else if (player->setWeapon((E_SELECTED_WEAPON)weapon))
		player->setEState(DBG_NEW SwitchingState(), time);
}