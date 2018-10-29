#pragma once

#include "PlayerState.h"

class InAirState : public PlayerState
{
public:
	InAirState() : PlayerState() { }
	virtual ~InAirState() { }
};