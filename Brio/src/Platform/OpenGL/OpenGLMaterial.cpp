#include "brpch.h"
#include "OpenGLMaterial.h"

#include <glad/glad.h>

namespace Brio
{
	OpenGLMaterial::OpenGLMaterial(const std::string& name, const Ref<Shader>& shader)
	{
		m_Uniforms = UniformBuffer::Create();
		m_Shader = shader->GetName();
		m_Name = name;

		SetFlag(MaterialFlag::TwoSided, false);
	}

	void OpenGLMaterial::Bind()
	{
		MaterialLibrary::GetShader(m_Shader)->Bind();

		if (m_Flags == 3452816845)
		{
			glDisable(GL_CULL_FACE);
		}
		else
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
		}
	}

	void OpenGLMaterial::Unbind()
	{
		MaterialLibrary::GetShader(m_Shader)->Unbind();
	}
}
