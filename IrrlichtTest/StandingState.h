#pragma once

#include "PlayerState.h"

class StandingState : public PlayerState
{
public:

	StandingState() : PlayerState() { }
	virtual ~StandingState() { }

	virtual void update(Character * player, Core * core, irr::u32 time)
	{
		irr::u32 dt = time - lastUpdateTime;
		lastUpdateTime = time;

		if (!core || !player)
			return;

		/*irr::f32 y = player->getScale().Y;

		irr::f32 v = y + PLAYER_CROUCH_SPEED * ((double)dt / 1000.0f);
		if (v > 1.0f)
			v = 1.0f;

		if (y < 0.999)
		{
			player->setScale(irr::core::vector3df(1.0f, v, 1.0f));
			player->setPosition(irr::core::vector3df(player->getPosition().X, 0.5f * v, player->getPosition().Z));
		}*/
		
		PlayerState::update(player, core, time);
	}
};