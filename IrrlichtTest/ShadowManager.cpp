#include "stdafx.h"
#include "ShadowManager.h"


ShadowManager::ShadowManager()
{
}


ShadowManager::~ShadowManager()
{
}

void ShadowManager::generateMaps(irr::scene::ISceneManager * smgr)
{
	if (!smgr)
		return;

	irr::core::array<irr::scene::ISceneNode*> lights;
	smgr->getSceneNodesFromType(irr::scene::ESNT_LIGHT, lights);

	for (int i = 0; i < lights.size(); i++)
	{
	}
}