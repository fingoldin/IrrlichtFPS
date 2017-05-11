#pragma once

#include "Command.h"

#include "Character.h"

class Walk : public Command
{
public:
	Walk() : Command()
	{
		name = "walk";
		type = ECT_WALK;
	}

	~Walk()
	{

	}

	void run(Character * player, bool flag)
	{
		player->setInputState(EIS_WALK, flag);
	}
};