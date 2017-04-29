#pragma once

#include "PlayerState.h"
#include "Character.h"

class CrouchingState
{
public:
	CrouchingState() { }
	virtual ~CrouchingState() { }

	void jump(Character * player) { }
};