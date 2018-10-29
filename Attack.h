#pragma once

#include "EquipmentState.h"

#include "Command.h"

class Attack : public Command
{
public:
	Attack() : Command()
	{
		name = "attack1";
		type = ECT_ATTACK;
	}

	~Attack()
	{

	}

	void run(Character * player, bool flag, irr::u32 time)
	{
		if (!player)
			return;

		player->setInputState(EIS_ATTACK, flag, time);

		if (flag)
		{
			EquipmentState * state = player->getEState();
			if (state)
				state->attack(player, time);
		}
	}
};