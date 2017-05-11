#include "stdafx.h"
#include "Weapon.h"

#include "Character.h"

#include "Core.h"

Weapon::Weapon(Core * core, irr::s32 id) : core(core), irr::scene::ISceneNode(core->getDevice()->getSceneManager()->getRootSceneNode(), core->getDevice()->getSceneManager(), id), Actor()
{
	setOwner(NULL, false);

	for (int i = 0; i < E_WEAPON_ANIM_COUNT; i++)
		anims[i] = NULL;
}

void Weapon::setOwner(Character * player, bool act)
{
	owner = player;
	active = act;

	if (owner)
	{
		if (active)
			setParent(owner->getFirstPersonNode().weaponTag);
		else
			setParent(owner->getThirdPersonNode().weaponTag);
	}
	else
		setParent(0);
}

Weapon::~Weapon()
{
	for (int i = 0; i < E_WEAPON_ANIM_COUNT; i++)
		if (anims[i])
			anims[i]->drop();
}

void Weapon::OnRegisterSceneNode()
{
	if (isVisible())
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void Weapon::update(Core * core, irr::u32 time)
{

}