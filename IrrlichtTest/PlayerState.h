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

		core->debugMessage(name);
#endif
	}
	
	virtual void enter(Character * player)
	{
	}

	virtual void exit(Character * player) { }

	virtual void look(Character * player, double dx, double dy)
	{
		if (!player)
			return;

		player->setHorizontalAngle(player->getHorizontalAngle() + dx);

		double vangle = player->getVerticalAngle() + dy;

		if (vangle > LOOK_MAX_ANGLE * 2.0f && vangle < 360.0f - LOOK_MAX_ANGLE)
		{
			vangle = 360.0f - LOOK_MAX_ANGLE;
		}
		else if (vangle > LOOK_MAX_ANGLE && vangle < 360.0f - LOOK_MAX_ANGLE)
		{
			vangle = LOOK_MAX_ANGLE;
		}

		player->setVerticalAngle(vangle);
	}

	virtual void jump(Character * player) { }

	virtual void move(Character * player, int x, int y, double speed, irr::u32 dt)
	{
		irr::core::vector3df moveDir = player->getThirdPersonNode().root->getRotation().rotationToDirection();
		irr::core::vector3df strafeDir = -moveDir.crossProduct(irr::core::vector3df(0.0f, 1.0f, 0.0f));

		player->setPosition(player->getPosition() + speed * (y * moveDir + x * strafeDir).normalize() * ((double)dt / 1000.0f));
	}

protected:

	irr::u32 lastUpdateTime;

	irr::core::stringw name;
};

