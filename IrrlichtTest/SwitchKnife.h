#pragma once

#include "Command.h"

#include "Character.h"

class SwitchKnife : public Command
{
public:
	SwitchKnife() : Command()
	{
		name = "switch3";
		type = ECT_SWITCHKNIFE;
	}

	~SwitchKnife()
	{

	}

	void run(Character * player, bool flag, irr::u32 time)
	{
		player->switchWeapons(ESWT_KNIFE, time);
	}
};