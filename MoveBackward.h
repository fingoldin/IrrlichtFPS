#pragma once

#include "Command.h"

class MoveBackward : public Command
{
public:
	MoveBackward() : Command()
	{
		name = "backward";
		type = ECT_BACKWARD;
	}

	~MoveBackward()
	{

	}

	void run(Character * player, bool flag)
	{
		player->setInputState(EIS_BACKWARD, flag);
	}
};