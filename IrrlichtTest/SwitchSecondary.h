#pragma once

#include "Command.h"

class SwitchSecondary : public Command
{
public:
	SwitchSecondary() : Command()
	{
		name = "switch2";
		type = ECT_SWITCHSECONDARY;
	}

	~SwitchSecondary()
	{

	}

	void run(Character * player, bool flag)
	{
		player->switchWeapons(ESWT_SECONDARY);
	}
};