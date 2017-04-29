#pragma once

enum E_MOUSE_BUTTON
{
	EMB_LEFT = 0,
	EMB_RIGHT,
	EMB_MIDDLE,
	E_MOUSE_BUTTON_COUNT
};

class CEventReceiver : public irr::IEventReceiver
{
public:
	CEventReceiver(class Core * core);
	~CEventReceiver();

	bool OnEvent(const irr::SEvent& event);

	bool keyState(irr::EKEY_CODE key);

	bool mouseButtonState(E_MOUSE_BUTTON button);

	struct SMouseState
	{
		irr::core::position2di pos;
		SMouseState() : pos(0, 0) { }
	} mouseState;

private:

	irr::IrrlichtDevice * device;

	class Core * core;

	bool keyStates[irr::KEY_KEY_CODES_COUNT];
	bool mouseButtonStates[E_MOUSE_BUTTON_COUNT];
};

