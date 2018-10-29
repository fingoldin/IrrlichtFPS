#pragma once
#include "Actor.h"
#include "HitboxNode.h"

class HitboxActor : public Actor
{
public:
	HitboxActor() : Actor() { }
	virtual ~HitboxActor() { popHitboxActor(this); }

	virtual irr::f32 testHit(class Core * core, irr::core::vector3df d, irr::core::vector3df p, irr::f32 s)
	{
		for (std::vector<HitboxNode*>::size_type i = 0; i != hitboxes.size(); i++)
		{
			if (hitboxes[i]->testHit(core, d, p, s))
				return hitboxes[i]->getPenetrationCoef();
		}

		return 0.0f;
	}

protected:
	std::vector<HitboxNode*> hitboxes;

private:
	static std::vector<HitboxActor*> hitboxUpdateList;

public:
	static std::vector<HitboxActor*> getHitboxActors() { return hitboxUpdateList; }

protected:
	static void pushHitboxActor(HitboxActor * actor)
	{
		bool add = true;

		for (std::vector<HitboxActor*>::size_type i = 0; i != hitboxUpdateList.size(); i++)
		{
			if (hitboxUpdateList[i] == actor)
			{
				add = false;
				break;
			}
		}

		if(add)
			hitboxUpdateList.push_back(actor);
	}

	static void popHitboxActor(HitboxActor * actor)
	{
		for (std::vector<HitboxActor*>::size_type i = 0; i != hitboxUpdateList.size(); i++)
		{
			if (hitboxUpdateList[i] == actor)
			{
				hitboxUpdateList.erase(hitboxUpdateList.begin() + i);
				break;
			}
		}
	}
};
