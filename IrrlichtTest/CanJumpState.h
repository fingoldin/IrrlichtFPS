#pragma once

#include "StandingState.h"

#include "JumpingState.h"

class CanJumpState : public StandingState
{
public:
	CanJumpState() : StandingState() { }
	virtual ~CanJumpState() { }

	virtual void jump(Character * player, irr::u32 time)
	{
		player->setState(DBG_NEW JumpingState(), time);
	}
};