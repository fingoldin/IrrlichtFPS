#include "stdafx.h"

#include "SphereHitboxNode.h"

#include "Core.h"

bool SphereHitboxNode::testHit(Core * core, irr::core::vector3df d, irr::core::vector3df p, irr::f32 s)
{
	irr::core::vector3df cp = getAbsolutePosition() - p;
	irr::f32 dot = cp.dotProduct(d);

	return (radius*radius > (cp.getLengthSQ() - dot*dot / d.getLengthSQ()));
}