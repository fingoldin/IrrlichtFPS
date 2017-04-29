#include "stdafx.h"

#include "CanSwitchState.h"

#include "SwitchingState.h"

void CanSwitchState::switchWeapons(Character * player, E_SWITCH_WEAPON_TYPE weapon)
{
	if (weapon == ESWT_QUICK)
	{
		E_SELECTED_WEAPON prev = player->getPreviousWeapon();
		if (prev != ESW_NONE)
		{
			if(player->setWeapon(prev))
				player->setState(DBG_NEW SwitchingState());
		}
	}
	else if (player->setWeapon((E_SELECTED_WEAPON)weapon))
			player->setState(DBG_NEW SwitchingState());
}