#pragma once

#include "engine/core/keys.h"

#include <stdint.h>

namespace prime {

	class KeyPressedEvent
	{
	public:
		KeyPressedEvent() = default;
		KeyPressedEvent(const Key key, bool repeat = false)
			: m_key(key), m_repeat(repeat) {}

		Key GetKey() const { return m_key; }
		bool GetRepeat() const { return m_repeat; }

	private:
		Key m_key;
		bool m_repeat = false;
	};

	class KeyReleasedEvent
	{
	public:
		KeyReleasedEvent() = default;
		KeyReleasedEvent(Key key) : m_key(key) {}

		Key GetKey() const { return m_key; }

	private:
		Key m_key;
	};
}