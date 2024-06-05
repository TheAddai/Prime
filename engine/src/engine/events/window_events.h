#pragma once

#include <stdint.h>

namespace prime {

	class WindowCloseEvent
	{
	public:
		WindowCloseEvent() = default;
	};

	class WindowResizeEvent
	{
	public:
		WindowResizeEvent() = default;
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_width(width), m_height(height) {}

		uint32_t GetWidth() const { return m_width; }
		uint32_t GetHeight() const { return m_height; }

	private:
		uint32_t m_width = 0, m_height = 0;
	};
}
