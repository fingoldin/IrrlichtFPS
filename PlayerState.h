#pragma once

#include "Core.h"
#include "Character.h"

class PlayerState
{
public:
	PlayerState()
	{
	}

	virtual ~PlayerState() { }

	virtual void update(Character * player, Core * core, irr::u32 dt)
	{
#ifdef _DEBUG
		irr::core::stringw mes = "PlayerState: ";

		core->debugMessage(name);
#endif
	}
	
	virtual void enter(Character * player)
	{
	}

	virtual void exit(Character * player) { }

	virtual void moveX(Character * player, int dir) { }
	virtual void moveY(Character * player, int dir) { }

	virtual void jump(Character * player) { }

protected:

	irr::core::stringw name;
};

