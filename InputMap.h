#pragma once

#include "Command.h"

#include "CEventReceiver.h"

class InputMap
{
public:
	InputMap(class Core * core);

	~InputMap();

	std::vector<Command*> getCommands(irr::EKEY_CODE key)
	{
		return keyMap[key];
	}

	std::vector<Command*> getMouseCommands(E_MOUSE_BUTTON button)
	{
		return mouseMap[button];
	}

	void bindCommand(irr::EKEY_CODE key, std::vector<Command*> commands);

	void bindMouseCommand(E_MOUSE_BUTTON button, std::vector<Command*> commands)
	{
		mouseMap[button] = commands;
	}

	void loadConfig(irr::core::stringc cfg);

private:

	irr::EKEY_CODE getKey(const char * name)
	{
		return irr::KEY_KEY_E;
	}

	E_MOUSE_BUTTON getMouseButton(const char * name)
	{
		return EMB_LEFT;
	}

	std::array<std::vector<Command*>, irr::KEY_KEY_CODES_COUNT> keyMap;
	std::array<std::vector<Command*>, E_MOUSE_BUTTON_COUNT> mouseMap;

	class Core * core;
};

