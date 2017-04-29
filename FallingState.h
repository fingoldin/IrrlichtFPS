#pragma once

#include "PlayerState.h"

class FallingState : public PlayerState
{
public:
	FallingState() : PlayerState()
	{
		name = L"Falling";
	}

	~FallingState()
	{

	}

	virtual void update(Character * player, Core * core, irr::u32 dt);
};