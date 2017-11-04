#pragma once

#include "Core.h"
#include "Character.h"

#include "Constants.h"

class PlayerState
{
public:
	PlayerState()
	{
		lastUpdateTime = 0;
		startTime = 0;
	}

	virtual ~PlayerState() { }

	virtual void update(Character * player, Core * core, irr::u32 time)
	{
		if (!core || !player)
			return;

		FirstPersonNode fp = player->getFirstPersonNode();

		if (fp.camera)
		{
			//player->updateAbsolutePosition();
			fp.root->updateAbsolutePosition();
			fp.arms->updateAbsolutePosition();
			fp.camera->updateAbsolutePosition();
			fp.weaponTag->updateAbsolutePosition();
			fp.camera->setRotation(fp.camera->getRotation());
		}

#ifdef _DEBUG
		irr::core::stringw mes = "PlayerState: ";

		//core->debugMessage(name);
#endif
	}
	
	virtual void enter(Character * player, irr::u32 time)
	{
		lastUpdateTime = time;

		startTime = time;
	}

	virtual void exit(Character * player) { }

	virtual void look(Character * player, irr::f32 dx, irr::f32 dy)
	{
		if (!player)
			return;

		player->setHorizontalAngle(player->getHorizontalAngle() + dx);

		irr::f32 vangle = player->getVerticalAngle() + dy;

		/*if (vangle > LOOK_MAX_ANGLE * 2.0f && vangle < 360.0f - LOOK_MAX_ANGLE)
		{
			vangle = 360.0f - LOOK_MAX_ANGLE;
		}
		else if (vangle > LOOK_MAX_ANGLE && vangle < 360.0f - LOOK_MAX_ANGLE)
		{
			vangle = LOOK_MAX_ANGLE;
		}*/

		player->setVerticalAngle(vangle);
	}

	virtual void jump(Character * player, irr::u32 time) { }

	virtual void move(Character * player, int x, int y, irr::f32 speed, irr::u32 dt)
	{
		irr::core::vector3df moveDir = player->getThirdPersonNode().root->getRotation().rotationToDirection();
		irr::core::vector3df strafeDir = -moveDir.crossProduct(irr::core::vector3df(0.0f, 1.0f, 0.0f));

		player->setPosition(player->getPosition() + speed * ((irr::f32)y * moveDir + (irr::f32)x * strafeDir).normalize() * ((irr::f32)dt / 1000.0f));
	}

protected:

	irr::u32 lastUpdateTime;
	irr::u32 startTime;

	irr::core::stringw name;
};

