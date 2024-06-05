#pragma once

#include "engine/core/assert.h"
#include "scene.h"

namespace prime {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene)
			: m_handle(handle), m_scene(scene) {}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			PASSERT_MSG(!HasComponent<T>(), "entity already has component!");
			T& component = m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
			return component;
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			T& component = m_scene->m_registry.emplace_or_replace<T>(m_handle, std::forward<Args>(args)...);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			PASSERT_MSG(HasComponent<T>(), "entity does not have component!");
			return m_scene->m_registry.get<T>(m_handle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_scene->m_registry.has<T>(m_handle);
		}

		template<typename T>
		void RemoveComponent()
		{
			PASSERT_MSG(HasComponent<T>(), "entity does not have component!");
			m_scene->m_registry.remove<T>(m_handle);
		}

		operator bool() const { return m_handle != entt::null; }

		bool operator==(const Entity& other) const
		{
			return m_handle == other.m_handle && m_scene == other.m_scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

		entt::entity GetID() const { return m_handle; }

	private:
		entt::entity m_handle = entt::null;
		Scene* m_scene = nullptr;
	};
}