#pragma once

#include <glm/glm.hpp>

namespace prime {

	enum class ProjectionType
	{ 
		perspective = 0,
		orthographic = 1 
	};

	class Camera
	{
	public:
		Camera();

		void SetPerspective(float FOV, float nearClip, float farClip);
		void SetOrthographic(float size, float nearClip, float farClip);

		void SetViewport(uint32_t width, uint32_t height);
		glm::mat4 GetProjection() { return m_projection; }

		float GetPerspectiveFOV() const { return m_perspectiveFOV; }
		void SetPerspectiveFOV(float FOV);

		float GetPerspectiveNear() const { return m_perspectiveNearClip; }
		void SetPerspectiveNear(float nearClip);

		float GetPerspectiveFar() const { return m_perspectiveFarClip; }
		void SetPerspectiveFar(float farClip);

		float GetOrthographicSize() const { return m_orthographicSize; }
		void SetOrthographicSize(float size);

		float GetOrthographicNear() const { return m_orthographicNear; }
		void SetOrthographicNear(float nearClip);

		float GetOrthographicFar() const { return m_orthographicFar; }
		void SetOrthographicFar(float farClip);

		ProjectionType GetProjectionType() const { return m_projectionType; }
		void SetProjectionType(ProjectionType type);

	private:
		void CalculateProjection();

	private:
		ProjectionType m_projectionType = ProjectionType::orthographic;

		float m_perspectiveFOV = glm::radians(45.0f);
		float m_perspectiveNearClip = 0.01f, m_perspectiveFarClip = 1000.0f;

		float m_orthographicSize = 10.0f;
		float m_orthographicNear = -1.0f, m_orthographicFar = 1.0f;

		float m_aspectRatio = 1.7666f;

		glm::mat4 m_projection = glm::mat4(1.0f);
	};
}
