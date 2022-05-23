#pragma once

#include "Brio/Renderer/UniformBuffer.h"
#include <glad/glad.h>

namespace Brio
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer();
		~OpenGLUniformBuffer() {}

		virtual void UploadUniforms(uint32_t shaderRendererID) override;

		virtual void UploadUniformsViaBuffer() override;
		virtual void BindUniformsBuffer(uint32_t shaderRendererID) override;

	private:
		static uint32_t s_StaticBufferBindingPoint;
		uint32_t m_BufferRendererID = 0;
		uint32_t m_BufferBindingPoint = 0;

		uint32_t m_ShaderRendererID = 0;

		std::map <std::string, GLuint> m_UniformLocationCache;
		GLuint GetUniformLocation(const std::string& name);

		void UploadUniformInt(const std::string& name, const int& value);
		void UploadUniformFloat(const std::string& name, const float& value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4 values);
		void UploadUniformMat3(const std::string& name, const glm::mat3& value);
		void UploadUniformMat4(const std::string& name, const glm::mat4& value);
	};
}

