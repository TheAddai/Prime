
#include "pch.h"
#include "camera.h"
#include "engine/core/assert.h"

#include <glm/gtc/matrix_transform.hpp>

namespace prime {

	Camera::Camera()
	{
		CalculateProjection();
	}

	void Camera::SetPerspective(float FOV, float nearClip, float farClip)
	{
		m_projectionType = ProjectionType::perspective;
		m_perspectiveFOV = FOV;
		m_perspectiveNearClip = nearClip;
		m_perspectiveFarClip = farClip;
		CalculateProjection();
	}

	void Camera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_projectionType = ProjectionType::orthographic;
		m_orthographicSize = size;
		m_orthographicNear = nearClip;
		m_orthographicFar = farClip;
		CalculateProjection();
	}

	void Camera::SetViewport(uint32_t width, uint32_t height)
	{
		PASSERT(width > 0 && height > 0);
		m_aspectRatio = (float)width / (float)height;
		CalculateProjection();
	}

	void Camera::SetPerspectiveFOV(float FOV)
	{
		m_perspectiveFOV = FOV;
		CalculateProjection();
	}

	void Camera::SetPerspectiveNear(float nearClip)
	{
		m_perspectiveNearClip = nearClip;
		CalculateProjection();
	}

	void Camera::SetPerspectiveFar(float farClip)
	{
		m_perspectiveFarClip = farClip;
		CalculateProjection();
	}

	void Camera::SetOrthographicSize(float size)
	{
		m_orthographicSize = size;
		CalculateProjection();
	}

	void Camera::SetOrthographicNear(float nearClip)
	{
		m_orthographicNear = nearClip;
		CalculateProjection();
	}

	void Camera::SetOrthographicFar(float farClip)
	{
		m_orthographicFar = farClip;
		CalculateProjection();
	}

	void Camera::SetProjectionType(ProjectionType type)
	{
		m_projectionType = type;
		CalculateProjection();
	}
	
	void Camera::CalculateProjection()
	{
		if (m_projectionType == ProjectionType::perspective)
		{
			m_projection = glm::perspective(m_perspectiveFOV, m_aspectRatio,
				m_perspectiveNearClip, m_perspectiveFarClip);
		}
		else
		{
			float orthoLeft = -m_orthographicSize * m_aspectRatio * 0.5f;
			float orthoRight = m_orthographicSize * m_aspectRatio * 0.5f;
			float orthoBottom = -m_orthographicSize * 0.5f;
			float orthoTop = m_orthographicSize * 0.5f;

			m_projection = glm::ortho(orthoLeft, orthoRight,
				orthoBottom, orthoTop, m_orthographicNear, m_orthographicFar);
		}
	}
}