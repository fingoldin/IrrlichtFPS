#pragma once

#pragma once

#include "UpdateInputContext.h"
#include "EventInputContext.h"

#include "Command.h"

class ExitContext : public EventInputContext
{
public:
	ExitContext() : EventInputContext()
	{
	}

	~ExitContext()
	{
	}

	virtual bool runCommand(Core * core, Command * command, bool flag) { return false; }

	virtual bool handleEvent(Core * core, const irr::SEvent& event)
	{
		if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_ESCAPE && !event.KeyInput.PressedDown)
		{
			core->exitAll();
			return true;
		}

		return false;
	}
};