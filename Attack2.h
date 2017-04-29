#pragma once

#include "Command.h"

class Attack2 : public Command
{
public:
	Attack2() : Command()
	{
		name = "attack2";
		type = ECT_ATTACK2;
	}

	~Attack2()
	{

	}

	void run(Character * player, bool flag)
	{
		player->setInputState(EIS_ATTACK2, flag);
	}
};