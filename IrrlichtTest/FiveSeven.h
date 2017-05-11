#pragma once

#include "Core.h"

#include "Weapon.h"

#include "RestAnimation.h"
#include "SwitchAnimation.h"

#include "SemiAutoAnimation.h"

class FiveSeven : public Weapon
{
public:

	FiveSeven(Core * core, irr::s32 id = -1) : Weapon(core, id)
	{
		reloadTime = 1000;
		switchTime = 150;
		slot = EWS_SECONDARY;
		canFireWhileReloading = false;
		shotTime = 100;
		canSpray = false;

		if (!core)
			return;

		meshNode = core->getFPSmgr()->addMeshSceneNode(core->getFPSmgr()->getMesh("Assets\\1911\\m1911-handgun.obj"), this);
		meshNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
		meshNode->setPosition(irr::core::vector3df(-0.5f, 0.2f, -0.2f));
		meshNode->setScale(irr::core::vector3df(0.03f, 0.03f, 0.03f));
		meshNode->setRotation(irr::core::vector3df(0.0f, 90.0f, 0.0f));
		meshNode->setMaterialType((irr::video::E_MATERIAL_TYPE)Shader::getShader(EST_FANCY)->getID());

		anims[EWA_SWITCH] = new SwitchAnimation(switchTime);
		anims[EWA_REST] = new RestAnimation();
		anims[EWA_ATTACK] = new SemiAutoAnimation(shotTime);
	}

	~FiveSeven()
	{
	}
};