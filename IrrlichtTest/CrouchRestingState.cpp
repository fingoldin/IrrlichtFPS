#include "stdafx.h"

#include "CrouchRestingState.h"

#include "CrouchWalkingState.h"
#include "RestingState.h"

void CrouchRestingState::update(Character * player, Core * core, irr::u32 time)
{
	if (!player || !core)
		return;

	int y = (int)player->getInputState(EIS_FORWARD) - (int)player->getInputState(EIS_BACKWARD);
	int x = (int)player->getInputState(EIS_RIGHT) - (int)player->getInputState(EIS_LEFT);

	if (y != 0 || x != 0)
		player->setState(DBG_NEW CrouchWalkingState(), time);

	else if (!player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW RestingState(), time);

	else
		CrouchingState::update(player, core, time);
}