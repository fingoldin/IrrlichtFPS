#pragma once

#include "EquipmentState.h"

class CanSwitchState : public EquipmentState
{
public:
	CanSwitchState() : EquipmentState() { }
	virtual ~CanSwitchState() { }

	virtual void switchWeapons(Character * player, E_SWITCH_WEAPON_TYPE weapon);
};