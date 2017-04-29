#pragma once

#include "stdafx.h"

class Actor
{
public:
	Actor()
	{
		pushActor(this);
	}

	virtual ~Actor()
	{
		popActor(this);
	}

	virtual void update(class Core * core, irr::u32 dt) = 0;

	void setName(const irr::core::stringw& n) { name = n; }

	const irr::core::stringw& getName() const { return name; }

private:

	irr::core::stringw name;

private:
	static std::vector<Actor*> updateList;

public:
	static void updateAll(class Core * core, irr::u32 dt)
	{
		for (std::vector<Actor*>::size_type i = 0; i != updateList.size(); i++)
			updateList[i]->update(core, dt);
	}

protected:
	static void pushActor(Actor * actor)
	{
		updateList.push_back(actor);
	}

	static void popActor(Actor * actor)
	{
		for (std::vector<Actor*>::size_type i = 0; i != updateList.size(); i++)
		{
			if (updateList[i] == actor)
			{
				updateList.erase(updateList.begin() + i);
				break;
			}
		}
	}
};

