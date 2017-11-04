#pragma once

#include "EquipmentState.h"

class SwitchingState : public EquipmentState
{
public:
	SwitchingState();
	~SwitchingState();

	virtual void enter(Character * player, class Core * core, irr::u32 time);

	virtual void update(Character * player, class Core * core, irr::u32 time);

private:

	irr::u32 startTime;
};