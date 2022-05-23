#include "brpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "Brio/Core/Core.h"
#include "Brio/Core/Log.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Brio
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		BR_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BR_CORE_ASSERT(status, "Failed to initialize Glad");

		// Print system informations
		BR_CORE_TRACE("OpenGL context initialized.\n                  Vendor :   {0}\n                  Renderer : {1}\n                  Version :  {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
