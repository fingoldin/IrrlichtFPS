#pragma once

#include "EquipmentState.h"

class CanReloadState : public EquipmentState
{
public:
	CanReloadState() : EquipmentState() { }
	virtual ~CanReloadState() { }

	virtual void reload(Character * player, irr::u32 time);
};