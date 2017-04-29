#include "stdafx.h"
#include "GeneralManager.h"

#include "Core.h"
#include "Character.h"

#include "PlayState.h"

GeneralManager::GeneralManager(Core * core) : core(core)
{
	player = NULL;
}


GeneralManager::~GeneralManager()
{
}

void GeneralManager::startGame(irr::io::path map)
{
	if (player)
		delete player;
	player = NULL;

	if (core)
	{
		core->getSmgr()->clear();

		player = new Character(core, -1);
		player->setFP(true, true);
		player->setPosition(irr::core::vector3df(0.0, 0.0, 0.0));
		player->setRotation(irr::core::vector3df(0.0, 0.0, 0.0));

		irr::scene::IAnimatedMesh * mesh = core->getSmgr()->getMesh(map);

		if (mesh)
			core->getSmgr()->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	
		core->setState(DBG_NEW PlayState());
	}
}
