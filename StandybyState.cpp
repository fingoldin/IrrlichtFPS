#include "stdafx.h"

#include "StandbyState.h"

#include "EquipmentState.h"

#include "CanReloadState.h"

#include "Constants.h"

#include "FiringState.h"

void StandbyState::update(Character * player, Core * core, irr::u32 time)
{
	if (!startTime)
		startTime = time;

	if (!player || !core)
		return;

	//if (player->getInputState(EIS_ATTACK))
	//	player->setEState(new FiringState());

	Weapon * weapon = player->getSelectedWeapon();

	if (weapon && !weapon->getMagBullets() && weapon->getTotalBullets() && (time - startTime) > STANDBY_RELOAD_WAIT_TIME)
		reload(player, time);

	EquipmentState::update(player, core, time);
}

void StandbyState::attack(Character * player, irr::u32 time)
{
	Weapon * weapon = player->getSelectedWeapon();

	if (weapon && weapon->getMagBullets())
		player->setEState(new FiringState(), time);
}