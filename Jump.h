#pragma once

#include "Command.h"

#include "Character.h"

#include "PlayerState.h"

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

	void run(Character * player, bool flag, irr::u32 time)
	{
		player->getState()->jump(player, time);
	}
};