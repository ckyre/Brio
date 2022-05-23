#pragma once

#include "Brio/Core/Timestep.h"
#include "Brio/Renderer/Camera/Camera.h"
#include "Brio/Events/ApplicationEvent.h"
#include "Brio/Events/MouseEvent.h"

namespace Brio
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		bool m_Rotation;
		float m_ZoomSpeed = 0.25f;
		float m_CameraMoveSpeed = 1.3f, m_CameraRotationSpeed = 180.0f;
	};

	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float fov, float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		PerspectiveCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 1.0f, -1.5f };
		glm::vec2 m_CameraRotation = { 0.0f, -0.25f };
		bool m_Rotation;
		float m_ZoomSpeed = 3.0f;
		float m_CameraMoveSpeed = 2.0f;
		float m_Sensivity = 0.09f;
	};
}

