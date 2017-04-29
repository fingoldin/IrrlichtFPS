#pragma once

#include "InputMap.h"
#include "UpdateInputContext.h"

class LookFPContext : public UpdateInputContext
{
public:
	LookFPContext() : UpdateInputContext()
	{
	}

	~LookFPContext() { }

	void update(Core * core, irr::u32 dt)
	{

	}
};
