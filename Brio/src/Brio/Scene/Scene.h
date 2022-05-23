#pragma once

#include <glm/glm.hpp>

namespace Brio
{
	struct SceneData
	{
		glm::mat4 ViewProjectionMatrix;
		glm::vec3 ViewPosition;
		glm::vec3 LightPosition;
	};

	class Scene
	{
	};
}

