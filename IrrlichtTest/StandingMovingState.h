#pragma once

#include "stdafx.h"

#include "MovingState.h"

class StandingMovingState : public MovingState
{
public:
	StandingMovingState() : MovingState()
	{
		name = L"Moving";
	}

	virtual ~StandingMovingState() { }

	virtual void update(Character * player, Core * core, irr::u32 dt);
};

