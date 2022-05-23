#pragma once

#include "Brio/Core/Core.h"
#include "Brio/Renderer/Shader.h"
#include "Brio/Renderer/UniformBuffer.h"

namespace Brio
{
	enum class MaterialFlag
	{
		None = BIT(0),
		DepthTest = BIT(1),
		Blend = BIT(2),
		TwoSided = BIT(3)
	};

	class Material
	{
	public:
		static Ref<Material> Create(const std::string& name, Ref<Shader> shader);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		inline Ref<UniformBuffer> Uniforms() { return m_Uniforms; }
		void UploadUniforms() const;

		bool GetFlag(MaterialFlag flag) const;
		void SetFlag(MaterialFlag flag, bool value = true);

		inline const std::string& GetName() { return m_Name; }
		inline const std::string& GetShaderName() { return m_Shader; }

	protected:
		std::string m_Name;

		std::string m_Shader;
		Ref<UniformBuffer> m_Uniforms;
		uint32_t m_Flags;
	};

	class MaterialLibrary
	{
	public:
		static void Init();

		static Ref<Shader> CreateShader(const std::string& name, const std::string& path);
		static Ref<Material> CreateMaterial(const std::string& name, const Ref<Shader>& shader);

		static Ref<Shader> GetShader(const std::string& name);
		static Ref<Material> GetMaterial(const std::string& name);
		
		static inline Ref<UniformBuffer> StaticUniforms() { return m_StaticUniforms; }
		static void UnploadStaticUniforms();

	private:
		static Ref<UniformBuffer> m_StaticUniforms;
		static bool ShaderExists(const std::string& name);
		static bool MaterialExists(const std::string& name);

		static std::map<std::string, Ref<Shader>> s_Shaders;
		static std::map<std::string, Ref<Material>> s_Materials;
	};
}

