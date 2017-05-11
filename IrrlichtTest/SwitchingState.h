#pragma once

class SwitchingState : public CanSwitchState
{
public:
	SwitchingState();
	~SwitchingState();

	virtual void enter(Character * player, class Core * core);

	virtual void update(Character * player, class Core * core, irr::u32 time);

private:

	irr::u32 startTime;
};