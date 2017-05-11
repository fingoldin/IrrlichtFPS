#include "stdafx.h"

#include "StandbyState.h"

#include "FiringState.h"

void StandbyState::update(Character * player, Core * core, irr::u32 time)
{
	//if (!player || !core)
	//	return;

	//if (player->getInputState(EIS_ATTACK))
	//	player->setEState(new FiringState());
}

void StandbyState::attack(Character * player)
{
	player->setEState(new FiringState());
}