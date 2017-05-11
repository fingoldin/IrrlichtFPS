#pragma once

#include "stdafx.h"

#include "Core.h"

#include "Shader.h"

class PerPixelShader : public Shader
{
public:
	PerPixelShader(Core * core) : Shader(core)
	{
		type = EST_PERPIXEL;

		vertex =
			"#version 440 core\n"\
			"layout (location = 0) in vec3 position;\n"\
			"layout (location = 1) in vec3 normal;\n"\
			"layout (location = 2) in vec3 color;\n"\
			"\n"\
			"out vec3 FragColor;\n"\
			"out vec3 FragPos;\n"\
			"out vec3 FragNormal;\n"\
			"\n"\
			"uniform mat4 model;\n"\
			"uniform mat4 view;\n"\
			"uniform mat4 projection;\n"\
			"uniform mat4 normalMat;\n"\
			"\n"\
			"void main()\n"\
			"{\n"\
			"	gl_Position = projection * view * model * vec4(position, 1.0);\n"\
			"	FragColor = color;\n"\
			"	FragPos = vec3(model * vec4(position, 1.0));\n"\
			"	FragNormal = normalize(mat3(normalMat) * normal);\n"\
			"}\n";

		pixel =
			"#version 440 core\n"\
			"in vec3 FragPos;\n"\
			"in vec3 FragNormal;\n"\
			"in vec3 FragColor;\n"\
			"\n"\
			"out vec4 color;\n"\
			"\n"\
			"void main()\n"\
			"{\n"\
			"	color = vec4(FragNormal, 1.0f);\n"\
			"}";

		createShader();
	}

	~PerPixelShader() { }

	virtual void OnSetConstants(irr::video::IMaterialRendererServices * services, irr::s32 userData)
	{
		if (!core || id < 1)
			return;

		irr::video::IVideoDriver * driver = services->getVideoDriver();

		irr::core::matrix4 model = driver->getTransform(irr::video::ETS_WORLD);
		irr::core::matrix4 view = driver->getTransform(irr::video::ETS_VIEW);
		irr::core::matrix4 projection = driver->getTransform(irr::video::ETS_PROJECTION);

		irr::core::matrix4 normalMat;
		model.getInverse(normalMat);
		normalMat.getTransposed(normalMat);

		services->setVertexShaderConstant("model", model.pointer(), 16);
		services->setVertexShaderConstant("view", view.pointer(), 16);
		services->setVertexShaderConstant("projection", projection.pointer(), 16);

		services->setVertexShaderConstant("normalMat", normalMat.pointer(), 16);
	}

	virtual void createShader()
	{
		if (!core)
			return;

		irr::video::IGPUProgrammingServices * gpu = core->getDriver()->getGPUProgrammingServices();

		id = gpu->addHighLevelShaderMaterial(vertex.c_str(), "main", irr::video::EVST_VS_4_0,
			pixel.c_str(), "main", irr::video::EPST_PS_4_0,
			this, irr::video::EMT_SOLID, irr::video::EGSL_DEFAULT);
	}
};