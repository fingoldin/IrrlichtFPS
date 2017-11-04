#pragma once

#include "Actor.h"

#include "Animation.h"

#include "Character.h"

enum E_WEAPON_ANIM
{
	EWA_REST = 0,
	EWA_SWITCH,
	EWA_ATTACK,
	EWA_NOBULLETS,
	EWA_RELOAD,
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
	irr::u32 getReloadTime() { return reloadTime; }
	irr::u32 getActualReloadTime() { return actualReloadTime; }
	bool getCanSpray() { return canSpray; }

	int getMagCapacity() { return magCapacity; }
	int getMagBullets() { return magBullets; }
	int getTotalBullets() { return totalBullets; }

	bool fire();
	bool reload();

	Animation * getAnimation(E_WEAPON_ANIM anim) { return anims[anim]; }

protected:

	irr::u32 reloadTime;
	irr::u32 actualReloadTime;
	irr::u32 shotTime;
	irr::u32 switchTime;

	irr::f32 damageCoef;
	irr::f32 pStrength;

	int magCapacity;
	int magBullets;
	int totalBullets;

	bool canSpray;
	bool canFireWhileReloading;

	E_WEAPON_SLOT slot;

	class Core * core;

	bool active;
	class Character * owner;

	irr::scene::IMeshSceneNode * meshNode;

	Animation * anims[E_WEAPON_ANIM_COUNT];
};

