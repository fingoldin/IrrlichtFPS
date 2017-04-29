#pragma once

#include "Command.h"

class MoveLeft : public Command
{
public:
	MoveLeft() : Command()
	{
		name = "left";
		type = ECT_LEFT;
	}

	~MoveLeft()
	{

	}

	void run(Character * player, bool flag)
	{
		player->setInputState(EIS_LEFT, flag);
	}
};