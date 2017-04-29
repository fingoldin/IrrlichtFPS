#pragma once

#include "PlayerState.h"

class EquipmentState : public PlayerState
{
public:
	EquipmentState() { }
	virtual ~EquipmentState() { }

	virtual void attack(Character * player) { }
	virtual void attack2(Character * player) { }

	virtual void switchWeapons(Character * player, E_SWITCH_WEAPON_TYPE weapon) { }
};