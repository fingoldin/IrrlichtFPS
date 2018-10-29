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
		actualReloadTime = 900;
		switchTime = 200;
		slot = EWS_PRIMARY;
		canFireWhileReloading = false;
		shotTime = 60;
		canSpray = true;
		magCapacity = 30;
		totalBullets = 120;
		magBullets = 30;
		damageCoef = 1.0f;
		pStrength = 50.0f;

		if (!core)
			return;


		meshNode = core->getFPSmgr()->addMeshSceneNode(core->getFPSmgr()->getMesh("Assets/m4/rifle-sig-552-commando.obj"), this);
		meshNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
		//meshNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		meshNode->setPosition(irr::core::vector3df(0.0f, -0.1f, -0.3f));
		meshNode->setScale(irr::core::vector3df(0.15f, 0.15f, 0.15f));
		meshNode->setRotation(irr::core::vector3df(-90.0f, 0.0f, 0.0f));
		//meshNode->setMaterialType((irr::video::E_MATERIAL_TYPE)Shader::getShader(EST_FANCY)->getID());

		anims[EWA_SWITCH] = DBG_NEW SwitchAnimation(switchTime);
		anims[EWA_REST] = DBG_NEW RestAnimation();
		anims[EWA_ATTACK] = DBG_NEW FullAutoAnimation(shotTime);
		//anims[EWA_NOBULLETS] = new RestAnimation();
		anims[EWA_RELOAD] = DBG_NEW ReloadAnimation(reloadTime);
	}
};
