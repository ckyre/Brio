#include "brpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Brio
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   BR_CORE_ASSERT(false, "No graphics API selected"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		BR_CORE_ASSERT(false, "No graphics API selected");
		return nullptr;
	}

	Ref<TextureCube> TextureCube::Create(const std::string& partialPath, const std::vector<std::string> facesFilesName)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   BR_CORE_ASSERT(false, "No graphics API selected"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTextureCube>(partialPath, facesFilesName);
		}

		BR_CORE_ASSERT(false, "No graphics API selected");
		return nullptr;
	}
}