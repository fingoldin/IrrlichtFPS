#pragma once

#include "stdafx.h"
#include "Core.h"

#include "Command.h"

#include "EventInputContext.h"
#include "UpdateInputContext.h"

#include "InputMap.h"

class GameState
{
public:
	GameState()
	{
	}

	virtual ~GameState()
	{
		for (std::vector<UpdateInputContext*>::size_type i = 0; i != updateContexts.size(); i++)
			if (updateContexts[i])
				delete updateContexts[i];

		for (std::vector<EventInputContext*>::size_type i = 0; i != eventContexts.size(); i++)
			if (eventContexts[i])
				delete eventContexts[i];
	}

	virtual void enter(Core * core) = 0;
	virtual void exit(Core * core) = 0;

	virtual void update(Core * core, irr::u32 dt)
	{
		for (std::vector<UpdateInputContext*>::size_type i = 0; i != updateContexts.size(); i++)
			updateContexts[i]->update(core, dt);
	}

	virtual void handleEvent(Core * core, const irr::SEvent& event)
	{
		if(event.KeyInput.Key == irr::KEY_LCONTROL)
			OutputDebugString(L"event\n");

		bool handled = false;

		InputMap * inputMap = core->getInputMap();

		std::vector<Command*> commands;
		bool pressed = false;

		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			commands = inputMap->getCommands(event.KeyInput.Key);

			wchar_t debug[1024];
			wsprintf(debug, L"%d", commands.size());

			//OutputDebugString(debug);
			pressed = event.KeyInput.PressedDown;
		}
		else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT && event.MouseInput.Event < irr::EMIE_MOUSE_MOVED)
		{
			commands = inputMap->getMouseCommands((E_MOUSE_BUTTON)(event.MouseInput.Event % 3));
			pressed = core->getEventReceiver()->mouseButtonState((E_MOUSE_BUTTON)(event.MouseInput.Event % 3));
		}

		for (std::vector<Command*>::size_type i = 0; i != commands.size(); i++)
		{
			for (std::vector<EventInputContext*>::size_type j = 0; j != eventContexts.size(); j++)
			{
				if (eventContexts[j]->runCommand(core, commands[i], pressed))
				{
					handled = true;
					break;
				}
			}
		}


		if (!handled)
		{
			for (std::vector<EventInputContext*>::size_type i = 0; i != eventContexts.size(); i++)
				if (eventContexts[i]->handleEvent(core, event))
					break;
		}
	}

protected:

	void addEventContext(EventInputContext * c)
	{
		eventContexts.push_back(c);
	}

	void addUpdateContext(UpdateInputContext * c)
	{
		updateContexts.push_back(c);
	}

	std::vector<EventInputContext*> eventContexts;
	std::vector<UpdateInputContext*> updateContexts;
};

