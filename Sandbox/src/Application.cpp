#include <Brio.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui.h"

#include "glm/gtc/type_ptr.hpp"
#include <GLFW/include/GLFW/glfw3.h>

#include <iostream>
#include <filesystem>

class ExampleLayer : public Brio::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(55.0f, 1280.0f / 720.0f, true), m_AssetsBasePath(std::filesystem::current_path().string())
	{
		// Shaders
		Brio::Ref<Brio::Shader> flatShader = Brio::MaterialLibrary::CreateShader("FlatColorShader", m_AssetsBasePath + "/../Sandbox/assets/Shaders/FlatColor.glsl");
		Brio::Ref<Brio::Shader> diffuseShader = Brio::MaterialLibrary::CreateShader("DiffuseShader", m_AssetsBasePath + "/../Sandbox/assets/Shaders/Diffuse.glsl");

		// Textures
		albedoMap = Brio::Texture2D::Create(m_AssetsBasePath + "/../Sandbox/assets/Textures/CrateAlbedo.png");
		specularMap = Brio::Texture2D::Create(m_AssetsBasePath + "/../Sandbox/assets/Textures/CrateSpecular.png");

		// Materials
		Brio::MaterialLibrary::CreateMaterial("FlatColorMat", flatShader);
		Brio::Ref<Brio::Material> diffuseMat = Brio::MaterialLibrary::CreateMaterial("DiffuseMat", diffuseShader);
		diffuseMat->Uniforms()->Set("material.diffuse", albedoMap);
		diffuseMat->Uniforms()->Set("material.specular", specularMap);

		// Set up scene for Renderer
		Brio::Renderer::SetupScene(m_CameraController.GetCamera(), glm::vec3(0.0f));
	}

	void OnUpdate(Brio::Timestep ts) override
	{
		// Update logic
		timeStep = ts.GetMiliseconds();

		m_CameraController.OnUpdate(ts);

		// Update renderer
		Brio::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
		Brio::RenderCommand::Clear();

		glm::vec3 lightPos = glm::vec3(glm::sin(glfwGetTime()), 1.0f, 0.0f);

		Brio::Renderer::BeginScene(m_CameraController.GetCamera(), lightPos);
		{
			// Light
			{
				Brio::Transform cubeTransform(lightPos, glm::vec3(0.0f), glm::vec3(0.05f, 0.05f, 0.05f));

				Brio::MaterialLibrary::GetMaterial("FlatColorMat")->Uniforms()->Set("u_Color", glm::vec3(0.8f, 0.4f, 0.2f));
				Brio::Renderer::Submit(Brio::MaterialLibrary::GetMaterial("FlatColorMat"), CubeMesh, cubeTransform);
			}

			// Crate
			{
				Brio::Transform carTransform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

				// Material
				Brio::Ref<Brio::Material> sphereMaterial = Brio::MaterialLibrary::GetMaterial("DiffuseMat");
				sphereMaterial->Uniforms()->Set("material.shininess", 32.0f);

				// Point light
				{
					sphereMaterial->Uniforms()->Set("pointLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
					sphereMaterial->Uniforms()->Set("pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
					sphereMaterial->Uniforms()->Set("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

					sphereMaterial->Uniforms()->Set("pointLight.constant", 1.0f);
					sphereMaterial->Uniforms()->Set("pointLight.linear", 0.09f);
					sphereMaterial->Uniforms()->Set("pointLight.quadratic", 0.032f);
				}

				// Directional light
				{
					sphereMaterial->Uniforms()->Set("dirLight.direction", glm::vec3(0.6f, -0.8f, 0.3f));

					sphereMaterial->Uniforms()->Set("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
					sphereMaterial->Uniforms()->Set("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
					sphereMaterial->Uniforms()->Set("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
				}

				// Spot light
				{
					sphereMaterial->Uniforms()->Set("spotLight.position", m_CameraController.GetCamera().GetPosition());
					sphereMaterial->Uniforms()->Set("spotLight.direction", m_CameraController.GetCamera().GetForward());

					sphereMaterial->Uniforms()->Set("spotLight.cutOff", glm::cos(glm::radians(0.0f)));
					sphereMaterial->Uniforms()->Set("spotLight.outerCutOff", glm::cos(glm::radians(0.0f)));

					sphereMaterial->Uniforms()->Set("spotLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
					sphereMaterial->Uniforms()->Set("spotLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
					sphereMaterial->Uniforms()->Set("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

					sphereMaterial->Uniforms()->Set("spotLight.constant", 1.0f);
					sphereMaterial->Uniforms()->Set("spotLight.linear", 0.09f);
					sphereMaterial->Uniforms()->Set("spotLight.quadratic", 0.032f);
				}

				// Render
				Brio::Renderer::Submit(sphereMaterial, CarMesh, carTransform);
			}

			Skybox.Draw(m_CameraController.GetCamera());
		}
		Brio::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		{
			std::ostringstream ss{};
			ss << "Timestep : " << std::round(timeStep) << " ms";
			std::string s(ss.str());
			ImGui::Text(s.c_str());
		}

		{
			std::ostringstream ss{};
			ss << "Camera position : "
				<< " X " << m_CameraController.GetCamera().GetPosition().x
				<< " Y " << m_CameraController.GetCamera().GetPosition().y
				<< " Z " << m_CameraController.GetCamera().GetPosition().z
				;
			std::string s(ss.str());
			ImGui::Text(s.c_str());
		}

		{
			std::ostringstream ss{};
			ss << "Camera rotation : "
				<< " X " << m_CameraController.GetCamera().GetRotation().x
				<< " Y " << m_CameraController.GetCamera().GetRotation().y
				;
			std::string s(ss.str());
			ImGui::Text(s.c_str());
		}
		
		ImGui::End();
	}

	void OnEvent(Brio::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

private:
	float timeStep = 0.0f;
	Brio::PerspectiveCameraController m_CameraController;

	std::string m_AssetsBasePath;

	Brio::Mesh CarMesh = Brio::Mesh(m_AssetsBasePath + "/../Sandbox/assets/Meshs/Cube.obj");
	Brio::Mesh CubeMesh = Brio::Mesh(m_AssetsBasePath + "/../Sandbox/assets/Meshs/Cube.obj");

	Brio::Skybox Skybox = Brio::Skybox(m_AssetsBasePath + "/../Sandbox/assets/Textures/", {
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	});

	Brio::Ref<Brio::Texture2D> albedoMap, specularMap;
};

class Sandbox : public Brio::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Brio::Application* Brio::CreateApplication()
{
	return new Sandbox();
}