#pragma once

#include "Brio/Core/Core.h"
#include "Brio/Core/Timestep.h"
#include "Brio/Core/Window.h"
#include "Brio/Events/Event.h"
#include "Brio/Events/ApplicationEvent.h"
#include "Brio/Core/LayerStack.h"

#include "Brio/ImGui/ImGuiLayer.h"
#include "Brio/Renderer/Shader.h"
#include "Brio/Renderer/Buffer.h"
#include "Brio/Renderer/VertexArray.h"

#include "Brio/Renderer/Camera/Camera.h"

namespace Brio
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		bool m_Running = true;
		bool m_Minimized = false;

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}

