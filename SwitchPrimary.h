#pragma once

#include "Command.h"

class SwitchPrimary : public Command
{
public:
	SwitchPrimary() : Command()
	{
		name = "switch1";
		type = ECT_SWITCHPRIMARY;
	}

	~SwitchPrimary()
	{

	}

	void run(Character * player, bool flag, irr::u32 time)
	{
		player->switchWeapons(ESWT_PRIMARY, time);
	}
};