#pragma once

#include "engine/utils/timer.h"

namespace prime {

	class Timestep
	{
	public:
		Timestep() : m_time(0.0f), m_lastTime(0.0f) {}

		float GetDelta() { return m_time; }

	private:
		void Tick()
		{
			float time = Timer::GetTime();
			m_time = time - m_lastTime;
			m_lastTime = time;
		}

	private:
		float m_time = 0.0f, m_lastTime = 0.0f;
		friend class Engine;
	};
}
