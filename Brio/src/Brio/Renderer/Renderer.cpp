#include "brpch.h"
#include "Renderer.h"

#include "Brio/Renderer/Material.h"

namespace Brio
{
	SceneData* Renderer::m_SceneData = new SceneData;

	void Renderer::SetupScene(Camera& camera, glm::vec3 lightPos)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		m_SceneData->ViewPosition = camera.GetPosition();
		m_SceneData->LightPosition = lightPos;

		UpdateStaticUniforms();
	}

	void Renderer::BeginScene(Camera& camera, glm::vec3 lightPos)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		m_SceneData->ViewPosition = camera.GetPosition();
		m_SceneData->LightPosition = lightPos;

		UpdateStaticUniforms();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::UpdateStaticUniforms()
	{
		RenderCommand::UpdateStaticUniforms(*m_SceneData);
	}

	void Renderer::Init()
	{
		MaterialLibrary::Init();
		RenderCommand::Init();
	}

	void Renderer::OnWidowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(const Ref<Material>& material, const Ref<VertexArray>& vertexArray, const Transform& transform)
	{
		// Upload materials uniforms
		material->Bind();
		material->Uniforms()->Set("u_Transform", transform.GetMatrix());
		material->UploadUniforms();

		vertexArray->Bind();

		// Upload statics uniforms
		uint32_t shaderRendererID = MaterialLibrary::GetShader(material->GetShaderName())->GetRendererID();
		MaterialLibrary::StaticUniforms()->BindUniformsBuffer(shaderRendererID);

		// Draw
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Submit(const Ref<Material>& material, const Ref<VertexBuffer>& vertexBuffer, const Transform& transform)
	{
		// Upload materials uniforms
		material->Bind();
		material->Uniforms()->Set("u_Transform", transform.GetMatrix());
		material->UploadUniforms();

		vertexBuffer->Bind();

		// Upload statics uniforms
		uint32_t shaderRendererID = MaterialLibrary::GetShader(material->GetShaderName())->GetRendererID();
		MaterialLibrary::StaticUniforms()->BindUniformsBuffer(shaderRendererID);

		// Draw
		RenderCommand::DrawBuffer(vertexBuffer);
	}

	void Renderer::Submit(const Ref<Material>& material, Mesh& mesh, const Transform& transform)
	{
		// Upload materials uniforms
		material->Bind();
		material->Uniforms()->Set("u_Transform", transform.GetMatrix());
		material->UploadUniforms();

		mesh.Bind();

		// Upload statics uniforms
		uint32_t shaderRendererID = MaterialLibrary::GetShader(material->GetShaderName())->GetRendererID();
		MaterialLibrary::StaticUniforms()->BindUniformsBuffer(shaderRendererID);

		// Draw
		RenderCommand::DrawBuffer(mesh.GetVertexBuffer());
	}
}