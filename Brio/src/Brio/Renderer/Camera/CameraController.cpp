#include "brpch.h"
#include "Brio/Renderer/Camera/CameraController.h"

#include "Brio/Core/Input.h"
#include "Brio/Core/KeyCodes.h"
#include "Brio/Core/Application.h"

namespace Brio
{
	// Orthographic camera

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_Camera(aspectRatio), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		// Move
		if (Input::IsKeyPressed(Key::A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		if (Input::IsKeyPressed(Key::D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (Input::IsKeyPressed(Key::S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		if (Input::IsKeyPressed(Key::W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		m_Camera.SetPosition(m_CameraPosition);

		//  Rotate
		if (m_Rotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(Key::E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
			m_CameraMoveSpeed = m_Camera.GetZoom();
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BR_BIND_EVENT_FUNC(OrthographicCameraController::OnMouseScrolled)));
		dispatcher.Dispatch<WindowResizeEvent>(BR_BIND_EVENT_FUNC(OrthographicCameraController::OnWindowResized)));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		float zoom = m_Camera.GetZoom() - e.GetYOffset() * m_ZoomSpeed;
		zoom = std::max(zoom, 0.25f);
		m_Camera.SetZoom(zoom);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_Camera.SetAspectRatio((float)e.GetWidth() / (float)e.GetHeight());
		return false;
	}

	// Perspective camera

	PerspectiveCameraController::PerspectiveCameraController(float fov, float aspectRatio, bool rotation)
		: m_Camera(fov, aspectRatio), m_Rotation(rotation)
	{
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		// Move
		if (Input::IsKeyPressed(Key::W))
			m_CameraPosition += glm::normalize(m_Camera.GetForward()) * m_CameraMoveSpeed * ts.GetMiliseconds();
		if (Input::IsKeyPressed(Key::S))
			m_CameraPosition -= glm::normalize(m_Camera.GetForward()) * m_CameraMoveSpeed * ts.GetMiliseconds();
		if (Input::IsKeyPressed(Key::D))
			m_CameraPosition += glm::normalize(m_Camera.GetRight()) * m_CameraMoveSpeed * ts.GetMiliseconds();
		if (Input::IsKeyPressed(Key::A))
			m_CameraPosition -= glm::normalize(m_Camera.GetRight()) * m_CameraMoveSpeed * ts.GetMiliseconds();
		if (Input::IsKeyPressed(Key::Q))
			m_CameraPosition -= glm::normalize(m_Camera.GetUp()) * m_CameraMoveSpeed * ts.GetMiliseconds();
		if (Input::IsKeyPressed(Key::E))
			m_CameraPosition += glm::normalize(m_Camera.GetUp()) * m_CameraMoveSpeed * ts.GetMiliseconds();

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraMoveSpeed = m_Camera.GetFOV() / 12000;

		if (m_Rotation && Input::IsMouseButtonPressed(Mouse::Button1))
		{
			int windowWidth = Application::Get().GetWindow().GetWidth();
			int windowHeight = Application::Get().GetWindow().GetHeight();


			glm::vec2 velocity = { float((windowWidth / 2) - Input::GetMousePosition().first),
								   float((windowHeight / 2) - Input::GetMousePosition().second) };

			m_CameraRotation.x += m_Sensivity * ts * velocity.x;
			m_CameraRotation.y += m_Sensivity * ts * velocity.y;

			Application::Get().GetWindow().CenterCursor();

			m_Camera.SetRotation(m_CameraRotation);
		}
	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BR_BIND_EVENT_FUNC(PerspectiveCameraController::OnMouseScrolled)));
		dispatcher.Dispatch<WindowResizeEvent>(BR_BIND_EVENT_FUNC(PerspectiveCameraController::OnWindowResized)));
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		float fov = m_Camera.GetFOV() - e.GetYOffset() * m_ZoomSpeed;
		fov = std::max(fov, 10.0f);
		m_Camera.SetFOV(fov);
		return false;
	}
	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_Camera.SetAspectRatio((float)e.GetWidth() / (float)e.GetHeight());
		return false;
	}
}