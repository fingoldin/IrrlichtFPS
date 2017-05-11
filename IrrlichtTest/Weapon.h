#pragma once

#include "Actor.h"

#include "Animation.h"

#include "Character.h"

enum E_WEAPON_ANIM
{
	EWA_REST = 0,
	EWA_SWITCH,
	EWA_ATTACK,
	E_WEAPON_ANIM_COUNT
};

class Weapon : public irr::scene::ISceneNode, public Actor
{
public:
	Weapon(class Core * core, irr::s32 id);
	~Weapon();

	void OnRegisterSceneNode();
	void render() { }

	irr::u32 getMaterialCount() const { return 0; }

	void update(class Core * core, irr::u32 time);

	const irr::core::aabbox3d<irr::f32>& getBoundingBox() const { return meshNode->getBoundingBox(); }

	virtual E_WEAPON_SLOT getSlot() { return slot; }

	bool getActive() { return active; }

	class Character * getOwner() { return owner; }
	void setOwner(class Character * player, bool act);

	irr::u32 getSwitchTime() { return switchTime; }
	irr::u32 getShotTime() { return shotTime; }
	bool getCanSpray() { return canSpray; }

	Animation * getAnimation(E_WEAPON_ANIM anim) { return anims[anim]; }

protected:

	irr::u32 reloadTime;
	irr::u32 shotTime;
	irr::u32 switchTime;

	bool canSpray;
	bool canFireWhileReloading;

	E_WEAPON_SLOT slot;

	class Core * core;

	bool active;
	class Character * owner;

	irr::scene::IMeshSceneNode * meshNode;

	Animation * anims[E_WEAPON_ANIM_COUNT];
};

