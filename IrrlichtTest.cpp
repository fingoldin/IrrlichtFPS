// IrrlichtTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Core.h"

#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

int main()
{
	Core * core = new Core(L"test");

	core->begin();

	while (core->isValid())
		core->update();

	core->end();

	delete core;

	_CrtDumpMemoryLeaks();

    return 0;
}

