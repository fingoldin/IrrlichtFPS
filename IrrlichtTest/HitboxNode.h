#pragma once

#include "stdafx.h"

class HitboxNode : public irr::scene::ISceneNode
{
public:
	HitboxNode(irr::f32 pen, irr::scene::ISceneNode * parent, irr::scene::ISceneManager * manager, irr::s32 id = -1) : penetrationCoef(pen), irr::scene::ISceneNode(parent, manager, id) { }
	
	virtual ~HitboxNode() { }

	virtual bool testHit(class Core * core, irr::core::vector3df d, irr::core::vector3df p, irr::f32 s) = 0;

	virtual irr::f32 getPenetrationCoef() { return penetrationCoef; }
	virtual void setPenetrationCoef(irr::f32 pen) { penetrationCoef = pen; }

protected:

	irr::f32 penetrationCoef;
};

