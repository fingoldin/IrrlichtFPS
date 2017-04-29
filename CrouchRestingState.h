#pragma once

#include "stdafx.h"

#include "PlayerState.h"

class CrouchRestingState : public PlayerState
{
public:
	CrouchRestingState() : PlayerState()
	{
		name = L"CrouchResting";
	}

	~CrouchRestingState() { }

	virtual void update(Character * player, Core * core, irr::u32 dt);
};