#include "stdafx.h"

#include "Core.h"

#include "InputMap.h"

InputMap::InputMap(Core * core) : core(core)
{
	for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
		keyMap[i] = std::vector<Command*>{};

	for (int i = 0; i < E_MOUSE_BUTTON_COUNT; i++)
		mouseMap[i] = std::vector<Command*>{};

	bindCommand(irr::KEY_SPACE, std::vector<Command*>{Command::getCommand("jump")});
	bindCommand(irr::KEY_KEY_A, std::vector<Command*>{Command::getCommand("left")});
	bindCommand(irr::KEY_KEY_D, std::vector<Command*>{Command::getCommand("right")});
	bindCommand(irr::KEY_KEY_W, std::vector<Command*>{Command::getCommand("forward")});
	bindCommand(irr::KEY_KEY_S, std::vector<Command*>{Command::getCommand("backward")});
	bindCommand(irr::KEY_CONTROL, std::vector<Command*>{Command::getCommand("crouch")});
	bindCommand(irr::KEY_SHIFT, std::vector<Command*>{Command::getCommand("walk")});

	bindCommand(irr::KEY_KEY_1, std::vector<Command*>{Command::getCommand("switch1")});
	bindCommand(irr::KEY_KEY_2, std::vector<Command*>{Command::getCommand("switch2")});
	bindCommand(irr::KEY_KEY_3, std::vector<Command*>{Command::getCommand("switch3")});
	bindCommand(irr::KEY_KEY_Q, std::vector<Command*>{Command::getCommand("qswitch")});
	bindCommand(irr::KEY_KEY_R, std::vector<Command*>{Command::getCommand("reload")});

	bindMouseCommand(EMB_LEFT, std::vector<Command*>{Command::getCommand("attack1")});
	bindMouseCommand(EMB_RIGHT, std::vector<Command*>{Command::getCommand("attack2")});
}

void InputMap::bindCommand(irr::EKEY_CODE key, std::vector<Command*> commands)
{
	if (key == irr::KEY_CONTROL)
	{
		keyMap[irr::KEY_LCONTROL] = commands;
		keyMap[irr::KEY_RCONTROL] = commands;
	}
	else if (key == irr::KEY_SHIFT)
	{
		keyMap[irr::KEY_LSHIFT] = commands;
		keyMap[irr::KEY_RSHIFT] = commands;
	}
	
	keyMap[key] = commands;
}

void InputMap::loadConfig(irr::core::stringc cfg)
{
	/*irr::io::IReadFile * file = core->getDevice()->getFileSystem()->createAndOpenFile(cfg);

	long size = file->getSize();
	char * buffer = DBG_NEW char[size + 1];
	file->read(buffer, size);
	buffer[size] = '\0';

	long last_start = 0;

	for (long i = 0; i < size; i++)
	{
		if (buffer[i] == '\n')
		{
			char key_name[128];
			key_name[0] = '\0';
			char command_name[256];
			command_name[0] = '\0';

			std::vector<Command*> command_list;

			int r = sscanf_s(buffer + last_start, "bind %127s %255s", key_name, 128, command_name, 256);

			if (r == 2)
			{
				Command * comm = Command::getCommand(command_name);

				if (comm)
					command_list.push_back(comm);
			}
			else if (r == 1 && strlen(key_name) > 0)
			{
				int r2 = sscanf_s(buffer + last_start + 6 + strlen(key_name), "\"%255[^\n]\"", command_name, 256);

				if (r2 == 1)
				{
					int l = strlen(command_name);

					char comm_name[256];
					comm_name[0] = '\0';
					int idx = 0;

					for (int j = 0; j < l; j++)
					{
						if (command_name[j] == ' ')
						{
							comm_name[idx] = '\0';
							idx = 0;

							Command * comm = Command::getCommand(comm_name);

							if (comm)
								command_list.push_back(comm);

							strcpy_s(comm_name, 256, "");
						}
						else
							comm_name[idx++] = command_name[j];
					}
				}
			}

			if (command_list.size())
			{
				irr::EKEY_CODE key = getKey(key_name);

				bindCommand(key, command_list);
			}

			last_start = i + 1;
		}
	}

	delete[] buffer;*/
}


InputMap::~InputMap()
{
}