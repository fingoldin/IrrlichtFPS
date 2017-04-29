#include "stdafx.h"
#include "CEventReceiver.h"

#include "Core.h"

#include "GameState.h"

CEventReceiver::CEventReceiver(Core * core) : core(core)
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
		keyStates[i] = false;

	for (irr::u32 i = 0; i < E_MOUSE_BUTTON_COUNT; i++)
		mouseButtonStates[i] = false;
}


CEventReceiver::~CEventReceiver()
{
}

bool CEventReceiver::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		keyStates[event.KeyInput.Key] = event.KeyInput.PressedDown;
	else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			mouseButtonStates[EMB_LEFT] = true;
			break;
		case irr::EMIE_LMOUSE_LEFT_UP:
			mouseButtonStates[EMB_LEFT] = false;
			break;
		case irr::EMIE_RMOUSE_PRESSED_DOWN:
			mouseButtonStates[EMB_RIGHT] = true;
			break;
		case irr::EMIE_RMOUSE_LEFT_UP:
			mouseButtonStates[EMB_RIGHT] = false;
			break;
		case irr::EMIE_MMOUSE_PRESSED_DOWN:
			mouseButtonStates[EMB_MIDDLE] = true;
			break;
		case irr::EMIE_MMOUSE_LEFT_UP:
			mouseButtonStates[EMB_MIDDLE] = false;
			break;
		case irr::EMIE_MOUSE_MOVED:
			mouseState.pos.X = event.MouseInput.X;
			mouseState.pos.Y = event.MouseInput.Y;
			break;
		default:
			break;
		}
	}

	GameState * state = core->getState();

	if(state)
		state->handleEvent(core, event);

	return false;
}

bool CEventReceiver::keyState(irr::EKEY_CODE key)
{
	return keyStates[key];
}

bool CEventReceiver::mouseButtonState(E_MOUSE_BUTTON button)
{
	return mouseButtonStates[button];
}