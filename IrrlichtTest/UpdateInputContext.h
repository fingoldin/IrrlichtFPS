#pragma once

#include "InputContext.h"

class UpdateInputContext : public InputContext
{
public:
	UpdateInputContext() : InputContext()
	{
		lastUpdateTime = 0;
	}

	virtual ~UpdateInputContext()
	{

	}

	virtual void update(Core * core, irr::u32 time) { }

protected:

	irr::u32 lastUpdateTime;
};