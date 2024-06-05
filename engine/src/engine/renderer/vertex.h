#pragma once

#include <vector>

namespace prime {

	enum class VertexType
	{
		position
	};

	static uint32_t GetVertexTypeSize(VertexType vertexType)
	{
		switch (vertexType)
		{
		case VertexType::position: return 12; break;
		}
		return 0;
	}

	static uint32_t GetVertexTypeCount(VertexType vertexType)
	{
		switch (vertexType)
		{
		case VertexType::position: return 3; break;
		}
		return 0;
	}

	class Vertex
	{
	public:
		Vertex() = default;
		Vertex(VertexType vertexType, const char* name)
			: type(vertexType), name(name), size(GetVertexTypeSize(vertexType)) {}

		uint32_t GetCount() const { return GetVertexTypeCount(type); }

	public:
		const char* name = nullptr;
		VertexType type = VertexType::position;
		uint32_t size = 0;
		uint64_t offset = 0;
	};

	class VertexLayout
	{
	public:
		VertexLayout() = default;
		VertexLayout(std::initializer_list<Vertex> vertices) :m_vertices(vertices)
		{
			ProcessVertices();
		}

		uint32_t GetStride() const { return m_stride; }
		const std::vector<Vertex>& GetVertices() const { return m_vertices; }

		std::vector<Vertex>::iterator begin() { return m_vertices.begin(); }
		std::vector<Vertex>::iterator end() { return m_vertices.end(); }
		std::vector<Vertex>::const_iterator begin() const { return m_vertices.begin(); }
		std::vector<Vertex>::const_iterator end() const { return m_vertices.end(); }

		void ProcessVertices()
		{
			uint64_t offset = 0;
			m_stride = 0;
			for (Vertex& vertex : m_vertices)
			{
				vertex.offset = offset;
				offset += vertex.size;
				m_stride += vertex.size;
			}
		}

	private:
		uint32_t m_stride = 0;
		std::vector<Vertex> m_vertices;
	};
}