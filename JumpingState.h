#pragma once

#include "PlayerState.h"

class JumpingState : public PlayerState
{
public:
	JumpingState() : PlayerState()
	{
		name = L"Jumping";
	}

	~JumpingState() { }

	virtual void update(Character * player, Core * core, irr::u32 dt);
};