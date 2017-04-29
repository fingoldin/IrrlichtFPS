#include "stdafx.h"

#include "Character.h"
#include "CEventReceiver.h"

#include "GameState.h"
#include "PlayState.h"

#include "InputMap.h"

#include "Command.h"

#include "GeneralManager.h"

#include "Core.h"

Core::Core(const wchar_t * name) : w_name(name)
{
	eventReceiver = DBG_NEW CEventReceiver(this);

	device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(640, 480), 16, false, false, false, eventReceiver);

	if (!device)
		return;

	device->setWindowCaption(name);

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	Command::initCommands();

	inputMap = DBG_NEW InputMap(this);

	manager = DBG_NEW GeneralManager(this);

	debugMes = NULL;
}

void Core::debugMessage(irr::core::stringw mes)
{
	if (debugMes)
	{
		debugMes->remove();
		debugMes = NULL;
	}

	debugMes = guienv->addStaticText(mes.c_str(), irr::core::rect<irr::s32>(10, 10, 260, 22), true);
}

void Core::begin()
{
	manager->startGame("hello");
}

void Core::end()
{

}

Character * Core::getPlayer()
{
	return manager->getPlayer();
}

Core::~Core()
{
	Command::cleanupCommands();

	for (std::vector<GameState*>::size_type i = 0; i != stateStack.size(); i++)
		if (stateStack[i])
			delete stateStack[i];

	if (inputMap)
		delete inputMap;

	if (manager)
		delete manager;

	if (eventReceiver)
		delete eventReceiver;

	device->drop();
}

void Core::setState(GameState * set)
{
	if (!set)
		return;

	GameState * prev = getState();

	if (prev)
		prev->exit(this);

	if (stateStack.size() == maxStoreStates)
	{
		delete stateStack[0];
		stateStack.erase(stateStack.begin());
	}

	stateStack.push_back(set);
	set->enter(this);
}

GameState * Core::getState()
{
	if (stateStack.size())
		return stateStack.back();

	return NULL;
}

void Core::update()
{
	if (device->isWindowActive())
	{
		irr::u32 time = device->getTimer()->getTime();
		lastFrameTime = (time - lastTime);
		lastTime = time;

		getState()->update(this, lastFrameTime);
	}
	else
		device->yield();
}


bool Core::isValid()
{
	if (done)
		return false;
	else
		return device->run();
}
