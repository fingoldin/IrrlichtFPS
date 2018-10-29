#pragma once

#include "GameState.h"
#include "MovingContext.h"
#include "LookFPContext.h"
#include "WeaponContext.h"
#include "AliveContext.h"
#include "ExitContext.h"

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

		addEventContext(DBG_NEW ExitContext());
	}

	~PlayState()
	{
	}

	void update(Core * core, irr::u32 time)
	{
		Character * player = core->getPlayer();

		Actor::updateAll(core, time);
		GameState::update(core, time);

		core->getDriver()->beginScene(true, true, irr::video::SColor(255, 100, 100, 100));

		//if (player)
		//	player->getFirstPersonNode().root->setVisible(false);

		core->getSmgr()->drawAll();

		core->getDriver()->clearZBuffer();

		core->getFPSmgr()->drawAll();

		//core->getDriver()->clearZBuffer();

		//if (player)
		//{
			//player->getFirstPersonNode().root->setVisible(true);
			//player->getFirstPersonNode().root->OnRegisterSceneNode();
			//core->getDriver()->setTransform(irr::video::ETS_WORLD, player->getFirstPersonNode().root->getAbsoluteTransformation());
			//player->getFirstPersonNode().root->render();
		//}

		core->getGuienv()->drawAll();

		core->getDriver()->endScene();
	}

	void enter(Core * core)
	{
		core->getDevice()->getCursorControl()->setVisible(false);
	}

	void exit(Core * core)
	{
		core->getDevice()->getCursorControl()->setVisible(true);
	}
};

