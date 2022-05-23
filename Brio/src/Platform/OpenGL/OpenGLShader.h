#pragma once

#include <fstream>
#include <glad/glad.h>
#include "Brio/Renderer/Buffer.h"
#include "Brio/Renderer/Shader.h"

namespace Brio
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& path);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual inline const std::string& GetName() const override { return m_Name; }
		virtual inline const uint32_t& GetRendererID() const override { return m_RendererID; }

	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcessSource(const std::string& source);
		void OpenGLShader::Compile(std::unordered_map<GLenum, std::string> shaderSources);

		std::string m_Name;
		uint32_t m_RendererID;
	};
}