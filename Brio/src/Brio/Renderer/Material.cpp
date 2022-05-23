#include "brpch.h"
#include "Material.h"

#include "Brio/Renderer/Renderer.h"
#include "Brio/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLMaterial.h"

namespace Brio
{
	Ref<Material> Material::Create(const std::string& name, Ref<Shader> shader)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLMaterial>(name, shader);
		}

		BR_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	void Material::UploadUniforms() const
	{
		uint32_t shaderID = MaterialLibrary::GetShader(m_Shader)->GetRendererID();
		return m_Uniforms->UploadUniforms(shaderID);
	}

	bool Material::GetFlag(MaterialFlag flag) const
	{
		return (uint32_t)flag& m_Flags;
	}

	void Material::SetFlag(MaterialFlag flag, bool value)
	{
		if (value)
			m_Flags |= (uint32_t)flag;
		else
			m_Flags &= ~(uint32_t)flag;
	}

	/////////////////////////////////////////
	/////// MaterialLibrary /////////////////
	/////////////////////////////////////////

	std::map<std::string, Ref<Shader>> MaterialLibrary::s_Shaders;
	std::map<std::string, Ref<Material>> MaterialLibrary::s_Materials;

	Ref<UniformBuffer> MaterialLibrary::m_StaticUniforms;

	void MaterialLibrary::Init()
	{
		m_StaticUniforms = UniformBuffer::Create();
	}

	Ref<Shader> MaterialLibrary::CreateShader(const std::string& name, const std::string& path)
	{
		BR_CORE_INFO("Creating shader {0}", name);
		BR_CORE_ASSERT(!ShaderExists(name), "Shader with the same name alredy exists in library : {0}", name);

		Ref<Shader> shader = Shader::Create(name, path);
		s_Shaders[name] = shader;

		return shader;
	}

	Ref<Material> MaterialLibrary::CreateMaterial(const std::string& name, const Ref<Shader>& shader)
	{
		BR_CORE_ASSERT(!ShaderExists(name), "Material with the same name alredy exists in library : {0}");

		Ref<Material> material = Material::Create(name, shader);
		s_Materials[name] = material;

		return material;
	}

	Ref<Shader> MaterialLibrary::GetShader(const std::string& name)
	{
		BR_CORE_ASSERT(ShaderExists(name), "Shader with name {0} not found", name);
		return s_Shaders[name];
	}

	Ref<Material> MaterialLibrary::GetMaterial(const std::string& name)
	{
		BR_CORE_ASSERT(MaterialExists(name), "Material with name {0} not found", name);
		return s_Materials[name];
	}

	void MaterialLibrary::UnploadStaticUniforms()
	{
		m_StaticUniforms->UploadUniformsViaBuffer();
	}

	bool MaterialLibrary::ShaderExists(const std::string& name)
	{
		return s_Shaders.find(name) != s_Shaders.end();
	}

	bool MaterialLibrary::MaterialExists(const std::string& name)
	{
		return (s_Materials.find(name) != s_Materials.end());
	}
}