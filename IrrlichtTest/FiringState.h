#pragma once

#include "EquipmentState.h"

class FiringState : public EquipmentState
{
public:
	FiringState() : EquipmentState()
	{
		name = "FiringState";
	}

	~FiringState()
	{

	}

	virtual void enter(Character * player, Core * core, irr::u32 time);
	virtual void update(Character * player, Core * core, irr::u32 time);

private:

	irr::u32 shotsFired;
	irr::u32 startTime;
};