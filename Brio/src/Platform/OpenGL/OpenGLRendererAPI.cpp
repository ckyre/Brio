#include "brpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
#include "Brio/Renderer/Material.h"
#include "Brio/Renderer/UniformBuffer.h"

namespace Brio
{
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::UpdateStaticUniforms(const SceneData& sceneData)
	{
		// /!\ Warning /!\ : Respect order of shader's layout
		// + should place padding before vec3 to align them
		// https://stackoverflow.com/questions/20807797/opengl-glsl-uniform-block-data-values-incorrect/20807965#20807965
		MaterialLibrary::StaticUniforms()->Set("u_ViewProjection", sceneData.ViewProjectionMatrix);
		MaterialLibrary::StaticUniforms()->Set("u_LightPosition", sceneData.LightPosition);
		MaterialLibrary::StaticUniforms()->Set("padding", 0.0f);
		MaterialLibrary::StaticUniforms()->Set("u_ViewPosition", sceneData.ViewPosition);

		MaterialLibrary::UnploadStaticUniforms();
	}

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetDepthMask(bool value)
	{
		if (value)
			glDepthFunc(GL_LESS);
		else
			glDepthFunc(GL_LEQUAL);

		//glDepthMask(value);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		glDrawArrays(GL_TRIANGLES, 0, vertexBuffer->GetVerticesCount());
	}
}