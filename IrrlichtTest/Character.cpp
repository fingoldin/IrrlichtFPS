#include "stdafx.h"

#include "Actor.h"

#include "Character.h"

#include "Core.h"

#include "PlayerState.h"
#include "RestingState.h"
#include "StandbyState.h"
#include "DeadState.h"

#include "Shader.h"

#include "Weapon.h"

#include "Settings.h"

#include "EquipmentState.h"

#include "FiveSeven.h"
#include "M4A4.h"

Character::Character(Core * core, irr::s32 id) : core(core), Actor(), irr::IReferenceCounted()
{
	FPenabled = false;

	for (int i = 0; i < E_INPUT_STATES_COUNT; i++)
		inputStates[i] = false;

	for (int i = 0; i < E_WEAPON_SLOT_COUNT; i++)
		weapons[i] = NULL;

	selectedWeapon = ESW_NONE;
	previousWeapon = ESW_NONE;

	thirdPersonNode.root = NULL;
	thirdPersonNode.body = NULL;
	thirdPersonNode.weaponTag = NULL;

	firstPersonNode.arms = NULL;
	firstPersonNode.root = NULL;
	firstPersonNode.camera = NULL;
	firstPersonNode.weaponTag = NULL;

	thirdPersonNode.root = core->getSmgr()->addEmptySceneNode();
	firstPersonNode.root = core->getFPSmgr()->addEmptySceneNode();

	thirdPersonNode.body = core->getSmgr()->addEmptySceneNode(thirdPersonNode.root);// core->getSmgr()->addAnimatedMeshSceneNode(core->getSmgr()->getMesh("Assets\\man.obj"), thirdPersonNode.root);
	thirdPersonNode.body->setScale(irr::core::vector3df(0.01f, 0.01f, 0.01f));
	//thirdPersonNode.body->setMaterialType((irr::video::E_MATERIAL_TYPE)Shader::getShader(EST_FANCY)->getID());
	thirdPersonNode.weaponTag = core->getSmgr()->addEmptySceneNode(thirdPersonNode.body);

	firstPersonNode.camera = core->getFPSmgr()->addCameraSceneNode(firstPersonNode.root);
	firstPersonNode.camera->bindTargetAndRotation(true);
	firstPersonNode.camera->setNearValue(0.1f);

	firstPersonNode.arms = core->getFPSmgr()->addEmptySceneNode(firstPersonNode.root); // core->getSmgr()->addAnimatedMeshSceneNode(core->getSmgr()->getMesh("Assets\\arms.obj"), firstPersonNode.root);
	firstPersonNode.arms->setScale(irr::core::vector3df(0.2f, 0.2f, 0.2f));
	firstPersonNode.arms->setPosition(irr::core::vector3df(0.0f, -0.3f, 0.5f));
	firstPersonNode.arms->setRotation(irr::core::vector3df(0.0f, -90.0f, 0.0f));
	//firstPersonNode.arms->setMaterialType((irr::video::E_MATERIAL_TYPE)Shader::getShader(EST_FANCY)->getID());
	//firstPersonNode.arms->setAutomaticCulling(3);

	firstPersonNode.weaponTag = core->getFPSmgr()->addEmptySceneNode(firstPersonNode.arms);
	firstPersonNode.weaponTag->setPosition(irr::core::vector3df(-0.2f, 0.4f, -0.4f));

	setFP(false);

	setEState(DBG_NEW StandbyState());

	addWeapon(new FiveSeven(core));
	addWeapon(new M4A4(core));

	setVerticalAngle(0.0f);
	setHorizontalAngle(0.0f);

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

	for (int i = 0; i < E_WEAPON_SLOT_COUNT; i++)
		if (weapons[i])
			weapons[i]->drop();
}

void Character::updateNodes()
{
	firstPersonNode.root->setRotation(irr::core::vector3df(vAngle, hAngle, 0.0f));
	firstPersonNode.root->setPosition(pos);

	thirdPersonNode.root->setRotation(irr::core::vector3df(0.0f, hAngle, 0.0f));
	thirdPersonNode.root->setPosition(pos);

	if (firstPersonNode.camera)
		firstPersonNode.camera->setRotation(irr::core::vector3df(vAngle, hAngle, 0.0f));
}

void Character::setVerticalAngle(double set)
{
	vAngle = set;

	updateNodes();
}

void Character::setHorizontalAngle(double set)
{
	hAngle = set;

	updateNodes();
}

void Character::setPosition(const irr::core::vector3df& newPos)
{
	pos = newPos;

	updateNodes();
}

void Character::setFP(bool en)
{
	FPenabled = en;

	firstPersonNode.root->setVisible(en);
	thirdPersonNode.root->setVisible(!en);
}

bool Character::addWeapon(Weapon * weapon)
{
	if (!weapon)
		return false;

	E_WEAPON_SLOT slot = weapon->getSlot();

	if (weapons[slot] || slot >= E_WEAPON_SLOT_COUNT)
		return false;
	else
	{
		weapons[slot] = weapon;
		weapon->setOwner(this, false);

		if(core->getSettings()->queryBool(EBS_AUTOSWITCH))
			switchWeapons((E_SWITCH_WEAPON_TYPE)slot);
		
		return true;
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

		//OutputDebugString(L"here\n");

		if (previousWeapon != ESW_NONE)
			weapons[previousWeapon]->setOwner(this, false);

		if (selectedWeapon != ESW_NONE)
			weapons[selectedWeapon]->setOwner(this, true);
		
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
		prev->exit(this, core);

	if (e_stateStack.size() == maxStoreEStates)
	{
		delete e_stateStack[0];
		e_stateStack.erase(e_stateStack.begin());
	}

	e_stateStack.push_back(set);
	set->enter(this, core);
}

void Character::update(Core * core, irr::u32 time)
{
	PlayerState * state = getState();
	EquipmentState * estate = getEState();

	if(state)
		state->update(this, core, time);

	if (estate)
		estate->update(this, core, time);
}


