#pragma once

#include "PlayerState.h"

class AliveState : public PlayerState
{
public:
	AliveState() : PlayerState() { }

	virtual ~AliveState() { }
};