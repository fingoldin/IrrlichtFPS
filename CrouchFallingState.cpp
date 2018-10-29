#include "stdafx.h"

#include "CrouchFallingState.h"

#include "FallingState.h"

void CrouchFallingState::update(Character * player, Core * core, irr::u32 time)
{
	if (!player || !core)
		return;

	if (!player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW FallingState(), time);
	else
		CrouchingState::update(player, core, time);
}