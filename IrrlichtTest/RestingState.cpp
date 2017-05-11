#include "stdafx.h"

#include "RestingState.h"

#include "WalkingState.h"
#include "RunningState.h"

#include "CrouchRestingState.h"

void RestingState::update(Character * player, Core * core, irr::u32 time)
{
	int y = (int)player->getInputState(EIS_FORWARD) - (int)player->getInputState(EIS_BACKWARD);
	int x = (int)player->getInputState(EIS_RIGHT) - (int)player->getInputState(EIS_LEFT);

	if (y != 0 || x != 0)
	{
		if (player->getInputState(EIS_WALK))
			player->setState(DBG_NEW WalkingState());
		else
			player->setState(DBG_NEW RunningState());
	}
	else if (player->getInputState(EIS_CROUCH))
		player->setState(new CrouchRestingState());

	StandingState::update(player, core, time);
}