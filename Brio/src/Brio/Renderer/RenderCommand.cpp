#include "brpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Brio
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}