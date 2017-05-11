#pragma once

#include "CrouchingState.h"

class CrouchFallingState : public CrouchingState
{
public:
	CrouchFallingState() : CrouchingState()
	{
		name = L"CrouchFalling";
	}

	~CrouchFallingState() { }

	virtual void update(Character * player, Core * core, irr::u32 time);
};