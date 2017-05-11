#pragma once
class ShadowManager
{
public:
	ShadowManager();
	~ShadowManager();

	void generateMaps(irr::scene::ISceneManager * smgr);

private:

	irr::core::map<irr::scene::ILightSceneNode*, irr::video::ITexture*> shadowMaps;
};

