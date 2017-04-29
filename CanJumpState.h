#pragma once

#include "PlayerState.h"

#include "JumpingState.h"

class CanJumpState : public PlayerState
{
public:
	CanJumpState() : PlayerState() { }
	virtual ~CanJumpState() { }

	virtual void jump(Character * player)
	{
		player->setState(DBG_NEW JumpingState());
	}
};