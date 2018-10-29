#pragma once

#include "CrouchingState.h"

class CrouchWalkingState : public CrouchingState
{
public:
	CrouchWalkingState() : CrouchingState()
	{
		name = L"CrouhWalking";
	}

	~CrouchWalkingState() { }

	virtual void update(Character * player, Core * core, irr::u32 time);
};