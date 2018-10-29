#pragma once

class ProjectileManager : public irr::IReferenceCounted
{
public:
	ProjectileManager(class Core * c);
	~ProjectileManager();

	void hitScan(class Character * player, irr::core::vector3df d, irr::core::vector3df p, irr::f32 s, irr::f32 pStrength);

private:

	class Core * core;
};

