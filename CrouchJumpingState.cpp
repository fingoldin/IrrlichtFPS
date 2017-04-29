#include "stdafx.h"

#include "CrouchJumpingState.h"

#include "JumpingState.h"

void CrouchJumpingState::update(Character * player, Core * core, irr::u32 dt)
{
	if (!player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW JumpingState());

	PlayerState::update(player, core, dt);
}