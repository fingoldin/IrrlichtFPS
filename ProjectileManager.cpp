#include "stdafx.h"
#include "ProjectileManager.h"

#include "Core.h"

#include "Character.h"

#include "HitboxActor.h"

ProjectileManager::ProjectileManager(Core * c) : core(c), irr::IReferenceCounted()
{
}


ProjectileManager::~ProjectileManager()
{
}

void ProjectileManager::hitScan(Character * player, irr::core::vector3df d, irr::core::vector3df p, irr::f32 s, irr::f32 pStrength)
{
	std::vector<HitboxActor*> actors = HitboxActor::getHitboxActors();

	irr::f32 tPen = pStrength;

	for (std::vector<HitboxActor*>::size_type i = 0; i != actors.size(); i++)
	{
		if (actors[i] != (HitboxActor*)player)
		{
			tPen -= actors[i]->testHit(core, d, p, s);

			if (tPen < 0.0f)
				break;
		}
	}
}
