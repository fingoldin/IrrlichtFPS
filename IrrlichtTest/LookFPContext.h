#pragma once

#include "InputMap.h"
#include "UpdateInputContext.h"
#include "PlayerState.h"

#include "Settings.h"

class LookFPContext : public UpdateInputContext
{
public:
	LookFPContext() : UpdateInputContext()
	{
		firstUpdate = true;
	}

	~LookFPContext() { }

	void update(Core * core, irr::u32 time)
	{
		if (lastUpdateTime == 0)
			lastUpdateTime = time;

		irr::u32 dt = time - lastUpdateTime;
		lastUpdateTime = time;

		if (!core)
			return;

		Character * player = core->getPlayer();

		if (!player)
			return;

		Settings * settings = core->getSettings();

		if (!settings)
			return;

		double rotateSpeed = settings->queryDouble(EDS_MOUSE_SENS);

		//irr::scene::ICameraSceneNode * camera = player->getFPCamera();

		irr::gui::ICursorControl * control = core->getDevice()->getCursorControl();

		if (/*!camera || */!control)
			return;

		irr::core::vector2df pos = control->getRelativePosition();

		if (firstUpdate)
		{
			//camera->updateAbsolutePosition();

			control->setPosition(0.5f, 0.5f);
			centerCursor = pos = control->getRelativePosition();

			firstUpdate = false;
		}

		else if (pos != centerCursor)	
		{
			PlayerState * state = player->getState();

			if (state)
				state->look(player, -rotateSpeed * (centerCursor.X - pos.X), -rotateSpeed * (centerCursor.Y - pos.Y));

			/*irr::core::vector3df target = (camera->getTarget() - camera->getAbsolutePosition());
			irr::core::vector3df relativeRotation = target.getHorizontalAngle();

			relativeRotation.Y -= (centerCursor.X - pos.X) * rotateSpeed;
			relativeRotation.X -= (centerCursor.Y - pos.Y) * rotateSpeed;

			if (relativeRotation.X > maxVerticalAngle * 2 && relativeRotation.X < 360.0f - maxVerticalAngle)
			{
				relativeRotation.X = 360.0f - maxVerticalAngle;
			}
			else if (relativeRotation.X > maxVerticalAngle && relativeRotation.X < 360.0f - maxVerticalAngle)
			{
				relativeRotation.X = maxVerticalAngle;
			}

			target.set(0, 0, irr::core::max_(1.f, pos.getLength()));

			irr::core::matrix4 mat;
			mat.setRotationDegrees(irr::core::vector3df(relativeRotation.X, relativeRotation.Y, 0));
			mat.transformVect(target);

			camera->setTarget(camera->getPosition() + target);*/

			control->setPosition(0.5f, 0.5f);
			centerCursor = control->getRelativePosition();
			pos = centerCursor;
		}

		irr::video::IVideoDriver* driver = core->getSmgr()->getVideoDriver();
		irr::core::vector2d<irr::u32> mousepos(irr::u32(control->getPosition().X), irr::u32(control->getPosition().Y));
		irr::core::rect<irr::u32> screenRect(0, 0, driver->getScreenSize().Width, driver->getScreenSize().Height);

		if (!screenRect.isPointInside(mousepos))
		{
			control->setPosition(0.5f, 0.5f);
			centerCursor = control->getRelativePosition();
			pos = centerCursor;
		}

		//irr::core::stringw mes(dt);

		//core->debugMessage(mes);
	}

private:

	bool firstUpdate;
	irr::core::vector2df centerCursor;
};
