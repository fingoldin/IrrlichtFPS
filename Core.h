#pragma once

class Core
{
public:
	Core(const wchar_t * name);
	~Core();

	bool isValid();

	void update();
	void begin();
	void end();

	irr::IrrlichtDevice * getDevice() { return device;  }
	irr::scene::ISceneManager * getSmgr() { return smgr; }
	irr::video::IVideoDriver * getDriver() { return driver; }
	irr::gui::IGUIEnvironment * getGuienv() { return guienv;  }

	class CEventReceiver * getEventReceiver() { return eventReceiver; }

	class GameState * getState();
	void setState(class GameState * set);

	class InputMap * getInputMap() { return inputMap; }

	class Character * getPlayer();

	irr::u32 getLastFrameTime() { return lastFrameTime; }

	void debugMessage(irr::core::stringw mes);

private: 

	irr::u32 lastFrameTime;
	irr::u32 lastTime;

	irr::core::stringw w_name;

	bool done;

	irr::gui::IGUIElement * debugMes;

	irr::IrrlichtDevice * device;
	irr::scene::ISceneManager * smgr;
	irr::video::IVideoDriver * driver;
	irr::gui::IGUIEnvironment * guienv;

	class CEventReceiver * eventReceiver;

	class InputMap * inputMap;

	class GeneralManager * manager;

	std::vector<class GameState*> stateStack;
	const int maxStoreStates = 5;
};

