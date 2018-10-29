#pragma once
class LegMovingState
{
public:
	LegMovingState(irr::f32 amplitude, irr::f32 speed);
	~LegMovingState();

	virtual void enterLegs(class Character * player, irr::u32 time);
	virtual void updateLegs(class Character * player, irr::u32 time);

protected:

	void setPhi(irr::u32 time);

	void setLegs(struct ThirdPersonNode n);

	// phase constant for sin function (initial condition)
	irr::f32 phi;

	irr::f32 amplitude;

	// meters per second
	irr::f32 mspeed;

	// degrees per second
	irr::f32 speed;

	irr::f32 angle;

	irr::u32 lastAUpdateTime;

	bool phiset;
};

