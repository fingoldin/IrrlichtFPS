#pragma once

#include "EquipmentState.h"

#include "StandbyState.h"

class ReloadingState : public EquipmentState
{
public:
	ReloadingState() : EquipmentState()
	{
		name = "ReloadingState";
	}

	~ReloadingState() { }

	virtual void enter(Character * player, Core * core, irr::u32 time)
	{
		if (!player || !core)
			return;

		Weapon * weapon = player->getSelectedWeapon();

		
		setAnimation(player, EWA_RELOAD, time);

		startTime = time;
	}

	virtual void reload(Character * plater, irr::u32 time) { }

	virtual void update(Character * player, Core * core, irr::u32 time)
	{
		if (!startTime)
			startTime = time;

		if ((time - startTime) >= player->getSelectedWeapon()->getActualReloadTime())
			player->getSelectedWeapon()->reload();

		if ((time - startTime) >= player->getSelectedWeapon()->getReloadTime())
			player->setEState(DBG_NEW StandbyState(), time);

		EquipmentState::update(player, core, time);
	}

protected:

	irr::u32 startTime;
};