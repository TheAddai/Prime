#pragma once

#include "engine/core/buttons.h"

namespace prime {

	class MouseButtonPressedEvent
	{
	public:
		MouseButtonPressedEvent() = default;
		MouseButtonPressedEvent(Button button) : m_button(button) {}

		Button GetButton() const { return m_button; }

	private:
		Button m_button;
	};

	class MouseButtonReleasedEvent
	{
	public:
		MouseButtonReleasedEvent() = default;
		MouseButtonReleasedEvent(Button button) : m_button(button) {}

		Button GetButton() const { return m_button; }

	private:
		Button m_button;
	};

	class MouseMovedEvent
	{
	public:
		MouseMovedEvent() = default;
		MouseMovedEvent(float x, float y) : m_x(x), m_y(y) {}

		float GetX() const { return m_x; }
		float GetY() const { return m_y; }

	private:
		float m_x = 0.0f, m_y = 0.0f;
	};

	class MouseScrolledEvent
	{
	public:
		MouseScrolledEvent() = default;
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset) {}

		float GetOffsetX() const { return m_xOffset; }
		float GetOffsetY() const { return m_yOffset; }

	private:
		float m_xOffset = 0.0f, m_yOffset = 0.0f;
	};
}