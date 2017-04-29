#include "stdafx.h"

#include "JumpingState.h"

#include "CrouchJumpingState.h"

void JumpingState::update(Character * player, Core * core, irr::u32 dt)
{
	if (player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW CrouchJumpingState());

	PlayerState::update(player, core, dt);
}