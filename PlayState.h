#pragma once

#include "GameState.h"
#include "MovingContext.h"
#include "LookFPContext.h"
#include "WeaponContext.h"
#include "AliveContext.h"

#include "Actor.h"

class PlayState : public GameState
{
public:
	PlayState() : GameState()
	{
		addEventContext(DBG_NEW MovingContext());
		addUpdateContext(DBG_NEW LookFPContext());

		addEventContext(DBG_NEW WeaponContext());
		addUpdateContext(DBG_NEW AliveContext());
	}

	~PlayState()
	{
	}

	void update(Core * core, irr::u32 dt)
	{
		Actor::updateAll(core, dt);
		GameState::update(core, dt);

		core->getDriver()->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));

		core->getSmgr()->drawAll();
		core->getGuienv()->drawAll();

		core->getDriver()->endScene();
	}

	void enter(Core * core)
	{
		core->getPlayer()->setFP(true, true);
	}

	void exit(Core * core)
	{
		core->getPlayer()->setFP(false, false);
	}
};

