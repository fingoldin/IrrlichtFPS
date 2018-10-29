#pragma once

enum E_SHADER_TYPE
{
	EST_PERPIXEL = 0,
	EST_PERPIXEL_OLD,
	EST_FANCY,
	E_SHADER_TYPE_COUNT
};

class Shader : public irr::video::IShaderConstantSetCallBack
{
public:
	Shader(class Core * core);
	virtual ~Shader();

	irr::s32 getID() { return id; }

protected:

	E_SHADER_TYPE type;
	irr::s32 id;

	irr::core::stringc vertex;
	irr::core::stringc pixel;

	class Core * core;

	virtual void createShader()
	{
		if (!core)
			return;

		irr::video::IGPUProgrammingServices * gpu = core->getDriver()->getGPUProgrammingServices();

		id = gpu->addHighLevelShaderMaterial(vertex.c_str(), pixel.c_str(), this);
	}

private:

	static Shader * shaders[E_SHADER_TYPE_COUNT];

public:

	static Shader * getShader(E_SHADER_TYPE type) { return shaders[type]; }

	static void initShaders(class Core * core);

	static void cleanupShaders();
};

