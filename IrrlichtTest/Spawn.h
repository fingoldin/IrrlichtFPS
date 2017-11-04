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

	void run(Character * player, bool flag, irr::u32 time)
	{
		if (flag)
		{
			player->setState(DBG_NEW RestingState(), time);
			player->setEState(DBG_NEW StandbyState(), time);
		}
	}
};