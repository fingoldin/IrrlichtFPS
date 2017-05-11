#include "stdafx.h"

#include "CrouchFallingState.h"

#include "FallingState.h"

void CrouchFallingState::update(Character * player, Core * core, irr::u32 time)
{
	if (!player || !core)
		return;

	if (!player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW FallingState());

	CrouchingState::update(player, core, time);
}