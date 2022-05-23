#include "brpch.h"
#include "OpenGLUniformBuffer.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Brio/Renderer/Material.h"
#include <iostream>

namespace Brio
{
	uint32_t OpenGLUniformBuffer::s_StaticBufferBindingPoint;

	OpenGLUniformBuffer::OpenGLUniformBuffer()
	{
		m_Buffer = std::make_shared<Buffer>();
	}

	void OpenGLUniformBuffer::UploadUniforms(uint32_t shaderRendererID)
	{
		m_ShaderRendererID = shaderRendererID;

		for (auto& uniform : m_Uniforms)
		{
			switch (uniform.second.Type)
			{
			case ShaderDataType::Float:
				UploadUniformFloat(uniform.first, (*m_Buffer).Read<float>(uniform.second.Size, uniform.second.Offset));
				break;
			case ShaderDataType::Int:
				UploadUniformInt(uniform.first, (*m_Buffer).Read<int>(uniform.second.Size, uniform.second.Offset));
				break;
			case ShaderDataType::Float2:
				UploadUniformFloat2(uniform.first, (*m_Buffer).Read<glm::vec2>(uniform.second.Size, uniform.second.Offset));
				break;
			case ShaderDataType::Float3:
				UploadUniformFloat3(uniform.first, (*m_Buffer).Read<glm::vec3>(uniform.second.Size, uniform.second.Offset));
				break;
			case ShaderDataType::Float4:
				UploadUniformFloat4(uniform.first, (*m_Buffer).Read<glm::vec4>(uniform.second.Size, uniform.second.Offset));
				break;
			case ShaderDataType::Mat3:
				UploadUniformMat3(uniform.first, (*m_Buffer).Read<glm::mat3>(uniform.second.Size, uniform.second.Offset));
				break;
			case ShaderDataType::Mat4:
				UploadUniformMat4(uniform.first, (*m_Buffer).Read<glm::mat4>(uniform.second.Size, uniform.second.Offset));
				break;
			}
		}

		// Textures
		int i = 0;
		for (auto& texture : m_Textures)
		{
			if (i < 31)
			{
				UploadUniformInt(texture.first, i);
				glActiveTexture(33984 + i); // 33684 = GL_TEXTURE0
				texture.second->Bind(i);
				i++;
			}
			else break;
		}
	}

	void OpenGLUniformBuffer::UploadUniformsViaBuffer()
	{
		// Create buffer if not already
		if (m_BufferRendererID == 0)
		{
			glGenBuffers(1, &m_BufferRendererID);
			glBindBuffer(GL_UNIFORM_BUFFER, m_BufferRendererID);
			glBufferData(GL_UNIFORM_BUFFER, m_Buffer->Data.size(), m_Buffer->Data.data(), GL_DYNAMIC_DRAW);
		}
		else
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_BufferRendererID);

			GLvoid* ptr = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
			memcpy(ptr, m_Buffer->Data.data(), m_Buffer->Data.size());
			glUnmapBuffer(GL_UNIFORM_BUFFER);
		}
	}

	void OpenGLUniformBuffer::BindUniformsBuffer(uint32_t shaderRendererID)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_BufferRendererID);

		// Bind uniform buffer to a binding point in GPU memory
		unsigned int shaderBlockIndex = glGetUniformBlockIndex(shaderRendererID, "SceneData");

		// Chose a binding point
		if (s_StaticBufferBindingPoint > 70)
			s_StaticBufferBindingPoint = 0;

		m_BufferBindingPoint = s_StaticBufferBindingPoint;
		s_StaticBufferBindingPoint++;

		glBindBufferBase(GL_UNIFORM_BUFFER, m_BufferBindingPoint, m_BufferRendererID);

		// Specify this bidning point to shader program
		glUniformBlockBinding(shaderRendererID, shaderBlockIndex, m_BufferBindingPoint);
	}

	//////////////////////////////////
	////// Set uniforms //////////////
	//////////////////////////////////

	GLuint OpenGLUniformBuffer::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		GLuint location = glGetUniformLocation(m_ShaderRendererID, name.c_str());
		m_UniformLocationCache[name] = location;
		return location;
	}

	void OpenGLUniformBuffer::UploadUniformInt(const std::string& name, const int& value)
	{
		glUniform1i(GetUniformLocation(name.c_str()), value);
	}

	void OpenGLUniformBuffer::UploadUniformFloat(const std::string& name, const float& value)
	{
		glUniform1f(GetUniformLocation(name.c_str()), value);
	}

	void OpenGLUniformBuffer::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name.c_str()), value.x, value.y);
	}

	void OpenGLUniformBuffer::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name.c_str()), value.x, value.y, value.z);
	}

	void OpenGLUniformBuffer::UploadUniformFloat4(const std::string& name, const glm::vec4 value)
	{
		glUniform4f(GetUniformLocation(name.c_str()), value.x, value.y, value.z, value.w);
	}

	void OpenGLUniformBuffer::UploadUniformMat3(const std::string& name, const glm::mat3& value)
	{
		glUniformMatrix3fv(GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLUniformBuffer::UploadUniformMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
}