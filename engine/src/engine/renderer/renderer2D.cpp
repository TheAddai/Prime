
#include "pch.h"
#include "renderer2D.h"
#include "render_command.h"
#include "shader.h"
#include "engine/core/filesystem.h"

#include <glm/glm.hpp>

namespace prime {

	struct SpriteVertex
	{
		glm::vec3 position = glm::vec3(0.0f);
	};

	struct Data
	{
		uint32_t maxSprites = 20;

		// sprite
		Ref<VertexArray> spriteVertexArray;
		Ref<Shader> spriteShader;
		SpriteVertex* spriteVertexBase = nullptr;
		SpriteVertex* spriteVertexPtr = nullptr;
	};

	Data m_data;

	void Renderer2D::Init()
	{
		InitSpriteRendering();
	}

	void Renderer2D::Shutdown()
	{
		ShutdownSpriteRendering();
	}

	void Renderer2D::InitSpriteRendering()
	{
		uint32_t maxVertices = m_data.maxSprites * 4;
		uint32_t maxIndices = m_data.maxSprites * 6;

		m_data.spriteVertexArray = VertexArray::Create();
		Ref<VertexBuffer> spriteVB = VertexBuffer::Create(maxVertices * sizeof(SpriteVertex));
		m_data.spriteVertexBase = new SpriteVertex[maxVertices];

		VertexLayout spriteLayout = {
			{ VertexType::position, "a_position" }
		};

		// indices
		uint32_t* indices = new uint32_t[maxIndices];
		uint32_t offset = 0;
		for (uint32_t x = 0; x < maxIndices; x += 6)
		{
			indices[x + 0] = offset + 0;
			indices[x + 1] = offset + 1;
			indices[x + 2] = offset + 2;

			indices[x + 3] = offset + 2;
			indices[x + 4] = offset + 3;
			indices[x + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> spriteIB = IndexBuffer::Create(indices, maxIndices);
		delete[] indices;

		m_data.spriteShader = Filesystem::Loadshader("assets/shaders/sprite_vertex_shader.glsl",
			"assets/shaders/sprite_pixel_shader.glsl");
	}

	void Renderer2D::ShutdownSpriteRendering()
	{
		delete[] m_data.spriteVertexBase;
	}
}