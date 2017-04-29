#pragma once

#include "PlayerState.h"

class CrouchFallingState : public PlayerState
{
public:
	CrouchFallingState() : PlayerState()
	{
		name = L"CrouchFalling";
	}

	~CrouchFallingState() { }

	virtual void update(Character * player, Core * core, irr::u32 dt);
};