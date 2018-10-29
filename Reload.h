#pragma once

#include "Command.h"

class Reload : public Command
{
public:
	Reload() : Command()
	{
		name = "reload";
		type = ECT_RELOAD;
	}

	~Reload()
	{

	}

	void run(Character * player, bool flag, irr::u32 time)
	{
		player->getEState()->reload(player, time);
	}
};