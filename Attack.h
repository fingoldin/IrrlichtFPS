#pragma once

#include "Command.h"

class Attack : public Command
{
public:
	Attack() : Command()
	{
		name = "attack";
		type = ECT_ATTACK;
	}

	~Attack()
	{

	}

	void run(Character * player, bool flag)
	{
		player->setInputState(EIS_ATTACK, flag);
	}
};