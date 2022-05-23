#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <map>

namespace Brio
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, 
		Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual inline const std::string& GetName() const = 0;
		virtual inline const uint32_t& GetRendererID() const = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& path);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	
	protected:
		std::unordered_map<std::string, ShaderDataType> m_CompiledUniforms;
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		BR_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}
	
	struct ShaderUniform
	{
		ShaderDataType Type = ShaderDataType::None;
		uint32_t Size = 0;
		uint32_t Offset = 0; // offset in uniform buffer

		ShaderUniform() = default;

		ShaderUniform(ShaderDataType type, uint32_t size, uint32_t offset)
			: Type(type), Size(size), Offset(offset)
		{
		}
	};
}