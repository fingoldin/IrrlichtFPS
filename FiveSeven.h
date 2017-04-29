#pragma once

#include "Weapon.h"

class FiveSeven : public Weapon
{
public:

	FiveSeven(Core * core, irr::s32 id) : Weapon(core, id)
	{
		reloadTime = 1000;
	}
};