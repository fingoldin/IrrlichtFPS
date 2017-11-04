#pragma once

#include "Command.h"

#include "Character.h"

class Crouch : public Command
{
public:
	Crouch() : Command()
	{
		name = "crouch";
		type = ECT_CROUCH;
	}

	~Crouch()
	{

	}

	void run(Character * player, bool flag, irr::u32 time)
	{
		player->setInputState(EIS_CROUCH, flag, time);
	}
};