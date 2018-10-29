#pragma once

#include "PlayerState.h"

class StandingState : public PlayerState
{
public:

	StandingState() : PlayerState() { }
	virtual ~StandingState() { }

	virtual void update(Character * player, Core * core, irr::u32 time)
	{
		PlayerState::update(player, core, time);
	}
};