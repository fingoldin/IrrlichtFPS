#pragma once
class GeneralManager
{
public:
	GeneralManager(class Core * core);
	~GeneralManager();

	void startGame(irr::io::path map);

	class Character * getPlayer() { return player; }

private:

	class Core * core;
	class Character * player;
};

