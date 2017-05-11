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

	void run(Character * player, bool flag)
	{
		player->switchWeapons(ESWT_PRIMARY);
	}
};