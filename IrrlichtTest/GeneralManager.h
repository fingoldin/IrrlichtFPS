#pragma once
class GeneralManager
{
public:
	GeneralManager(class Core * core);
	~GeneralManager();

	void startGame(irr::io::path map);

	class Character * getPlayer() { return player; }

	irr::scene::ILightSceneNode * getSun() { return sun; }

private:

	class Core * core;
	class Character * player;

	irr::scene::ILightSceneNode * sun;
};

