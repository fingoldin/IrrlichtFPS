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

	void run(Character * player, bool flag, irr::u32 time)
	{
		player->switchWeapons(ESWT_SECONDARY, time);
	}
};