#include "stdafx.h"

#include "Weapon.h"

#include "Core.h"

#include "StandbyState.h"

#include "SwitchingState.h"

SwitchingState::SwitchingState() : CanSwitchState()
{
	startTime = 0;
	name = "SwitchingState";
}

SwitchingState::~SwitchingState()
{

}

void SwitchingState::enter(Character * player, Core * core)
{
	if (!player || !core)
		return;

	setAnimation(player, EWA_SWITCH);

	startTime = core->getDevice()->getTimer()->getTime();
}

void SwitchingState::update(Character * player, Core * core, irr::u32 time)
{
	if (!startTime)
		startTime = time;

	if ((time - startTime) >= player->getSelectedWeapon()->getSwitchTime())
		player->setEState(DBG_NEW StandbyState());
	
	EquipmentState::update(player, core, time);
}