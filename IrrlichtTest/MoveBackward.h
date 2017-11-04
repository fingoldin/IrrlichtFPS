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

	void run(Character * player, bool flag, irr::u32 time)
	{
		player->setInputState(EIS_BACKWARD, flag, time);
	}
};