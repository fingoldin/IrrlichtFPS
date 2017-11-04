#include "stdafx.h"

#include "FiringState.h"

#include "EquipmentState.h"

#include "StandbyState.h"

void FiringState::enter(Character * player, Core * core, irr::u32 time)
{
	if (!player || !core)
		return;

	Weapon * weapon = player->getSelectedWeapon();

	if (weapon)
	{
		if (weapon->fire())
		{
			setAnimation(player, EWA_ATTACK, time);
			shotsFired = 1;
		}
		else
		{
			//setAnimation(player, EWA_NOBULLETS, time);
			player->setEState(DBG_NEW StandbyState(), time);
		}
	}

	startTime = time;
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
			if (!weapon->getCanSpray() && !player->getInputState(EIS_ATTACK))
				player->setEState(DBG_NEW StandbyState(), time);

			else if(weapon->getCanSpray() && !player->getInputState(EIS_ATTACK) && (time - startTime) / shotTime > shotsFired)
				player->setEState(DBG_NEW StandbyState(), time);
			
			else if ((time - startTime) / shotTime > shotsFired)
			{
				if (weapon->fire())
					shotsFired++;
				else
					player->setEState(DBG_NEW StandbyState(), time);
			}
		}
	}
	else
		startTime = time;

	EquipmentState::update(player, core, time);
}