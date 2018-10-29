#pragma once

#include "Core.h"

#include "Weapon.h"

#include "RestAnimation.h"
#include "SwitchAnimation.h"
#include "ReloadAnimation.h"
#include "SemiAutoAnimation.h"

class FiveSeven : public Weapon
{
public:

	FiveSeven(Core * core, irr::s32 id = -1) : Weapon(core, id)
	{
		reloadTime = 1000;
		actualReloadTime = 900;
		switchTime = 150;
		slot = EWS_SECONDARY;
		canFireWhileReloading = false;
		shotTime = 100;
		canSpray = false;
		magCapacity = 10;
		totalBullets = 50;
		magBullets = 10;
		damageCoef = 0.6f;
		pStrength = 20.0f;

		if (!core)
			return;

		meshNode = core->getFPSmgr()->addMeshSceneNode(core->getFPSmgr()->getMesh("Assets/1911/m1911-handgun.obj"), this);
		meshNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
		meshNode->setPosition(irr::core::vector3df(0.0f, 0.0f, 0.0f));
		meshNode->setScale(irr::core::vector3df(0.005f, 0.005f, 0.005f));
		meshNode->setRotation(irr::core::vector3df(90.0f, 0.0f, 0.0f));
		meshNode->setMaterialType((irr::video::E_MATERIAL_TYPE)Shader::getShader(EST_FANCY)->getID());

		anims[EWA_SWITCH] = DBG_NEW SwitchAnimation(switchTime);
		anims[EWA_REST] = DBG_NEW RestAnimation();
		anims[EWA_ATTACK] = DBG_NEW SemiAutoAnimation(shotTime);
		//anims[EWA_NOBULLETS] = DBG_NEW RestAnimation();
		anims[EWA_RELOAD] = DBG_NEW ReloadAnimation(reloadTime);
	}

	~FiveSeven()
	{
	}
};
