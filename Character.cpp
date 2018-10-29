#include "stdafx.h"

#include "Actor.h"

#include "Character.h"

#include "Core.h"

#include "Command.h"

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

#include "CharacterHitboxNode.h"

Character::Character(Core * core, irr::s32 id) : core(core), HitboxActor(), irr::IReferenceCounted()
{
	FPenabled = false;

	for (int i = 0; i < E_INPUT_STATES_COUNT; i++)
		inputStates[i] = false;

	for (int i = 0; i < E_WEAPON_SLOT_COUNT; i++)
		weapons[i] = NULL;

	selectedWeapon = ESW_NONE;
	previousWeapon = ESW_NONE;

	thirdPersonNode.root = NULL;
	thirdPersonNode.head = NULL;
	thirdPersonNode.leftArm = NULL;
	thirdPersonNode.leftLeg = NULL;
	thirdPersonNode.rightArm = NULL;
	thirdPersonNode.rightLeg = NULL;
	thirdPersonNode.torso = NULL;
	thirdPersonNode.weaponTag = NULL;

	firstPersonNode.arms = NULL;
	firstPersonNode.root = NULL;
	firstPersonNode.camera = NULL;
	firstPersonNode.weaponTag = NULL;

	thirdPersonNode.root = core->getSmgr()->addEmptySceneNode();
	firstPersonNode.root = core->getFPSmgr()->addEmptySceneNode();

	//thirdPersonNode.body = core->getSmgr()->addAnimatedMeshSceneNode(core->getSmgr()->getMesh("Assets\\man.obj"), thirdPersonNode.root);
	//thirdPersonNode.body->setScale(irr::core::vector3df(0.3f, 0.3f, 0.3f));
	//thirdPersonNode.body->setMaterialType((irr::video::E_MATERIAL_TYPE)Shader::getShader(EST_FANCY)->getID());

	thirdPersonNode.head = DBG_NEW CharacterHitboxNode(core, this, irr::core::vector3df(0.2f, 0.2f, 0.18f), 5.0f, 2.0f, thirdPersonNode.root, core->getSmgr());
	thirdPersonNode.head->setPosition(irr::core::vector3df(0.0f, 1.8f, 0.0f));
	hitboxes.push_back(thirdPersonNode.head);

	thirdPersonNode.torso = DBG_NEW CharacterHitboxNode(core, this, irr::core::vector3df(0.21f, 0.4f, 0.15f), 3.0f, 2.0f, thirdPersonNode.root, core->getSmgr());
	thirdPersonNode.torso->setPosition(irr::core::vector3df(0.0f, 1.15f, 0.0f));
	hitboxes.push_back(thirdPersonNode.torso);

	thirdPersonNode.leftLeg = DBG_NEW CharacterHitboxNode(core, this, irr::core::vector3df(0.1f, 0.35f, 0.1f), 2.0f, 1.5f, thirdPersonNode.root, core->getSmgr());
	thirdPersonNode.leftLeg->setPosition(irr::core::vector3df(-0.12f, 0.35f, 0.0f));
	hitboxes.push_back(thirdPersonNode.leftLeg);

	thirdPersonNode.rightLeg = DBG_NEW CharacterHitboxNode(core, this, irr::core::vector3df(0.1f, 0.35f, 0.1f), 2.0f, 1.5f, thirdPersonNode.root, core->getSmgr());
	thirdPersonNode.rightLeg->setPosition(irr::core::vector3df(0.12f, 0.35f, 0.0f));
	hitboxes.push_back(thirdPersonNode.rightLeg);

	thirdPersonNode.leftArm = DBG_NEW CharacterHitboxNode(core, this, irr::core::vector3df(0.1f, 0.3f, 0.1f), 2.0f, 1.5f, thirdPersonNode.root, core->getSmgr());
	thirdPersonNode.leftArm->setPosition(irr::core::vector3df(-0.35f, 1.2f, 0.0f));
	hitboxes.push_back(thirdPersonNode.leftArm);

	thirdPersonNode.rightArm = DBG_NEW CharacterHitboxNode(core, this, irr::core::vector3df(0.1f, 0.3f, 0.1f), 2.0f, 1.5f, thirdPersonNode.root, core->getSmgr());
	thirdPersonNode.rightArm->setPosition(irr::core::vector3df(0.35f, 1.2f, 0.0f));
	hitboxes.push_back(thirdPersonNode.rightArm);

	thirdPersonNode.weaponTag = core->getSmgr()->addEmptySceneNode(thirdPersonNode.rightArm);
	thirdPersonNode.weaponTag->setPosition(irr::core::vector3df(0.0f, -0.3f, 0.1f));

	firstPersonNode.camera = core->getFPSmgr()->addCameraSceneNode(firstPersonNode.root);
	firstPersonNode.camera->bindTargetAndRotation(true);
	firstPersonNode.camera->setNearValue(0.1f);

	firstPersonNode.arms = core->getFPSmgr()->addMeshSceneNode(core->getFPSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(0.2f, 0.6f, 0.2f)), firstPersonNode.root); // core->getSmgr()->addAnimatedMeshSceneNode(core->getSmgr()->getMesh("Assets\\arms.obj"), firstPersonNode.root);
	firstPersonNode.arms->setPosition(irr::core::vector3df(0.3f, -0.3f, 1.0f));
	firstPersonNode.arms->setRotation(irr::core::vector3df(90.0f, 0.0f, 0.0f));
	firstPersonNode.arms->setMaterialType((irr::video::E_MATERIAL_TYPE)Shader::getShader(EST_FANCY)->getID());
	//firstPersonNode.arms->setAutomaticCulling(3);

	firstPersonNode.weaponTag = core->getFPSmgr()->addEmptySceneNode(firstPersonNode.arms);
	firstPersonNode.weaponTag->setPosition(irr::core::vector3df(0.0f, -0.3f, 0.1f));

	setFP(false);

	setState(DBG_NEW RestingState(), 0);
	setEState(DBG_NEW StandbyState(), 0);

	irr::u32 time = core->getDevice()->getTimer()->getTime();

	addWeapon(DBG_NEW FiveSeven(core), time);
//	addWeapon(DBG_NEW M4A4(core), time);

	setVerticalAngle(0.0f);
	setHorizontalAngle(0.0f);

	health = PLAYER_MAX_HEALTH;

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

	if(thirdPersonNode.head)
		thirdPersonNode.head->drop();

	if (thirdPersonNode.leftArm)
		thirdPersonNode.leftArm->drop();

	if (thirdPersonNode.rightArm)
		thirdPersonNode.rightArm->drop();

	if (thirdPersonNode.leftLeg)
		thirdPersonNode.leftLeg->drop();

	if (thirdPersonNode.rightLeg)
		thirdPersonNode.rightLeg->drop();

	if (thirdPersonNode.torso)
		thirdPersonNode.torso->drop();
}

void Character::updateNodes()
{
	firstPersonNode.root->setRotation(irr::core::vector3df(vAngle, hAngle, 0.0f));
	firstPersonNode.root->setPosition(pos);

	thirdPersonNode.root->setRotation(irr::core::vector3df(0.0f, hAngle, 0.0f));
	thirdPersonNode.root->setPosition(pos);

	thirdPersonNode.rightArm->setRotation(irr::core::vector3df(vAngle - 90.0f, 0.0f, 0.0f));
	thirdPersonNode.rightArm->setPosition(irr::core::vector3df(0.35f, 1.35f - 0.15 * cos((vAngle - 90.0f) * irr::core::DEGTORAD), -0.15 * sin((vAngle - 90.0f) * irr::core::DEGTORAD)));

	if (firstPersonNode.camera)
		firstPersonNode.camera->setRotation(irr::core::vector3df(vAngle, hAngle, 0.0f));
}

void Character::setVerticalAngle(irr::f32 set)
{
	vAngle = set;

	updateNodes();
}

void Character::setHorizontalAngle(irr::f32 set)
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

bool Character::addWeapon(Weapon * weapon, irr::u32 time)
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
			switchWeapons((E_SWITCH_WEAPON_TYPE)slot, time);
		
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

void Character::switchWeapons(E_SWITCH_WEAPON_TYPE weapon, irr::u32 time)
{
	EquipmentState * state = getEState();

	if (state)
		state->switchWeapons(this, weapon, time);
}

void Character::setInputState(E_INPUT_STATES state, bool value, irr::u32 time)
{
	inputStates[state] = value;

	if (time)
		update(core, time);
}

void Character::setState(PlayerState * set, irr::u32 time)
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
	set->enter(this, time);
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

void Character::setEState(EquipmentState * set, irr::u32 time)
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
	set->enter(this, core, time);
}

void Character::update(Core * core, irr::u32 time)
{
	PlayerState * state = getState();
	EquipmentState * estate = getEState();

	this->core = core;

	if(state)
		state->update(this, core, time);

	if (estate)
		estate->update(this, core, time);
}

void Character::takeDamage(irr::f32 amount)
{
	health -= amount;

	if (health < 0.0f)
	{
		health = 0.0f;

		die();
	}

#ifdef _DEBUG
	irr::core::stringw mes(health);

	core->debugMessage(mes);
#endif
}

void Character::spawn()
{
	setFP(false);
	pushHitboxActor(this);
}

void Character::die()
{
	popHitboxActor(this);
}
