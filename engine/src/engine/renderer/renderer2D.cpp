
#include "pch.h"
#include "renderer2D.h"
#include "render_command.h"
#include "shader.h"
#include "engine/core/filesystem.h"
#include "engine/utils/math.h"
#include "engine/scene/components.h"
#include "uniform_buffer.h"

namespace prime {

	struct SpriteVertex
	{
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec4 color = glm::vec4(1.0f);
		glm::vec2 textureCoords = glm::vec2(0.0f);
		float textureIndex = 0.0f;
	};

	struct Data
	{
		uint32_t maxSprites = 20, maxSpritePerCall = 1000;
		glm::vec4 vertexPositions[4]{};
		Ref<UniformBuffer> cameraUniformBuffer;

		// texture
		uint32_t textureSlotIndex = 1;
		static const uint32_t maxTextureSlots = 16;
		glm::vec2 textureCoords[4]{};
		std::array<Ref<Texture>, maxTextureSlots> textureSlots;

		// sprite
		uint32_t spriteIndexCount = 0;
		Ref<VertexArray> spriteVertexArray;
		Ref<Shader> spriteShader;
		SpriteVertex* spriteVertexBase = nullptr;
		SpriteVertex* spriteVertexPtr = nullptr;
	};

	Data m_data;

	void Renderer2D::Begin(const glm::mat4 viewProjectionMatrix)
	{
		m_data.cameraUniformBuffer->SetData(&viewProjectionMatrix, sizeof(glm::mat4));
		BeginRendering();
	}

	void Renderer2D::End()
	{
		if (m_data.spriteIndexCount)
		{
			int64_t spriteDataSize = (uint8_t*)m_data.spriteVertexPtr - (uint8_t*)m_data.spriteVertexBase;
			m_data.spriteVertexArray->GetVertexBuffer()->SetData(m_data.spriteVertexBase, (uint32_t)spriteDataSize);

			for (uint32_t i = 0; i < m_data.textureSlotIndex; i++)
			{
				m_data.textureSlots[i]->Bind(i);
			}

			m_data.spriteShader->Bind();
			RenderCommand::Submit(m_data.spriteVertexArray, m_data.spriteIndexCount);
		}
	}

	void Renderer2D::DrawSprite(TransformComponent transform, SpriteComponent sprite)
	{
		if (m_data.spriteIndexCount >= m_data.maxSpritePerCall * 6)
		{
			End();
			BeginRendering();
		}

		if (m_data.textureSlotIndex > m_data.maxTextureSlots)
		{
			End();
			BeginRendering();
		}

		float textureIndex = 0.0f;
		if (sprite.texture.get()) { textureIndex = GetTextureIndex(sprite.texture); }

		glm::mat4 matrix = GetTransform(transform);
		for (auto i = 0; i < 4; i++)
		{
			m_data.spriteVertexPtr->position = matrix * m_data.vertexPositions[i];
			m_data.spriteVertexPtr->textureCoords = m_data.textureCoords[i];
			m_data.spriteVertexPtr->textureIndex = textureIndex;
			m_data.spriteVertexPtr->color = sprite.color;
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

		m_data.textureCoords[0] = { 0.0f, 0.0f };
		m_data.textureCoords[1] = { 1.0f, 0.0f };
		m_data.textureCoords[2] = { 1.0f, 1.0f };
		m_data.textureCoords[3] = { 0.0f, 1.0f };

		m_data.cameraUniformBuffer = UniformBuffer::Create(sizeof(glm::mat4), 0);
		m_data.textureSlots[0] = Texture2D::Create(TextureConfig());

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
			{ VertexType::position, "a_position" },
			{ VertexType::color, "a_color" },
			{ VertexType::textureCoords, "a_textureCoords" },
			{ VertexType::textureIndex, "a_textureIndex" }
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

		// texture
		int32_t samplers[m_data.maxTextureSlots]{};
		for (uint32_t i = 0; i < m_data.maxTextureSlots; i++) { samplers[i] = i; }

		m_data.spriteShader = Filesystem::Loadshader("assets/shaders/sprite_vertex_shader.glsl",
			"assets/shaders/sprite_pixel_shader.glsl");
		m_data.spriteShader->Bind();
		m_data.spriteShader->SetIntArray("u_textures", samplers, m_data.maxTextureSlots);
	}

	void Renderer2D::ShutdownSpriteRendering()
	{
		delete[] m_data.spriteVertexBase;
	}
	
	void Renderer2D::BeginRendering()
	{
		m_data.spriteIndexCount = 0;
		m_data.spriteVertexPtr = m_data.spriteVertexBase;

		m_data.textureSlotIndex = 1;
	}

	float Renderer2D::GetTextureIndex(Ref<Texture2D>& texture)
	{
		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < m_data.textureSlotIndex; i++)
		{
			if (*m_data.textureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)m_data.textureSlotIndex;
			m_data.textureSlots[m_data.textureSlotIndex] = texture;
			m_data.textureSlotIndex++;
		}
		return textureIndex;
	}	
}