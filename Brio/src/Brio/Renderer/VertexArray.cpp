#include "brpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Brio
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   BR_CORE_ASSERT(false, "No graphics API selected"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		BR_CORE_ASSERT(false, "No graphics API selected");
		return nullptr;
	}
}