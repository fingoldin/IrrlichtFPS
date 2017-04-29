#include "stdafx.h"

#include "Character.h"

#include "Command.h"

#include "MoveForward.h"
#include "Attack.h"
#include "Attack2.h"
#include "Die.h"
#include "Jump.h"
#include "MoveBackward.h"
#include "MoveLeft.h"
#include "MoveRight.h"
#include "Quickswitch.h"
#include "SwitchPrimary.h"
#include "SwitchSecondary.h"
#include "SwitchKnife.h"
#include "Crouch.h"
#include "Walk.h"

Command * Command::commands[E_COMMAND_TYPE_COUNT];

void Command::initCommands()
{
	for (size_t i = 0; i < E_COMMAND_TYPE_COUNT; i++)
		commands[i] = NULL;

	commands[ECT_FORWARD] = DBG_NEW MoveForward();
	commands[ECT_BACKWARD] = DBG_NEW MoveBackward();
	commands[ECT_LEFT] = DBG_NEW MoveLeft();
	commands[ECT_RIGHT] = DBG_NEW MoveRight();
	commands[ECT_ATTACK] = DBG_NEW Attack();
	commands[ECT_ATTACK2] = DBG_NEW Attack2();
	commands[ECT_DIE] = DBG_NEW Die();
	commands[ECT_JUMP] = DBG_NEW Jump();
	commands[ECT_QUICKSWITCH] = DBG_NEW Quickswitch();
	commands[ECT_SWITCHPRIMARY] = DBG_NEW SwitchPrimary();
	commands[ECT_SWITCHSECONDARY] = DBG_NEW SwitchSecondary();
	commands[ECT_SWITCHKNIFE] = DBG_NEW SwitchKnife();
	commands[ECT_CROUCH] = DBG_NEW Crouch();
	commands[ECT_WALK] = DBG_NEW Walk();
}

void Command::cleanupCommands()
{
	for (size_t i = 0; i < E_COMMAND_TYPE_COUNT; i++)
		if (commands[i])
			delete commands[i];
}

Command * Command::getCommand(irr::core::stringc name)
{
	for (size_t i = 0; i < E_COMMAND_TYPE_COUNT; i++)
		if (commands[i] && commands[i]->getName() == name)
			return commands[i];

	return NULL;
}