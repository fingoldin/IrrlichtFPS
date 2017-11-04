#pragma once
#include "SphereHitboxNode.h"

class CharacterHitboxNode : public SphereHitboxNode
{
public:
	CharacterHitboxNode(class Core * c, class Character * own, irr::core::vector3df si, irr::f32 dam, irr::f32 pen, irr::scene::ISceneNode * parent, irr::scene::ISceneManager * manager, irr::s32 id = -1);
	
	~CharacterHitboxNode();

	virtual bool testHit(class Core * core, irr::core::vector3df d, irr::core::vector3df p, irr::f32 s);

	irr::core::vector3df getSize() { return size; }
	void setSize(irr::core::vector3df s);

	virtual void render();

	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;

	virtual void OnRegisterSceneNode();

	virtual irr::video::SMaterial& getMaterial(irr::u32 i);

	virtual irr::u32 getMaterialCount() const;

protected:
	class Character * owner;

	class Core * core;

	irr::core::vector3df size;

	irr::scene::IMesh * mesh;

	irr::f32 damageCoef;
};

