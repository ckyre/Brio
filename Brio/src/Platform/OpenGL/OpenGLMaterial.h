#pragma once

#include "Brio/Renderer/Material.h"
#include "Brio/Renderer/Shader.h"

namespace Brio
{
	class OpenGLMaterial : public Material
	{
	public:
		OpenGLMaterial(const std::string& name, const Ref<Shader>& shader);

		virtual void Bind() override;
		virtual void Unbind() override;
	};
}

