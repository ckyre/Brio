#include "brpch.h"
#include "Skybox.h"

#include "Brio/Renderer/RenderCommand.h"
#include "Brio/Renderer/Renderer.h"

#include <glm/gtx/transform.hpp>

namespace Brio
{
	Skybox::Skybox(const std::string& partialPath, const std::vector<std::string> facesFilesName)
		: m_ShaderName("SkyboxShader"), m_MaterialName("SkyboxMaterial")
	{
		m_CubeMap = TextureCube::Create(partialPath, facesFilesName);

		MaterialLibrary::CreateShader(m_ShaderName, partialPath + "/../Shaders/Skybox.glsl");
		MaterialLibrary::CreateMaterial(m_MaterialName, MaterialLibrary::GetShader(m_ShaderName));
		MaterialLibrary::GetMaterial(m_MaterialName)->SetFlag(MaterialFlag::TwoSided, true);

		m_Mesh = std::make_shared<Mesh>(m_Vertices, 120); // 120 is skybox's vertices components count
		
		m_Transform = *(new Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(100.0f)));
	}

	Skybox::Skybox(Ref<TextureCube> cubeMap)
		: m_CubeMap(cubeMap), m_ShaderName("SkyboxShader"), m_MaterialName("SkyboxMaterial")
	{
		MaterialLibrary::CreateShader(m_ShaderName, "E:/Dev/Brio/Sandbox/assets/Shaders/Skybox.glsl");
		MaterialLibrary::CreateMaterial(m_MaterialName, MaterialLibrary::GetShader(m_ShaderName));
		MaterialLibrary::GetMaterial(m_MaterialName)->SetFlag(MaterialFlag::TwoSided, true);

		m_Mesh = std::make_shared<Mesh>(m_Vertices, 120); // 120 is skybox's vertices components count

		m_Transform = *(new Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(100.0f)));
	}

	Skybox::~Skybox()
	{
	}

	void Skybox::Draw(Camera& camera)
	{
		RenderCommand::SetDepthMask(false);

		Ref<UniformBuffer> uniformBuffer = MaterialLibrary::GetMaterial(m_MaterialName)->Uniforms();
		uniformBuffer->Set("u_Skybox", 0);
		uniformBuffer->Set("u_CustomViewMatrix", glm::mat4(glm::mat3(camera.GetViewMatrix())));
		uniformBuffer->Set("u_Projection", camera.GetProjectionMatrix());
		m_CubeMap->Bind(0);

		Renderer::Submit(MaterialLibrary::GetMaterial(m_MaterialName), m_Mesh->GetVertexBuffer(), m_Transform);

		RenderCommand::SetDepthMask(true);
	}
}