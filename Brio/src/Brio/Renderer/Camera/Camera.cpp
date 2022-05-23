#include "brpch.h"
#include "Brio/Renderer/Camera/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Brio
{
	Camera::Camera(float aspectRatio)
		: m_AspectRatio(aspectRatio)
	{
	}

	// Orthographic camera

	OrthographicCamera::OrthographicCamera(float aspectRatio)
		: Camera(aspectRatio)
	{
		ComputeMatrices();
	}

	void OrthographicCamera::ComputeMatrices()
	{
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 transform = translate * rotate;
		m_ViewMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetAspectRatio(const float& aspectRatio)
	{
		m_AspectRatio = aspectRatio;
		ComputeMatrices();
	}

	void OrthographicCamera::SetRotation(const float& rotation)
	{
		m_Rotation = rotation;
		ComputeMatrices();
	}

	void OrthographicCamera::SetZoom(float zoom)
	{
		m_Zoom = zoom;
		ComputeMatrices();
	}

	// Perspective camera

	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio)
		: Camera(aspectRatio), m_FOV(fov)
	{
		ComputeMatrices();
	}

	void PerspectiveCamera::ComputeMatrices()
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, 0.1f, 100.0f);

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + forward, up);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::SetRotation(const glm::vec2& rotation)
	{
		m_Rotation = rotation;
		forward = glm::vec3(cos(m_Rotation.y) * sin(m_Rotation.x), sin(m_Rotation.y), cos(m_Rotation.y) * cos(m_Rotation.x));
		right = glm::vec3(sin(m_Rotation.x - 3.14f / 2.0f), 0, cos(m_Rotation.x - 3.14f / 2.0f));
		up = cross(right, forward);

		ComputeMatrices();
	}

	void PerspectiveCamera::SetAspectRatio(const float& aspectRatio)
	{
		m_AspectRatio = aspectRatio;
		ComputeMatrices();
	}

	void PerspectiveCamera::SetFOV(const float& fov)
	{
		m_FOV = fov;
		ComputeMatrices();
	}
}