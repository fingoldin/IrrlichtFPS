#pragma once

#include "UpdateInputContext.h"
#include "EventInputContext.h"

class WeaponContext : public EventInputContext
{
public:
	WeaponContext() : EventInputContext()
	{
		validCommands.push_back(ECT_RELOAD);
		validCommands.push_back(ECT_SWITCHPRIMARY);
		validCommands.push_back(ECT_SWITCHSECONDARY);
		validCommands.push_back(ECT_SWITCHKNIFE);
		validCommands.push_back(ECT_QUICKSWITCH);
		validCommands.push_back(ECT_ATTACK);
		validCommands.push_back(ECT_ATTACK2);
	}

	~WeaponContext()
	{

	}
};