#include "stdafx.h"

#include "FallingState.h"

#include "CrouchFallingState.h"

void FallingState::update(Character * player, Core * core, irr::u32 time)
{
	if (player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW CrouchFallingState());

	StandingState::update(player, core, time);
}