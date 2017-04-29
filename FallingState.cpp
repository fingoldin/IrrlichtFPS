#include "stdafx.h"

#include "FallingState.h"

#include "CrouchFallingState.h"

void FallingState::update(Character * player, Core * core, irr::u32 dt)
{
	if (player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW CrouchFallingState());

	PlayerState::update(player, core, dt);
}