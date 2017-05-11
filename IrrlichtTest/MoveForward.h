#pragma once

#include "Command.h"

class MoveForward : public Command
{
public:
	MoveForward() : Command()
	{
		name = "forward";
		type = ECT_FORWARD;
	}

	~MoveForward()
	{

	}

	void run(Character * player, bool flag)
	{
		player->setInputState(EIS_FORWARD, flag);
	}
};