#include "brpch.h"
#include "Transform.h"

#include <glm/ext/matrix_transform.hpp>

namespace Brio
{
	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		: Position(position), Rotation(rotation), Scale(scale)
	{
	}

	glm::mat4 Transform::GetMatrix() const
	{
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), Position);
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, glm::vec3(1.0f)) *
							 glm::rotate(glm::mat4(1.0f), Rotation.y, glm::vec3(1.0f)) *
							 glm::rotate(glm::mat4(1.0f), Rotation.z, glm::vec3(1.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);

		return (translation * rotation * scale);
	}
}