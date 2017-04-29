#pragma once

#include "PlayerState.h"

class CrouchWalkingState : public PlayerState
{
public:
	CrouchWalkingState() : PlayerState()
	{
		name = L"CrouhWalking";
	}

	~CrouchWalkingState() { }

	virtual void update(Character * player, Core * core, irr::u32 dt);
};