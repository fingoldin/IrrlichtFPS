#pragma once

#include "CanJumpState.h"

class WalkingState : public CanJumpState
{
public:
	WalkingState() : CanJumpState()
	{
		name = L"Walking";
	}

	~WalkingState() { }

	virtual void update(Character * player, Core * core, irr::u32 time);
};