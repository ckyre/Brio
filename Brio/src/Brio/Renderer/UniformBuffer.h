#pragma once

#include <map>
#include <string>
#include "Brio/Renderer/Buffer.h"
#include "Brio/Renderer/Shader.h"
#include "Brio/Renderer/Texture.h"

namespace Brio
{
	class UniformBuffer
	{
	public:
		static Ref<UniformBuffer> UniformBuffer::Create();

		virtual void UploadUniforms(uint32_t shaderRendererID) = 0;

		virtual void UploadUniformsViaBuffer() = 0;
		virtual void BindUniformsBuffer(uint32_t shaderRendererID) = 0;

		void Set(const std::string& name, const float& value);
		void Set(const std::string& name, const glm::vec2& value);
		void Set(const std::string& name, const glm::vec3& value);
		void Set(const std::string& name, const glm::vec4& value);
		void Set(const std::string& name, const glm::mat4& value);
		void Set(const std::string& name, const Ref<Texture2D> value);

		uint32_t GetSize() { return (*m_Buffer).GetSize(); }
		uint32_t GetCount() { return m_Uniforms.size(); }

	protected:
		std::map<std::string, ShaderUniform> m_Uniforms;
		std::map<std::string, Ref<Texture2D>> m_Textures;

		Ref<Buffer> m_Buffer;
	};
}



