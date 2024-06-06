#pragma once

#include <glm/glm.hpp>

namespace prime {

	enum class ProjectionType
	{ 
		Perspective = 0,
		Orthographic = 1 
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

		float GetOrthoSize() const { return m_orthographicSize; }
		void SetOrthoSize(float size);

		float GetOrthoNearClip() const { return m_orthographicNear; }
		void SetOrthoNearClip(float nearClip);

		float GetOrthoFarClip() const { return m_orthographicFar; }
		void SetOrthoFarClip(float farClip);

		ProjectionType GetProjectionType() const { return m_projectionType; }
		void SetProjectionType(ProjectionType type);

	private:
		void CalculateProjection();

	private:
		ProjectionType m_projectionType = ProjectionType::Orthographic;

		float m_perspectiveFOV = glm::radians(45.0f);
		float m_perspectiveNearClip = 0.01f, m_perspectiveFarClip = 1000.0f;

		float m_orthographicSize = 10.0f;
		float m_orthographicNear = -1.0f, m_orthographicFar = 1.0f;

		float m_aspectRatio = 1.7666f;

		glm::mat4 m_projection = glm::mat4(1.0f);
	};
}
