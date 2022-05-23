#pragma once

#include <glm/glm.hpp>

namespace Brio
{
	class Camera
	{
	public:
		Camera(float aspectRatio);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; ComputeMatrices(); }

		const float& GetAspectRatio() const { return m_AspectRatio; }
		virtual void SetAspectRatio(const float& aspectRatio) = 0;

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	protected:
		virtual void ComputeMatrices() = 0;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		float m_AspectRatio;
		glm::vec3 m_Position = { 0.0f, 0.0f, 10.0f };
	};

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float aspectRatio);

		const float& GetRotation() const { return m_Rotation; }
		void SetRotation(const float& rotation);

		float GetZoom() { return m_Zoom; }
		void SetZoom(float zoom);

		virtual void SetAspectRatio(const float& aspectRatio) override;

	private:
		virtual void ComputeMatrices() override;

		float m_Rotation = 0.0f;
		float m_Zoom = 1.0f;
	};

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio);

		const glm::vec2& GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::vec2& rotation);

		const float& GetFOV() const { return m_FOV; }
		void SetFOV(const float& fov);

		const glm::vec3& GetForward() const { return forward; }
		const glm::vec3& GetRight() const { return right; }
		const glm::vec3& GetUp() const { return up; }

		virtual void SetAspectRatio(const float& aspectRatio) override;

	private:
		virtual void ComputeMatrices() override;

		float m_FOV = 30.0f;

		glm::vec2 m_Rotation = { 0.0f, 0.0f };

		glm::vec3 forward = { 0, 0, 1 };
		glm::vec3 right = { 1, 0, 0 };
		glm::vec3 up = { 0, 0, 1 };
	};

}

