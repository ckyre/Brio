#pragma once

#include <glm/glm.hpp>

namespace Brio
{
	class Transform
	{
	public:
		Transform() = default;
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);

		glm::mat4 GetMatrix() const;
	};
}

