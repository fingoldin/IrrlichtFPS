#pragma once

#include "InputContext.h"

class UpdateInputContext : public InputContext
{
public:
	UpdateInputContext() : InputContext()
	{

	}

	virtual ~UpdateInputContext()
	{

	}

	virtual void update(Core * core, irr::u32 dt) { }
};