#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Brio/Renderer/Buffer.h"
#include "Brio/Renderer/VertexArray.h"

namespace Brio
{
	class Mesh
	{
	public:
		Mesh(const std::string& path);
		Mesh(float* vertices, uint32_t size);

		void Bind();
		void Unbind();

		inline uint32_t GetVerticesCount() { return m_VB->GetVerticesCount(); };
		inline uint32_t GetIndexCount() { return m_IB->GetCount(); };

		inline Ref<VertexArray> GetVertexArray() { return m_VA; };
		inline Ref<VertexBuffer> GetVertexBuffer() { return m_VB; };

	private:
		Ref<VertexArray> m_VA;
		Ref<VertexBuffer> m_VB;
		Ref<IndexBuffer> m_IB;

		void LoadFile(const std::string& path);
		void CreateMesh(float* vertices, uint32_t verticesCount, uint32_t* indices, uint32_t indicesCount);
	};
}

