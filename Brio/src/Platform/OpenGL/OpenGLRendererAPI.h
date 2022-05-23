#pragma once

#include "Brio/Renderer/RendererAPI.h"
#include "Brio/Scene/Scene.h"

namespace Brio
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void UpdateStaticUniforms(const SceneData& sceneData) override;

		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetDepthMask(bool value) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void DrawBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
	};
}

