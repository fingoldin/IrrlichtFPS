#pragma once

#include "PlayerState.h"

class CrouchJumpingState : public PlayerState
{
public:
	CrouchJumpingState() : PlayerState()
	{
		name = L"CrouchJumping";
	}
	
	~CrouchJumpingState() { }

	virtual void update(Character * player, Core * core, irr::u32 dt);
};