#pragma once

#include "Core.h"

#include "Weapon.h"

#include "SwitchAnimation.h"
#include "RestAnimation.h"
#include "FullAutoAnimation.h"

class M4A4 : public Weapon
{
public:

	M4A4(Core * core, irr::s32 id = -1) : Weapon(core, id)
	{
		reloadTime = 1000;
		switchTime = 200;
		slot = EWS_PRIMARY;
		canFireWhileReloading = false;
		shotTime = 60;
		canSpray = true;

		if (!core)
			return;

		meshNode = core->getFPSmgr()->addMeshSceneNode(core->getFPSmgr()->getMesh("Assets\\m4\\rifle-sig-552-commando.obj"), this);
		meshNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
		//meshNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		meshNode->setPosition(irr::core::vector3df(0.0f, -0.1f, -0.3f));
		meshNode->setScale(irr::core::vector3df(0.6f, 0.6f, 0.6f));
		meshNode->setRotation(irr::core::vector3df(0.0f, 90.0f, 0.0f));
		meshNode->setMaterialType((irr::video::E_MATERIAL_TYPE)Shader::getShader(EST_FANCY)->getID());

		anims[EWA_SWITCH] = new SwitchAnimation(switchTime);
		anims[EWA_REST] = new RestAnimation();
		anims[EWA_ATTACK] = new FullAutoAnimation(shotTime);
	}
};