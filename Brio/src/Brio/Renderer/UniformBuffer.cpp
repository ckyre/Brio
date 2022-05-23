#include "brpch.h"
#include "UniformBuffer.h"

#include "Platform/OpenGL/OpenGLUniformBuffer.h"
#include "Brio/Renderer/Renderer.h"
#include <glm/gtc/type_ptr.hpp>

namespace Brio
{
	Ref<UniformBuffer> UniformBuffer::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   BR_CORE_ASSERT(false, "No graphics API selected"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLUniformBuffer>();
		}

		BR_CORE_ASSERT(false, "No graphics API selected");
		return nullptr;
	}

	void UniformBuffer::Set(const std::string& name, const float& value)
	{
		ShaderDataType type = ShaderDataType::Float;
		uint32_t size = ShaderDataTypeSize(type);

		if (m_Uniforms.find(name) == m_Uniforms.end())
		{
			ShaderUniform uniform = ShaderUniform(type, size, m_Buffer->GetSize());
			m_Uniforms.insert(std::pair<std::string, ShaderUniform>(name, uniform));

			m_Buffer->Write((void*)&value, size);
		}
		else
		{
			m_Buffer->Write((void*)&value, size, m_Uniforms[name].Offset);
		}
	}

	void UniformBuffer::Set(const std::string& name, const glm::vec2& value)
	{
		ShaderDataType type = ShaderDataType::Float2;
		uint32_t size = ShaderDataTypeSize(type);

		if (m_Uniforms.find(name) == m_Uniforms.end())
		{
			ShaderUniform uniform = ShaderUniform(type, size, m_Buffer->GetSize());
			m_Uniforms.insert(std::pair<std::string, ShaderUniform>(name, uniform));

			m_Buffer->Write((void*)glm::value_ptr(value), size);
		}
		else
		{
			m_Buffer->Write((void*)glm::value_ptr(value), size, m_Uniforms[name].Offset);
		}
	}

	void UniformBuffer::Set(const std::string& name, const glm::vec3& value)
	{
		ShaderDataType type = ShaderDataType::Float3;
		uint32_t size = ShaderDataTypeSize(type);

		if (m_Uniforms.find(name) == m_Uniforms.end())
		{
			ShaderUniform uniform = ShaderUniform(type, size, m_Buffer->GetSize());
			m_Uniforms.insert(std::pair<std::string, ShaderUniform>(name, uniform));

			m_Buffer->Write((void*)glm::value_ptr(value), size);
		}
		else
		{
			m_Buffer->Write((void*)glm::value_ptr(value), size, m_Uniforms[name].Offset);
		}
	}

	void UniformBuffer::Set(const std::string& name, const glm::vec4& value)
	{
		ShaderDataType type = ShaderDataType::Float4;
		uint32_t size = ShaderDataTypeSize(type);

		if (m_Uniforms.find(name) == m_Uniforms.end())
		{
			ShaderUniform uniform = ShaderUniform(type, size, m_Buffer->GetSize());
			m_Uniforms.insert(std::pair<std::string, ShaderUniform>(name, uniform));

			m_Buffer->Write((void*)glm::value_ptr(value), size);
		}
		else
		{
			m_Buffer->Write((void*)glm::value_ptr(value), size, m_Uniforms[name].Offset);
		}
	}

	void UniformBuffer::Set(const std::string& name, const glm::mat4& value)
	{
		ShaderDataType type = ShaderDataType::Mat4;
		uint32_t size = ShaderDataTypeSize(type);

		if (m_Uniforms.find(name) == m_Uniforms.end())
		{
			ShaderUniform uniform = ShaderUniform(type, size, m_Buffer->GetSize());
			m_Uniforms.insert(std::pair<std::string, ShaderUniform>(name, uniform));

			m_Buffer->Write((void*)glm::value_ptr(value), size);
		}
		else
		{
			m_Buffer->Write((void*)glm::value_ptr(value), size, m_Uniforms[name].Offset);
		}
	}

	void UniformBuffer::Set(const std::string& name, const Ref<Texture2D> value)
	{
		m_Textures[name] = value;
	}
}