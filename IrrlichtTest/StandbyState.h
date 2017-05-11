#pragma once

#include "CanSwitchState.h"

class StandbyState : public CanSwitchState
{
public:
	StandbyState() : CanSwitchState()
	{
		name = "StandbyState";
	}

	~StandbyState()
	{

	}

	virtual void enter(Character * player, Core * core)
	{
		setAnimation(player, EWA_REST);
	}

	virtual void attack(Character * player);

	virtual void update(Character * player, Core * core, irr::u32 time);
};