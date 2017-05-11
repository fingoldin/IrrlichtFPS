#include "stdafx.h"

#include "StandbyState.h"

#include "FiringState.h"

void FiringState::enter(Character * player, Core * core)
{
	if (!player || !core)
		return;

	setAnimation(player, EWA_ATTACK);

	startTime = core->getDevice()->getTimer()->getTime();
}

void FiringState::update(Character * player, Core * core, irr::u32 time)
{
	if (!player || !core)
		return;

	Weapon * weapon = player->getSelectedWeapon();

	if (weapon)
	{
		irr::u32 shotTime = weapon->getShotTime();

		if ((time - startTime) >= shotTime)
		{
			if (!weapon->getCanSpray())
				player->setEState(new StandbyState());
			else if(!player->getInputState(EIS_ATTACK) && (time - startTime) / shotTime > shotsFired)
					player->setEState(DBG_NEW StandbyState());
		}

		shotsFired = (time - startTime) / shotTime;
	}
	else
		startTime = time;
}