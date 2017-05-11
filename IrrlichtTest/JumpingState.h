#pragma once

#include "StandingState.h"

class JumpingState : public StandingState
{
public:
	JumpingState() : StandingState()
	{
		name = L"Jumping";
	}

	~JumpingState() { }

	virtual void update(Character * player, Core * core, irr::u32 time);
};