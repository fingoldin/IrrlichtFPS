#pragma once

#include "CanSwitchState.h"

class SwitchingState : public CanSwitchState
{
public:
	SwitchingState() : CanSwitchState() { }
	~SwitchingState() { }
};