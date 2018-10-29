#pragma once

#include "HitboxNode.h"

class SphereHitboxNode : public HitboxNode
{
public:
	SphereHitboxNode(irr::f32 pen, irr::f32 rad, irr::scene::ISceneNode * parent, irr::scene::ISceneManager * manager, irr::s32 id = -1) : radius(rad), HitboxNode(pen, parent, manager, id) { }
	virtual ~SphereHitboxNode() { }

	virtual bool testHit(class Core * core, irr::core::vector3df d, irr::core::vector3df p, irr::f32 s);

	irr::f32 getRadius() { return radius; }
	void setRadius(irr::f32 rad) { radius = rad; }

protected:

	irr::f32 radius;
};