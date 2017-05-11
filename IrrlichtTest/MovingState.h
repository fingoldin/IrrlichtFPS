#pragma once

#include "OnGroundState.h"

class MovingState : public OnGroundState
{
public:
	MovingState() : OnGroundState() { }
	virtual ~MovingState() { }
};