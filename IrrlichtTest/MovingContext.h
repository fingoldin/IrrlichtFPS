#pragma once

#include "InputMap.h"
#include "EventInputContext.h"

class MovingContext : public EventInputContext
{
public:
	MovingContext() : EventInputContext()
	{
		validCommands.push_back(ECT_FORWARD);
		validCommands.push_back(ECT_BACKWARD);
		validCommands.push_back(ECT_LEFT);
		validCommands.push_back(ECT_RIGHT);
		validCommands.push_back(ECT_JUMP);
		validCommands.push_back(ECT_CROUCH);
		validCommands.push_back(ECT_WALK);
	}

	~MovingContext() { }

	//void update(Core * core)
	//{
		/*CEventReceiver * rec = core->getEventReceiver();
		InputMap * map = core->getInputMap();

		if (rec->keyState(map->getStateKey(ISTATES_FORWARD)))
			core->getPlayer()->move(this->moveSens, true);
		else if (rec->keyState(map->getStateKey(ISTATES_BACKWARD)))
			core->getPlayer()->move(-this->moveSens, true);

		if (rec->keyState(map->getStateKey(ISTATES_STRAFE_RIGHT)))
			core->getPlayer()->move(this->moveSens, false);
		else if (rec->keyState(map->getStateKey(ISTATES_STRAFE_LEFT)))
			core->getPlayer()->move(-this->moveSens, false);*/
	//}

	//bool handleEvent(Core * core, const irr::SEvent& event)
	//{
		/*Character * player = core->getPlayer();

		if (event.EventType == irr::EET_KEY_INPUT_EVENT && player)
		{
			CEventReceiver * rec = core->getEventReceiver();
			InputMap * map = core->getInputMap();*/



			/*bool up = rec->keyState(map->getStateKey(ISTATES_FORWARD));
			bool down = rec->keyState(map->getStateKey(ISTATES_BACKWARD));
			bool left = rec->keyState(map->getStateKey(ISTATES_STRAFE_LEFT));
			bool right = rec->keyState(map->getStateKey(ISTATES_STRAFE_RIGHT));

			bool crouch = rec->keyState(map->getStateKey(ISTATES_CROUCH));
			bool duck = rec->keyState(map->getStateKey(ISTATES_DUCK));

			player->move((int)up - (int)down, (int)right - (int)left, crouch, duck);*/
		//}

	//	return false;
	//}

};