#include "stdafx.h"

#include "JumpingState.h"

#include "CrouchJumpingState.h"

void JumpingState::update(Character * player, Core * core, irr::u32 time)
{
	if (player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW CrouchJumpingState(), time);
	else
		StandingState::update(player, core, time);
}