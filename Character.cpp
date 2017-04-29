#include "stdafx.h"

#include "Actor.h"

#include "Character.h"

#include "Core.h"

#include "PlayerState.h"
#include "RestingState.h"
#include "StandbyState.h"
#include "DeadState.h"

#include "Weapon.h"

#include "EquipmentState.h"

Character::Character(Core * core, irr::s32 id) : core(core), ISceneNode(core->getDevice()->getSceneManager()->getRootSceneNode(), core->getDevice()->getSceneManager(), id), Actor()
{
	FPenabled = false;
	canMove = false;

	for (int i = 0; i < E_INPUT_STATES_COUNT; i++)
		inputStates[i] = false;

	for (int i = 0; i < E_WEAPON_SLOT_COUNT; i++)
		weapons[i] = NULL;

	selectedWeapon = ESW_NONE;
	previousWeapon = ESW_NONE;

	setState(DBG_NEW RestingState());
	setEState(DBG_NEW StandbyState());

	//irr::scene::ISceneManagercore->getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.0, 5.0, 5.0));
}

Character::~Character()
{
	for(std::vector<PlayerState*>::size_type i = 0; i != stateStack.size(); i++)
		if(stateStack[i])
			delete stateStack[i];

	for (std::vector<EquipmentState*>::size_type i = 0; i != e_stateStack.size(); i++)
		if (e_stateStack[i])
			delete e_stateStack[i];
}

void Character::setFP(bool en, bool move)
{
	FPenabled = en;
	canMove = move;

	if (en)
	{
		setState(DBG_NEW RestingState());
		setEState(DBG_NEW StandbyState());
	}
}

Weapon * Character::getSelectedWeapon()
{
	if (selectedWeapon == ESW_NONE)
		return NULL;

	return weapons[selectedWeapon];
}

bool Character::setWeapon(E_SELECTED_WEAPON weapon)
{
	if (selectedWeapon == weapon)
		return false;
	
	if (weapon == ESW_NONE || weapons[weapon])
	{
		previousWeapon = selectedWeapon;
		selectedWeapon = weapon;
		
		return true;
	}

	return false;
}

void Character::switchWeapons(E_SWITCH_WEAPON_TYPE weapon)
{
	EquipmentState * state = getEState();

	if (state)
		state->switchWeapons(this, weapon);
}

void Character::setInputState(E_INPUT_STATES state, bool value)
{
	inputStates[state] = value;
}

void Character::OnRegisterSceneNode()
{
	if (isVisible())
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void Character::setState(PlayerState * set)
{
	if (!set)
		return;

	PlayerState * prev = getState();

	if (prev)
		prev->exit(this);

	if (stateStack.size() == maxStoreStates)
	{
		delete stateStack[0];
		stateStack.erase(stateStack.begin());
	}

	stateStack.push_back(set);
	set->enter(this);
}

PlayerState * Character::getState()
{
	if (stateStack.size())
		return stateStack.back();

	return NULL;
}

EquipmentState * Character::getEState()
{
	if (e_stateStack.size())
		return e_stateStack.back();

	return NULL;
}

void Character::setEState(EquipmentState * set)
{
	if (!set)
		return;

	EquipmentState * prev = getEState();

	if (prev)
		prev->exit(this);

	if (e_stateStack.size() == maxStoreEStates)
	{
		delete e_stateStack[0];
		e_stateStack.erase(e_stateStack.begin());
	}

	e_stateStack.push_back(set);
	set->enter(this);
}

void Character::update(Core * core, irr::u32 dt)
{
	getState()->update(this, core, dt);
}


