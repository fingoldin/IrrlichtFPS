#pragma once

#include "CanReloadState.h"

class StandbyState : public CanReloadState
{
public:
	StandbyState() : CanReloadState()
	{
		name = "StandbyState";
	}

	~StandbyState()
	{

	}

	virtual void enter(Character * player, Core * core, irr::u32 time)
	{
		setAnimation(player, EWA_REST, time);

		startTime = time;
	}

	virtual void attack(Character * player, irr::u32 time);

	virtual void update(Character * player, Core * core, irr::u32 time);

protected:

	irr::u32 startTime;
};