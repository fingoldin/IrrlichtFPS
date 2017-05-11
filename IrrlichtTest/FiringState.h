#pragma once

#include "CanSwitchState.h"

class FiringState : public CanSwitchState
{
public:
	FiringState() : CanSwitchState()
	{
		name = "FiringState";
	}

	~FiringState()
	{

	}

	virtual void enter(Character * player, Core * core);
	virtual void update(Character * player, Core * core, irr::u32 time);

private:

	int shotsFired;
	irr::u32 startTime;
};