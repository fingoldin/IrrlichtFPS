#pragma once

#include "Actor.h"

enum E_INPUT_STATES
{
	EIS_FORWARD = 0,
	EIS_BACKWARD,
	EIS_RIGHT,
	EIS_LEFT,
	EIS_ATTACK,
	EIS_ATTACK2,
	EIS_CROUCH,
	EIS_WALK,
	E_INPUT_STATES_COUNT
};

enum E_WEAPON_SLOT
{
	EWS_PRIMARY = 0,
	EWS_SECONDARY,
	EWS_KNIFE,
	E_WEAPON_SLOT_COUNT
};

enum E_SELECTED_WEAPON
{
	ESW_PRIMARY = 0,
	ESW_SECONDARY,
	ESW_KNIFE,
	ESW_NONE,
	E_SELECTED_WEAPON_COUNT
};

enum E_SWITCH_WEAPON_TYPE
{
	ESWT_PRIMARY = 0,
	ESWT_SECONDARY,
	ESWT_KNIFE,
	ESWT_QUICK,
	E_SWITCH_WEAPON_TYPE_COUNT
};

enum E_CHARACTER_PART
{
	ECP_LEGS = 0,
	ECP_TORSO,
	ECP_LEFTLEG,
	ECP_RIGHTLEG,
	ECP_LEFTARM,
	ECP_RIGHTARM,
	ECP_HEAD,
	E_CHARACTER_PART_COUNT
};

class Character : public irr::scene::ISceneNode, public Actor
{
public:
	Character(class Core * core, irr::s32 id);
	~Character();

	void setFP(bool en, bool move);
	
	void OnRegisterSceneNode();
	void render() { }

	irr::u32 getMaterialCount() const { return 0; }

	void update(class Core * core, irr::u32 dt);

	const irr::core::aabbox3d<irr::f32>& getBoundingBox() const { return box; }

	class PlayerState * getState();
	void setState(class PlayerState * set);

	class EquipmentState * getEState();
	void setEState(class EquipmentState * set);

	void setInputState(E_INPUT_STATES state, bool value);

	bool getInputState(E_INPUT_STATES state) { return inputStates[state]; }

	class Weapon * getSelectedWeapon();

	bool setWeapon(E_SELECTED_WEAPON weapon);
	E_SELECTED_WEAPON getPreviousWeapon() { return previousWeapon; }
	void switchWeapons(E_SWITCH_WEAPON_TYPE weapon);

private:

	irr::core::aabbox3d<irr::f32> box;

	bool FPenabled;
	bool canMove;

	class Core * core;

	bool inputStates[E_INPUT_STATES_COUNT];

	std::vector<class PlayerState*> stateStack;
	const int maxStoreStates = 5;

	std::vector<class EquipmentState*> e_stateStack;
	const int maxStoreEStates = 5;

	class Weapon * weapons[E_WEAPON_SLOT_COUNT];
	E_SELECTED_WEAPON selectedWeapon;
	E_SELECTED_WEAPON previousWeapon;

	irr::scene::ISceneNode * partNodes[E_CHARACTER_PART_COUNT];
};

