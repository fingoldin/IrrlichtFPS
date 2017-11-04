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

	virtual void enter(Character * player, Core * core, irr::u32 time)
	{
		/*if (!player || !core)
			return;

		player->getFirstPersonNode().root->removeAnimators();
		player->getThirdPersonNode().root->removeAnimators();*/
	}

	virtual void reload(Character * player, irr::u32 time) { }

	virtual void exit(Character * player, Core * core) { }

	virtual void attack(Character * player, irr::u32 time) { }
	virtual void attack2(Character * player, irr::u32 time) { }

	virtual void switchWeapons(Character * player, E_SWITCH_WEAPON_TYPE weapon, irr::u32 time);

	virtual void update(Character * player, Core * core, irr::u32 time)
	{
#ifdef _DEBUG
		irr::core::stringw mes = "Equipment State: ";

		//core->debugMessage(name);
#endif
	}

	virtual void setAnimation(Character * player, E_WEAPON_ANIM anim, irr::u32 time)
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
				animation->setFirstUpdate(time);
				player->getFirstPersonNode().weaponTag->addAnimator(animation);
			}
		}
	}

protected:

	irr::core::stringw name;
};