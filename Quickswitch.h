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

	void run(Character * player, bool flag)
	{
		player->switchWeapons(ESWT_QUICK);
	}
};