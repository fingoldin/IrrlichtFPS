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
	irr::scene::ISceneManager * getFPSmgr() { return fpSmgr; }
	irr::video::IVideoDriver * getDriver() { return driver; }
	irr::gui::IGUIEnvironment * getGuienv() { return guienv;  }

	class CEventReceiver * getEventReceiver() { return eventReceiver; }

	class Settings * getSettings() { return settings; }

	class GameState * getState();
	void setState(class GameState * set);

	class InputMap * getInputMap() { return inputMap; }

	class Character * getPlayer();

	class GeneralManager * getManager() { return manager; }

	class ProjectileManager * getProjectileManager() { return projectileManager; }

	irr::u32 getLastFrameTime() { return lastFrameTime; }

	void debugMessage(irr::core::stringw mes);

	void exitAll() { shouldExit = true; }

private: 

	irr::u32 lastFrameTime;
	irr::u32 lastTime;

	irr::core::stringw w_name;

	bool shouldExit;

	irr::gui::IGUIElement * debugMes;

	irr::IrrlichtDevice * device;
	irr::scene::ISceneManager * smgr;
	irr::scene::ISceneManager * fpSmgr;
	irr::video::IVideoDriver * driver;
	irr::gui::IGUIEnvironment * guienv;

	class CEventReceiver * eventReceiver;

	class InputMap * inputMap;

	class Settings * settings;

	class GeneralManager * manager;
	class ProjectileManager * projectileManager;
	class ShadowManager * shadowManager;

	std::vector<class GameState*> stateStack;
	const int maxStoreStates = 5;
};

