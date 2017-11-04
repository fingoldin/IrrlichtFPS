#pragma once

#include "PlayerState.h"

class CrouchingState : public PlayerState
{
public:

	CrouchingState() : PlayerState() { }
	virtual ~CrouchingState() { }

	virtual void update(Character * player, Core * core, irr::u32 time)
	{
		PlayerState::update(player, core, time);
	}
};