#include "stdafx.h"
#include "LegMovingState.h"

#include "Core.h"

#include "Character.h"

#include "Constants.h"

#include "CharacterHitboxNode.h"

LegMovingState::LegMovingState(irr::f32 ampli, irr::f32 sp)
{
	amplitude = ampli;
	phi = 0.0f;
	phiset = false;
	angle = 0.0f;
	lastAUpdateTime = 0;
	mspeed = sp;
}


LegMovingState::~LegMovingState()
{
}

void LegMovingState::updateLegs(Character * player, irr::u32 time)
{
	if (!player->getFP())
	{
		ThirdPersonNode n = player->getThirdPersonNode();

		if (n.leftLeg && n.rightLeg)
		{
			irr::u32 dt = time - lastAUpdateTime;
			lastAUpdateTime = time;

			player->getCore()->debugMessage(irr::core::stringw(phiset));

			if(angle > amplitude + 0.1f)
			{
				angle -= speed * ((irr::f32)dt / 1000.0f);

				phiset = false;
			}
			else if (angle < -amplitude - 0.1f)
			{
				angle += speed * ((irr::f32)dt / 1000.0f);

				phiset = false;
			}
			else if (!phiset)
			{
				if (angle > amplitude)
					angle = amplitude;
				else if (angle < -amplitude)
					angle = -amplitude;

				setPhi(time);
			}
			else
			{
				irr::f32 s = (2.0f * M_PI) * ((irr::f32)time / 1000.0f) * (speed / (4.0f * amplitude)) + phi;
				s = s - 2.0f * M_PI * floor(s / (2.0f * M_PI));
				angle = amplitude * sin(s);
			}

			setLegs(n);
		}
	}
}

void LegMovingState::setLegs(ThirdPersonNode n)
{
	n.leftLeg->setRotation(irr::core::vector3df(angle, 0.0f, 0.0f));
	n.rightLeg->setRotation(irr::core::vector3df(-angle, 0.0f, 0.0f));
}

void LegMovingState::enterLegs(Character * player, irr::u32 time)
{
	if (!player->getFP())
	{
		ThirdPersonNode n = player->getThirdPersonNode();

		if (n.leftLeg && n.rightLeg)
		{
			phiset = false;
			lastAUpdateTime = time;

			angle = n.leftLeg->getRotation().X;

			speed = 0.4f * amplitude / (2.0f * n.leftLeg->getSize().Y * sin(amplitude * irr::core::DEGTORAD) / mspeed);
			
			if (angle < 0.5f && angle > -0.5f)
			{
				angle = 0.0f;

				setPhi(time);
			}
			else if (angle < amplitude && angle > -amplitude)
				setPhi(time);

			setLegs(n);
		}
	}
}

void LegMovingState::setPhi(irr::u32 time)
{
	phi = asin(angle / amplitude) - (2.0f * M_PI) * ((irr::f32)time / 1000.0f) * (speed / (4.0f * amplitude));

	phiset = true;
}
