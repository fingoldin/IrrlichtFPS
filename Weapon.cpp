#include "stdafx.h"
#include "Weapon.h"

#include "Core.h"

Weapon::Weapon(Core * core, irr::s32 id) : core(core), irr::scene::ISceneNode(core->getDevice()->getSceneManager()->getRootSceneNode(), core->getDevice()->getSceneManager(), id), Actor()
{

}


Weapon::~Weapon()
{
}

void Weapon::OnRegisterSceneNode()
{
	if (isVisible())
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void Weapon::update(Core * core, irr::u32 dt)
{

}