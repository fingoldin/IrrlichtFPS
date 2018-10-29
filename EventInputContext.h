#pragma once

#include <algorithm>

#include "InputContext.h"

#include "Character.h"

class EventInputContext : public InputContext
{
public:
	EventInputContext() : InputContext()
	{

	}

	virtual ~EventInputContext()
	{

	}

	virtual bool handleEvent(Core * core, const irr::SEvent& event)
	{
		return false;
	}

	virtual bool runCommand(Core * core, Command * command, bool flag, irr::u32 time)
	{
		if (!core || !command)
			return false;

		Character * player = core->getPlayer();

//		if (command->getType() == EIS_WALK)
//			OutputDebugString(L"Walk");

		if(player && core && command && std::find(validCommands.begin(), validCommands.end(), command->getType()) != validCommands.end())
		{
			//OutputDebugString(L"hello");
			command->run(player, flag, time);
			return true;
		}

		return false;
	}

protected:

	std::vector<E_COMMAND_TYPE> validCommands;
};
