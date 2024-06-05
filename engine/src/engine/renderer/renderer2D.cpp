
#include "pch.h"
#include "renderer2D.h"
#include "render_command.h"
#include "shader.h"
#include "engine/core/filesystem.h"
#include "engine/utils/math.h"
#include "engine/scene/components.h"

namespace prime {

	struct SpriteVertex
	{
		glm::vec3 position = glm::vec3(0.0f);
	};

	struct Data
	{
		uint32_t maxSprites = 20;
		glm::vec4 vertexPositions[4]{};

		// sprite
		uint32_t spriteIndexCount = 0;
		Ref<VertexArray> spriteVertexArray;
		Ref<Shader> spriteShader;
		SpriteVertex* spriteVertexBase = nullptr;
		SpriteVertex* spriteVertexPtr = nullptr;
	};

	Data m_data;

	void Renderer2D::Begin()
	{
		m_data.spriteIndexCount = 0;
		m_data.spriteVertexPtr = m_data.spriteVertexBase;
	}

	void Renderer2D::End()
	{
		if (m_data.spriteIndexCount)
		{
			int64_t spriteDataSize = (uint8_t*)m_data.spriteVertexPtr - (uint8_t*)m_data.spriteVertexBase;
			m_data.spriteVertexArray->GetVertexBuffer()->SetData(m_data.spriteVertexBase, (uint32_t)spriteDataSize);

			m_data.spriteShader->Bind();
			RenderCommand::Submit(m_data.spriteVertexArray, m_data.spriteIndexCount);
		}
	}

	void Renderer2D::DrawSprite(TransformComponent transform, SpriteComponent sprite)
	{
		glm::mat4 matrix = GetTransform(transform);
		for (auto i = 0; i < 4; i++)
		{
			m_data.spriteVertexPtr->position = matrix * m_data.vertexPositions[i];
			m_data.spriteVertexPtr++;
		}
		m_data.spriteIndexCount += 6;
	}

	void Renderer2D::Init()
	{
		m_data.vertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		m_data.vertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		m_data.vertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		m_data.vertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

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

		VertexLayout spriteLayout = {
			{ VertexType::position, "a_position" }
		};

		m_data.spriteVertexArray = VertexArray::Create();
		Ref<VertexBuffer> spriteVB = VertexBuffer::Create(maxVertices * sizeof(SpriteVertex));
		spriteVB->SetLayout(spriteLayout);
		m_data.spriteVertexArray->SetVertexBuffer(spriteVB);
		m_data.spriteVertexBase = new SpriteVertex[maxVertices];

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
		m_data.spriteVertexArray->SetIndexBuffer(spriteIB);
		delete[] indices;

		m_data.spriteShader = Filesystem::Loadshader("assets/shaders/sprite_vertex_shader.glsl",
			"assets/shaders/sprite_pixel_shader.glsl");
	}

	void Renderer2D::ShutdownSpriteRendering()
	{
		delete[] m_data.spriteVertexBase;
	}
}