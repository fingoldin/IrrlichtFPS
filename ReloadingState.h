#pragma once

#include "CanSwitchState.h"

class ReloadingState : public CanSwitchState
{
public:
	ReloadingState() : CanSwitchState() { }
	~ReloadingState() { }
};