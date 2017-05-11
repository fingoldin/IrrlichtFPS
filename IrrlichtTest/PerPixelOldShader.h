#pragma once

#include "stdafx.h"

#include "Constants.h"

#include "Core.h"

#include "GeneralManager.h"

#include "Shader.h"

class PerPixelOldShader : public Shader
{
public:
	PerPixelOldShader(Core * core) : Shader(core)
	{
		type = EST_PERPIXEL_OLD;

		vertex =
			"out vec3 FragColor;\n"\
			"out vec3 FragPos;\n"\
			"out vec3 FragNormal;\n"\
			
			"uniform mat4 model;\n"\
			"uniform mat4 view;\n"\
			"uniform mat4 projection;\n"\
			"uniform float gTime;"
			
			"float rand(vec2 co, float s) {\n"\
			"	return fract(sin(dot(co * s, vec2(12.9898, 78.233))) * 43758.5453);\n"\
			"}"\
			
			"void main()\n"\
			"{"\
			"	gl_Position = projection * view * model * gl_Vertex;\n"\
			"	gl_FrontColor = gl_BackColor = gl_Color;//(1.0 - 0.6 * rand(vec2(gl_Vertex) * vec2(gl_Normal), gTime / 10.0))+\n"\
			"	FragPos = vec3(model * gl_Vertex);\n"\
			"	FragNormal = gl_Normal;\n"\
			"}";

		pixel =
			"in vec3 FragPos;\n"\
			"in vec3 FragNormal;\n"\
			"in vec3 FragColor;\n"\

			"uniform vec3 SunAmbience;\n"\
			"uniform vec3 SunDiffuse;\n"\
			"uniform vec3 SunSpecular;\n"\

			"uniform vec3 SunDir;\n"\
			"uniform vec3 CamPos;\n"\

			"uniform float Shininess;\n"\

			"uniform mat4 normalMat;\n"\

			"void main()\n"\
			"{"\
			"	vec3 normal = normalize(mat3(normalMat) * FragNormal);\n"\
			"	vec3 viewDir = normalize(CamPos - FragPos);\n"\
			"	vec3 lightDir = normalize(-SunDir);\n"\
			"	vec3 halfwayDir = normalize(lightDir + viewDir);\n"\

			"	vec3 color = vec3(0.0, 0.0, 0.0);\n"\

			"	color += SunAmbience;\n"\
			"	color += SunDiffuse * max(dot(normal, lightDir), 0.0);\n"\
			"	color += SunSpecular * pow(max(dot(normal, halfwayDir), 0.0), Shininess);\n"\

			"	gl_FragColor = vec4(color, 1.0) * gl_Color;\n"\
			"}";

		/*pixel =
			"in vec3 FragPos;\n"\
			"in vec3 FragNormal;\n"\
			"in vec3 FragColor;\n"\

			"uniform Material material;\n"\

			"uniform Light lights[" + MAX_SHADER_LIGHTS + "];\n"\
			"uniform int numLights;\n"\

			"uniform vec3 CamPos\n"\

			"out vec4 color;\n"\

			"void main()\n"\
			"{"\

			"	color = vec3(0.0, 0.0, 0.0);\n"\
			"	vec3 normal = normalize(FragNormal);\n"\
			"	vec3 viewDir = normalize(CamPos - FragPos);\n"\

			"	for(int i = 0; i < numLights && lights < " + MAX_SHADER_LIGHTS + "; i++)\n"\
			"	{"\
			"		vec3 lightDir = normalize(lights[i].position - FragPos);\n"\

			"		if(type == 1)\n"\
			"			lightDir = normalize(-light.position);\n"\

			"		vec3 halfwayDir = normalize(lightDir + viewDir);\n"\

			"		float dist = length(light.position - worldPos);\n"\
			
			"		float ambient = lights[i].params.x * material.params.x;\n"\
			"		float diffuse = lights[i].params.y * max(dot(normal, lightDir), 0.0) * material.params.y;\n"\
			"		float specular = lights[i].params.z * pow(max(dot(normal, halfwayDir), 0.0), material.shininess) * material.params.z;\n"\
			
			"		float attenuation = min(1.0 / (lights[i].attenuation.x + lights[i].attenuation.y * dist + lights[i].attenuation.z * dist * dist), 1.0);\n"\

			"		color += attenuation * (ambient + diffuse + specular);\n"\
			"	}"\

			"	color = gl_Color * max(dot(FragNormal, vec3(-0.2, -0.2, -0.5)), 0.0);\n"\
			
			"}";*/

		createShader();
	}

	~PerPixelOldShader() { }

	virtual void OnSetMaterial(const irr::video::SMaterial& material)
	{
		this->material = material;
	}

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

		services->setPixelShaderConstant("normalMat", normalMat.pointer(), 16);

		irr::f32 time = (irr::f32)core->getDevice()->getTimer()->getTime() / 1000.0f;

		services->setVertexShaderConstant("gTime", &time, 1);

		irr::scene::ISceneNode * camera = core->getSmgr()->getActiveCamera();
		if (camera)
		{
			irr::core::vector3df pos = camera->getAbsolutePosition();
			services->setPixelShaderConstant("CamPos", reinterpret_cast<irr::f32*>(&pos), 3);
		}

		irr::scene::ILightSceneNode * sun = core->getManager()->getSun();
		if (sun)
		{
			irr::video::SLight data = sun->getLightData();

			services->setPixelShaderConstant("SunAmbient", reinterpret_cast<irr::f32*>(&data.AmbientColor), 3);
			services->setPixelShaderConstant("SunDiffuse", reinterpret_cast<irr::f32*>(&data.DiffuseColor), 3);
			services->setPixelShaderConstant("SunSpecular", reinterpret_cast<irr::f32*>(&data.SpecularColor), 3);

			services->setPixelShaderConstant("SunDir", reinterpret_cast<irr::f32*>(&data.Direction), 3);
		}

		irr::f32 shininess = this->material.Shininess;
		services->setPixelShaderConstant("Shininess", &shininess, 1);
	}

	virtual void createShader()
	{
		if (!core)
			return;

		irr::video::IGPUProgrammingServices * gpu = core->getDriver()->getGPUProgrammingServices();

		id = gpu->addHighLevelShaderMaterial(vertex.c_str(), "main", irr::video::EVST_VS_1_1,
			pixel.c_str(), "main", irr::video::EPST_PS_1_1,
			this, irr::video::EMT_SOLID, irr::video::EGSL_DEFAULT);
	}

private:

	irr::video::SMaterial material;
};