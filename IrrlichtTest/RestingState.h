#pragma once

#include "CanJumpState.h"

class RestingState : public CanJumpState
{
public:
	RestingState() : CanJumpState()
	{
		name = L"Resting";
	}

	~RestingState()
	{

	}

	virtual void update(Character * player, Core * core, irr::u32 time);
};