#include "brpch.h"
#include "Shader.h"

#include "Brio/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Brio
{
	Ref<Shader> Shader::Create(const std::string& name, const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   BR_CORE_ASSERT(false, "No graphics API selected"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, path);
		}

		BR_CORE_ASSERT(false, "No graphics API selected");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   BR_CORE_ASSERT(false, "No graphics API selected"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		BR_CORE_ASSERT(false, "No graphics API selected");
		return nullptr;
	}
}