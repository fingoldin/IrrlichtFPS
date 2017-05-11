#pragma once

#include "StandingState.h"

class FallingState : public StandingState
{
public:
	FallingState() : StandingState()
	{
		name = L"Falling";
	}

	~FallingState()
	{

	}

	virtual void update(Character * player, Core * core, irr::u32 time);
};