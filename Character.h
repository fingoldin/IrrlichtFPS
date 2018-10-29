#pragma once

#include "HitboxActor.h"
#include "CharacterHitboxNode.h"

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

/*enum E_CHARACTER_PART
{
	ECP_LEGS = 0,
	ECP_TORSO,
	ECP_LEFTLEG,
	ECP_RIGHTLEG,
	ECP_LEFTARM,
	ECP_RIGHTARM,
	ECP_HEAD,
	E_CHARACTER_PART_COUNT
};*/

struct FirstPersonNode
{
	irr::scene::ISceneNode * root;
	irr::scene::ISceneNode * arms;
	irr::scene::ICameraSceneNode * camera;
	irr::scene::ISceneNode * weaponTag;
};

struct ThirdPersonNode
{
	irr::scene::ISceneNode * root;
	CharacterHitboxNode * leftLeg;
	CharacterHitboxNode * rightLeg;
	CharacterHitboxNode * torso;
	CharacterHitboxNode * rightArm;
	CharacterHitboxNode * leftArm;
	CharacterHitboxNode * head;
	irr::scene::ISceneNode * weaponTag;
};

class Character : public HitboxActor, public irr::IReferenceCounted
{
public:
	Character(class Core * core, irr::s32 id);
	~Character();

	void setFP(bool en);

	bool getFP() { return FPenabled; }

	//irr::u32 getMaterialCount() const { return 0; }

	//const irr::core::aabbox3d<irr::f32>& getBoundingBox() const { return thirdPersonNode.root->getBoundingBox(); }

	class PlayerState * getState();
	void setState(class PlayerState * set, irr::u32 time);

	class EquipmentState * getEState();
	void setEState(class EquipmentState * set, irr::u32 time);

	void setInputState(E_INPUT_STATES state, bool value, irr::u32 time);

	bool getInputState(E_INPUT_STATES state) { return inputStates[state]; }

	class Weapon * getSelectedWeapon();

	bool setWeapon(E_SELECTED_WEAPON weapon);
	E_SELECTED_WEAPON getPreviousWeapon() { return previousWeapon; }
	void switchWeapons(E_SWITCH_WEAPON_TYPE weapon, irr::u32 time);

	FirstPersonNode getFirstPersonNode() { return firstPersonNode; }
	ThirdPersonNode getThirdPersonNode() { return thirdPersonNode; }

	void setVerticalAngle(irr::f32 set);
	irr::f32 getVerticalAngle() { return vAngle; }

	void setHorizontalAngle(irr::f32 set);
	irr::f32 getHorizontalAngle() { return hAngle; }

	bool addWeapon(Weapon * weapon, irr::u32 time);

	virtual void update(class Core * core, irr::u32 time);

	void setPosition(const irr::core::vector3df& newPos);
	irr::core::vector3df getPosition() { return pos; }

	void takeDamage(irr::f32 amount);

	class Core * getCore() { return core; }

	void spawn();
	void die();

private:

	void updateNodes();

	bool FPenabled;

	class Core * core;

	bool inputStates[E_INPUT_STATES_COUNT];

	std::vector<class PlayerState*> stateStack;
	const int maxStoreStates = 5;

	std::vector<class EquipmentState*> e_stateStack;
	const int maxStoreEStates = 5;

	class Weapon * weapons[E_WEAPON_SLOT_COUNT];
	E_SELECTED_WEAPON selectedWeapon;
	E_SELECTED_WEAPON previousWeapon;


	ThirdPersonNode thirdPersonNode;
	FirstPersonNode firstPersonNode;

	irr::f32 vAngle;
	irr::f32 hAngle;

	irr::f32 health;

	irr::core::vector3df pos;
};

