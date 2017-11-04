#pragma once

#include "Command.h"

class Quickswitch : public Command
{
public:
	Quickswitch() : Command()
	{
		name = "qswitch";
		type = ECT_QUICKSWITCH;
	}

	~Quickswitch()
	{

	}

	void run(Character * player, bool flag, irr::u32 time)
	{
		if(flag)
			player->switchWeapons(ESWT_QUICK, time);
	}
};