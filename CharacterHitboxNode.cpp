#include "stdafx.h"

#include "CharacterHitboxNode.h"

#include "Character.h"

#include "Core.h"

CharacterHitboxNode::CharacterHitboxNode(Core * c, Character * own, irr::core::vector3df si, irr::f32 dam, irr::f32 pen, irr::scene::ISceneNode * parent, irr::scene::ISceneManager * manager, irr::s32 id) : damageCoef(dam), owner(own), core(c), mesh(NULL), SphereHitboxNode(pen, si.getLength(), parent, manager, id)
{
	setSize(si);
}

CharacterHitboxNode::~CharacterHitboxNode()
{
	if (mesh)
		mesh->drop();
}

void CharacterHitboxNode::setSize(irr::core::vector3df s)
{
	size = s;

	if (mesh)
		mesh->drop();

	mesh = core->getSmgr()->getGeometryCreator()->createCubeMesh(2.0f * size);
}

bool CharacterHitboxNode::testHit(Core * core, irr::core::vector3df d, irr::core::vector3df p, irr::f32 s)
{
	bool res = SphereHitboxNode::testHit(core, d, p, s);
	
	if (res)
		owner->takeDamage(damageCoef * s);

//	if (res)
//		OutputDebugString(L"Hit\n");
//	else
//		OutputDebugString(L"No hit\n");

	return res;
}

void CharacterHitboxNode::render()
{
	irr::video::IVideoDriver* driver = core->getDriver();
	driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);

	irr::video::SMaterial mat = mesh->getMeshBuffer(0)->getMaterial();

	driver->setMaterial(mat);
	driver->drawMeshBuffer(mesh->getMeshBuffer(0));
}


const irr::core::aabbox3d<irr::f32>& CharacterHitboxNode::getBoundingBox() const
{
	return mesh->getMeshBuffer(0)->getBoundingBox();
}

irr::u32 CharacterHitboxNode::getMaterialCount() const
{
	return 1;
}

irr::video::SMaterial& CharacterHitboxNode::getMaterial(irr::u32 i)
{
	return mesh->getMeshBuffer(0)->getMaterial();
}

void CharacterHitboxNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}
