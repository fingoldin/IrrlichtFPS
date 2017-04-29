#pragma once

#include "Actor.h"

enum E_WEAPON_TYPE
{
	EWT_PISTOL = 0,
	EWT_KNIFE,
	EWT_RIFLE,
	EWT_SHOTGUN,
	EWT_HEAVY,
	E_WEAPON_TYPE_COUNT
};

class Weapon : public Actor, public irr::scene::ISceneNode
{
public:
	Weapon(class Core * core, irr::s32 id);
	~Weapon();

	void OnRegisterSceneNode();
	void render() { }

	irr::u32 getMaterialCount() const { return 0; }

	void update(class Core * core, irr::u32 dt);

	const irr::core::aabbox3d<irr::f32>& getBoundingBox() const { return box; }

private:

	irr::core::aabbox3d<irr::f32> box;

	irr::u32 reloadTime;
	irr::u32 shotTime;

	bool canSpray;
	bool canFireWhileReloading;

	E_WEAPON_TYPE type;

	class Core * core;
};

