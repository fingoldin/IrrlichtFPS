#include "stdafx.h"

#include "CrouchFallingState.h"

#include "FallingState.h"

void CrouchFallingState::update(Character * player, Core * core, irr::u32 dt)
{
	if (!player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW FallingState());

	PlayerState::update(player, core, dt);
}