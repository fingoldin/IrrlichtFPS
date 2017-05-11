#pragma once

#include "Core.h"

#include "Animation.h"

#include "Character.h"

#include "Weapon.h"

class EquipmentState
{
public:
	EquipmentState() { }
	virtual ~EquipmentState() { }

	virtual void enter(Character * player, Core * core)
	{
		/*if (!player || !core)
			return;

		player->getFirstPersonNode().root->removeAnimators();
		player->getThirdPersonNode().root->removeAnimators();*/
	}

	virtual void exit(Character * player, Core * core) { }

	virtual void attack(Character * player) { }
	virtual void attack2(Character * player) { }

	virtual void switchWeapons(Character * player, E_SWITCH_WEAPON_TYPE weapon) { }

	virtual void update(Character * player, Core * core, irr::u32 time)
	{
#ifdef _DEBUG
		irr::core::stringw mes = "Equipment State: ";

		core->debugMessage(name);
#endif
	}

	virtual void setAnimation(Character * player, E_WEAPON_ANIM anim)
	{
		if (!player)
			return;

		player->getFirstPersonNode().weaponTag->removeAnimators();

		Weapon * weapon = player->getSelectedWeapon();

		if (weapon)
		{
			Animation * animation = weapon->getAnimation(anim);

			//OutputDebugString(L"Weaapon\n");

			if (animation)
			{
				animation->setFirstUpdate();
				player->getFirstPersonNode().weaponTag->addAnimator(animation);
			}
		}
	}

protected:

	irr::core::stringw name;
};