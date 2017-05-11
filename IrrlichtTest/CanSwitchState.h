#pragma once

#include "EquipmentState.h"

#include "Weapon.h"

class CanSwitchState : public EquipmentState
{
public:
	CanSwitchState() : EquipmentState() { }
	virtual ~CanSwitchState() { }

	virtual void switchWeapons(Character * player, E_SWITCH_WEAPON_TYPE weapon);

};