#pragma once

#include "EquipmentState.h"

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

	void run(Character * player, bool flag, irr::u32 time)
	{
		if (!player)
			return;

		player->setInputState(EIS_ATTACK2, flag, time);

		if (flag)
		{
			EquipmentState * state = player->getEState();
			if (state)
				state->attack2(player, time);
		}
	}
};