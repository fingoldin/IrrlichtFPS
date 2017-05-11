#include "stdafx.h"

#include "Core.h"

#include "Shader.h"

#include "PerPixelShader.h"
#include "PerPixelOldShader.h"
#include "FancyShader.h"

Shader * Shader::shaders[E_SHADER_TYPE_COUNT];

Shader::Shader(Core * core) : core(core), id(0)
{
}


Shader::~Shader()
{
}

void Shader::initShaders(Core * core)
{
	for (int i = 0; i < E_SHADER_TYPE_COUNT; i++)
		shaders[i] = NULL;

	shaders[EST_PERPIXEL] = DBG_NEW PerPixelShader(core);
	shaders[EST_PERPIXEL_OLD] = DBG_NEW PerPixelOldShader(core);
	shaders[EST_FANCY] = DBG_NEW FancyShader(core);
}

void Shader::cleanupShaders()
{
	for (int i = 0; i < E_SHADER_TYPE_COUNT; i++)
		if (shaders[i])
			shaders[i]->drop();
}