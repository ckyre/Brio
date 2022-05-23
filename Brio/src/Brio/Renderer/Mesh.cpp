#include "brpch.h"
#include "Mesh.h"

namespace Brio
{
	Mesh::Mesh(const std::string& path)
	{
		LoadFile(path);
	}

	Mesh::Mesh(float* vertices, uint32_t size)
	{
		CreateMesh(vertices, size, nullptr, 0);
	}

	void Mesh::Bind()
	{
		m_VA->Bind();
		m_VB->Bind();
		//m_IB->Bind(); // TODO : Fix error here
	}

	void Mesh::Unbind()
	{
		m_VA->Unbind();
		m_VB->Unbind();
		m_IB->Unbind();
	}

	void Mesh::LoadFile(const std::string& path)
	{
		std::vector<float> vertices;
		std::vector<uint32_t> indices;

		Assimp::Importer importer;
		//const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
		const aiScene* scene = importer.ReadFile(path, 0);
		if (scene)
		{
			// Foreach meshs in scene
			for (unsigned int i = 0; i < scene->mNumMeshes; i++)
			{
				const aiMesh* mesh = scene->mMeshes[i];
				const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

				// Foreach vertices in mesh
				for (unsigned int j = 0; j < mesh->mNumVertices; j++)
				{
					const aiVector3D* _positions = &(mesh->mVertices[j]);
					const aiVector3D* _normals = &(mesh->mNormals[j]);
					const aiVector3D* _uvs = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][j]) : &Zero3D;

					vertices.push_back((float)_positions->x);
					vertices.push_back((float)_positions->y);
					vertices.push_back((float)_positions->z);
					vertices.push_back((float)_uvs->x);
					vertices.push_back((float)_uvs->y);
					vertices.push_back((float)_normals->x);
					vertices.push_back((float)_normals->y);
					vertices.push_back((float)_normals->z);
				}
			}
		}

		CreateMesh(vertices.data(), vertices.size(), indices.data(), indices.size());
	}

	void Mesh::CreateMesh(float* vertices, uint32_t verticesCount, uint32_t* indices, uint32_t indicesCount)
	{
		// Vertex buffer
		m_VB = Brio::VertexBuffer::Create(vertices, verticesCount * sizeof(float));

		// Vertex buffer layout
		Brio::BufferLayout layout = {
			{ Brio::ShaderDataType::Float3, "a_Position" },
			{ Brio::ShaderDataType::Float2, "a_UV" },
			{ Brio::ShaderDataType::Float3, "a_Normal" }
		};
		m_VB->SetLayout(layout);

		// Index buffer
		Brio::Ref<Brio::IndexBuffer> indexBuffer;
		if (indices != nullptr)
			indexBuffer = Brio::IndexBuffer::Create(indices, indicesCount);

		// Vertex array
		m_VA.reset(Brio::VertexArray::Create());
		m_VA->AddVertexBuffer(m_VB);
		if (indices != nullptr)
			m_VA->SetIndexBuffer(indexBuffer);
	}

}