#include "GameState.h"

#include "Actor.h"

std::vector<Actor*> GameState::updateList;

void GameState::handleEvent(Core * core, const irr::SEvent& event)
{
	bool handled = false;

	InputMap * inputMap = core->getInputMap();

	std::vector<Command*> commands;
	bool pressed = false;

	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		commands = inputMap->getCommands(event.KeyInput.Key);
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