#pragma once

#include "Command.h"
#include "Character.h"

#include "RestingState.h"
#include "StandbyState.h"

class Spawn : public Command
{
public:
	Spawn() : Command()
	{
		name = "spawn";
		type = ECT_SPAWN;
	}

	~Spawn()
	{

	}

	void run(Character * player, bool flag)
	{
		if (flag)
		{
			player->setState(DBG_NEW RestingState());
			player->setEState(DBG_NEW StandbyState());
		}
	}
};