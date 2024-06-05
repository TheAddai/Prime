#pragma once

#include <stdint.h>

namespace prime {

	class GUID
	{
	public:
		GUID();
		GUID(uint64_t _GUID);
		GUID(const GUID&) = default;

		operator uint64_t() const { return m_gUID; }

	private:
		uint64_t m_gUID = 0;
	};
}

namespace std {

	template <typename T> struct hash;

	template<>
	struct hash<prime::GUID>
	{
		uint64_t operator()(const prime::GUID& gUID) const
		{
			return (uint64_t)gUID;
		}
	};
}