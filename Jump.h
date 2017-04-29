#pragma once

#include "Command.h"

class Jump : public Command
{
public:
	Jump() : Command()
	{
		name = "jump";
		type = ECT_JUMP;
	}

	~Jump()
	{

	}

	void run(Character * player, bool flag)
	{
		player->getState()->jump(player);
	}
};