#include "stdafx.h"

#include "CanReloadState.h"

#include "EquipmentState.h"

#include "Weapon.h"

#include "SwitchingState.h"
#include "ReloadingState.h"

void CanReloadState::reload(Character * player, irr::u32 time)
{
	if (!player)
		return;

	Weapon * weapon = player->getSelectedWeapon();

	if (weapon && weapon->getTotalBullets() && weapon->getMagBullets() < weapon->getMagCapacity())
		player->setEState(DBG_NEW ReloadingState(), time);
}