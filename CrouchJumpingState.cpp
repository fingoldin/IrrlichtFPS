#include "stdafx.h"

#include "CrouchJumpingState.h"

#include "JumpingState.h"

void CrouchJumpingState::update(Character * player, Core * core, irr::u32 time)
{
	if (!player || !core)
		return;

	if (!player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW JumpingState(), time);
	else
		CrouchingState::update(player, core, time);
}