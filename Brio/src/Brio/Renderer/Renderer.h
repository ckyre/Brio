#pragma once

#include <glad/glad.h>
#include "Brio/Renderer/RenderCommand.h"
#include "Brio/Renderer/Camera/Camera.h"
#include "Brio/Renderer/Material.h"
#include "Brio/Core/Transform.h"
#include "Brio/Scene/Scene.h"
#include "Brio/Renderer/Mesh.h"

namespace Brio
{
	class Renderer
	{
	public:
		static void SetupScene(Camera& camera, glm::vec3 lightPos);
		static void BeginScene(Camera& camera, glm::vec3 lightPos);
		static void EndScene();

		static void UpdateStaticUniforms();

		static void Init();
		static void OnWidowResize(uint32_t width, uint32_t height);

		static void Submit(const Ref<Material>& material, const Ref<VertexArray>& vertexArray, const Transform& transform);
		static void Submit(const Ref<Material>& material, const Ref<VertexBuffer>& vertexBuffer, const Transform& transform);
		static void Submit(const Ref<Material>& material, Mesh& mesh, const Transform& transform);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static SceneData* m_SceneData;
	};
}

