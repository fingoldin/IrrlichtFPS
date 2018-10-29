#pragma once

#include "CrouchingState.h"

class CrouchJumpingState : public CrouchingState
{
public:
	CrouchJumpingState() : CrouchingState()
	{
		name = L"CrouchJumping";
	}
	
	~CrouchJumpingState() { }

	virtual void update(Character * player, Core * core, irr::u32 time);
};