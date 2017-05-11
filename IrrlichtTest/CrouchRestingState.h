#pragma once

#include "CrouchingState.h"

class CrouchRestingState : public CrouchingState
{
public:
	CrouchRestingState() : CrouchingState()
	{
		name = L"CrouchResting";
	}

	~CrouchRestingState() { }

	virtual void update(Character * player, Core * core, irr::u32 time);
};