#include "stdafx.h"

#include "Character.h"
#include "CEventReceiver.h"

#include "GameState.h"
#include "PlayState.h"

#include "InputMap.h"

#include "Command.h"

#include "GeneralManager.h"

#include "Settings.h"

#include "Shader.h"

#include "ShadowManager.h"

#include "Core.h"

Core::Core(const wchar_t * name) : w_name(name)
{
	eventReceiver = DBG_NEW CEventReceiver(this);

	irr::SIrrlichtCreationParameters params;
	params.DriverType = irr::video::EDT_OPENGL;
	params.EventReceiver = eventReceiver;
	params.WindowSize = irr::core::dimension2d<irr::u32>(1920, 1080);
	params.AntiAlias = 16;
	params.Fullscreen = false;
	params.Vsync = false;
	params.Stencilbuffer = true;
	
	//device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 16, false, false, false, eventReceiver);

	device = irr::createDeviceEx(params);
	
	if (!device)
	{
		printf("Could not create device, exiting\n");
		return;
	}

	device->setWindowCaption(name);

	driver = device->getVideoDriver();

	if (!driver->queryFeature(irr::video::EVDF_ARB_FRAGMENT_PROGRAM_1) &&
		!driver->queryFeature(irr::video::EVDF_ARB_VERTEX_PROGRAM_1))
	{
		device->getLogger()->log("WARNING: Vertex or fragment shaders disabled because of missing driver/hardware support, exiting.");
		shouldExit = true;
		return;
	}

	if (driver->queryFeature(irr::video::EVDF_RENDER_TO_TARGET))
	{
		device->getLogger()->log("WARNING: Render to texture not supported.");
		shadowManager = NULL;
	}
	else
		shadowManager = DBG_NEW ShadowManager();

	smgr = device->getSceneManager();
	fpSmgr = smgr->createNewSceneManager(false);
	guienv = device->getGUIEnvironment();

	Command::initCommands();

	Shader::initShaders(this);

	inputMap = DBG_NEW InputMap(this);

	manager = DBG_NEW GeneralManager(this);

	settings = DBG_NEW Settings();

	debugMes = NULL;

	shouldExit = false;

	if (device->getFileSystem()->changeWorkingDirectoryTo("C:\\Users\\Vassy Lord Of Arda\\Documents\\Visual Studio 2015\\Projects\\IrrlichtPlayground\\IrrlichtTest"))
		device->getLogger()->log("Changed directory");

	//smgr->addHillPlaneMesh("testhill", irr::core::dimension2df(10.0f, 10.0f), irr::core::dimension2d<irr::u32>(10, 10), 0, 2.0f, irr::core::dimension2d<irr::f32>(5.0f, 5.0f));
}

void Core::debugMessage(irr::core::stringw mes)
{
	if (debugMes)
	{
		debugMes->remove();
		debugMes = NULL;
	}

	if(guienv)
		debugMes = guienv->addStaticText(mes.c_str(), irr::core::rect<irr::s32>(10, 10, 260, 22), true);
}

void Core::begin()
{
	if(manager)
		manager->startGame("hello");
}

void Core::end()
{

}

Character * Core::getPlayer()
{
	if(manager)
		return manager->getPlayer();
	
	return NULL;
}

Core::~Core()
{
	Command::cleanupCommands();
	Shader::cleanupShaders();

	for (std::vector<GameState*>::size_type i = 0; i != stateStack.size(); i++)
		if (stateStack[i])
			delete stateStack[i];

	if (inputMap)
		delete inputMap;

	if (manager)
		delete manager;

	if (eventReceiver)
		delete eventReceiver;

	if (settings)
		delete settings;

	if (shadowManager)
		delete shadowManager;

	if(device)
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
	if (!device)
		return;

	if (device->isWindowActive())
	{
		irr::u32 time = device->getTimer()->getTime();
		lastFrameTime = (time - lastTime);
		lastTime = time;

		irr::core::stringw title = "FPS: ";
		title += driver->getFPS();

		device->setWindowCaption(title.c_str());

		getState()->update(this, time);
	}
	else
		device->yield();
}


bool Core::isValid()
{
	if (shouldExit)
		return false;
	else if (device)
		return device->run();
	else
		return false;
}
