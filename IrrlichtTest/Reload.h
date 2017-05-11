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

	void run(Character * player, bool flag)
	{
		//player->getState()->moveY(1);
	}
};