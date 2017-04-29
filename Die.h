#pragma once

#include "Command.h"
#include "DeadState.h"

class Die : public Command
{
public:
	Die() : Command()
	{
		name = "die";
		type = ECT_DIE;
	}

	~Die()
	{

	}

	void run(Character * player, bool flag)
	{
		player->setState(DBG_NEW DeadState());
	}
};