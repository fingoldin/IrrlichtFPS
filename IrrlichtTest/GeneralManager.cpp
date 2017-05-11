#include "stdafx.h"
#include "GeneralManager.h"

#include "Core.h"
#include "Character.h"

#include "Shader.h"

#include "PlayState.h"

GeneralManager::GeneralManager(Core * core) : core(core)
{
	player = NULL;

	sun = NULL;
}


GeneralManager::~GeneralManager()
{
	if (player)
		player->drop();
}

void GeneralManager::startGame(irr::io::path map)
{
	if (player)
		player->drop();

	player = NULL;

	if (core)
	{
		core->getSmgr()->clear();

		//core->getSmgr()->addMeshSceneNode(core->getSmgr()->getMesh("testhill"));

		bool g = false;

		auto manMesh = core->getSmgr()->getMesh("Model\\Man_model1910.obj");
		auto man2Mesh = core->getSmgr()->getMesh("Assets\\man.obj");
		auto cubeMesh = core->getSmgr()->getMesh("Assets\\cube.obj");
		auto wallsMesh = core->getSmgr()->getMesh("Assets\\walls.obj");

		auto cube = core->getSmgr()->addMeshSceneNode(cubeMesh, 0, -1, irr::core::vector3df(-5.0f, 0.6f, 8.0f));
		//cube->setMaterialType((irr::video::E_MATERIAL_TYPE)(Shader::getShader(EST_FANCY)->getID()));

		//cubeMesh->drop();

		player = new Character(core, -1);
		player->setFP(true);
		player->setPosition(irr::core::vector3df(0.0f, 1.3f, 0.0f));
		//player->setRotation(irr::core::vector3df(0.0f, 0.0f, 0.0f));
		//player->setScale(irr::core::vector3df(2.5f, 2.5f, 2.5f));

		Command::getCommand(ECT_SPAWN)->run(player, true);

		irr::scene::IAnimatedMesh * mesh = core->getSmgr()->getMesh(map);

		if (mesh)
			core->getSmgr()->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	
		irr::scene::ICameraSceneNode * camera = player->getFirstPersonNode().camera;

		if (camera)
			core->getSmgr()->setActiveCamera(camera);

		auto sunParent = core->getSmgr()->addEmptySceneNode();
		sunParent->setPosition(irr::core::vector3df(10.0f, 10.0f, 10.0f));

		sun = core->getSmgr()->addLightSceneNode(sunParent);
		irr::video::SLight light;
		light.DiffuseColor = irr::video::SColorf(1.0f, 1.0f, 1.0f);
		light.SpecularColor = irr::video::SColorf(0.9f, 0.9f, 0.9f);
		light.AmbientColor = irr::video::SColorf(0.1f, 0.1f, 0.1f);
		light.Direction = irr::core::vector3df(-1.0f, 1.0f, -1.0f);
		//light.Direction = irr::core::vector3df(10.9f, 1.0f, -0.1f).normalize();
		light.Type = irr::video::ELT_DIRECTIONAL;

		core->getSmgr()->setAmbientLight(irr::video::SColorf(0.1f, 0.1f, 0.1f));

		sun->setLightData(light);
		sun->setRadius(1000.0f);
		//sun->enableCastShadow();
		sun->setPosition(irr::core::vector3df(10.0f, 10.0f, 10.0f));
		//Ssun->setRotation(irr::core::vector3df(-0.5f, -10.0f, -0.9f).getHorizontalAngle().normalize());


		//core->getFPSmgr()->getRootSceneNode()->addChild(sun);

		//core->getSmgr()->addLightSceneNode(0, irr::core::vector3df(10.0f, 10.0f, 10.0f));

		irr::scene::IMeshSceneNode * man = core->getSmgr()->addMeshSceneNode(man2Mesh);
	
		//manMesh->drop();

		auto anim = core->getSmgr()->createRotationAnimator(irr::core::vector3df(0.0f, 0.5f, 0.0f));
		if (anim)
		{
			man->addAnimator(anim);
			anim->drop();
		}

		man->setMaterialType((irr::video::E_MATERIAL_TYPE)(Shader::getShader(EST_FANCY)->getID()));
		man->setScale(irr::core::vector3df(0.3f, 0.3f, 0.3f));
		man->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
		man->getMaterial(0).Shininess = 2.0f;
		man->setMaterialFlag(irr::video::EMF_GOURAUD_SHADING, false);
		//man->addShadowVolumeSceneNode();

		irr::scene::IMesh * floor = core->getSmgr()->getGeometryCreator()->createPlaneMesh(irr::core::dimension2d<irr::f32>(2.0f, 2.0f), irr::core::dimension2d<irr::u32>(10.0f, 10.0f));
		if (floor)
		{
			auto floorNode = core->getSmgr()->addMeshSceneNode(floor);
			//floorNode->getMaterial(0).DiffuseColor = irr::video::SColor(255, 12, 12, 255);
			floor->drop();
		}

		//core->getSmgr()->addCameraSceneNodeFPS(0, 100.0f, 0.01f);

		core->setState(DBG_NEW PlayState());
	}
}
