#include "brpch.h"
#include "Buffer.h"

#include "Brio/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Brio
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   BR_CORE_ASSERT(false, "No graphics API selected"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		BR_CORE_ASSERT(false, "No graphics API selected");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   BR_CORE_ASSERT(false, "No graphics API selected"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		BR_CORE_ASSERT(false, "No graphics API selected");
		return nullptr;
	}
}