#pragma once

#include "CanJumpState.h"

class RunningState : public CanJumpState
{
public:
	RunningState() : CanJumpState()
	{
		name = L"Running";
	}

	~RunningState() { }

	virtual void update(Character * player, Core * core, irr::u32 time);
};

