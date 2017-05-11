#pragma once

#include "PlayerState.h"

class DeadState : public PlayerState
{
public:
	DeadState() : PlayerState()
	{
		name = L"Dead";
	}

	~DeadState() { }
};