#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "../Maths/Vector2ul.hpp"
#include "../System/Animation.hpp"

#include <algorithm>
#include <typeindex>
#include <memory>
#include <map>

namespace Engine { namespace ECM {

	class Component;

	// Entity class interface and base functionality
	class Entity
	{
		// TODO: Implement scale like position is implemented!!!

		protected:
			std::map<std::string, std::shared_ptr<Component>> m_components;
			sf::Vector2f m_position;			
			float m_rotation;
			sf::Vector2f m_scale;

			bool m_alive; ///> should be updated
			bool m_visible; ///> should be rendered
			bool m_forDeletion; ///> should be deleted
		
		public:
			Entity();
			virtual ~Entity() = default;

			virtual Entity* GetType();

			std::map<std::string, std::shared_ptr<Component>> GetCompsDictionary();

			virtual void Update(const float t_deltaTime);
			virtual void Render();

			const sf::Vector2f& GetPosition() const;
			void SetPosition(const sf::Vector2f& t_position);
			
			float GetRotation() const;
			void SetRotation(float t_rotation);
			
			const sf::Vector2f& GetScale() const;
			void SetScale(const sf::Vector2f& t_factor);

			void Move(const sf::Vector2f& t_position);

			bool IsAlive() const;
			void SetAlive(bool t_alive);

			bool IsVisible() const;
			void SetVisible(bool t_visible);

			bool IsForDeletion() const;
			void SetForDelete();

			template<class T, class... Targs>
			std::shared_ptr<T> AddComponent(const std::string& t_name, Targs... t_params)
			{
				static_assert(std::is_base_of<Component, T>::value, "must be a component");
				std::shared_ptr<T> comp(std::make_shared<T>(this, t_params...));
				m_components.insert_or_assign(t_name, comp);
				return comp;
			}

			template<class T>
			T* GetComponent(const std::string t_name)
			{
				static_assert(std::is_base_of<Component, T>::value, "must be a component");
				// ... checks
				return dynamic_cast<T*>(m_components[t_name]->GetType());
			}
	};
 
	class Component
	{
		protected:
			Entity* const m_parent;
			bool m_forDeletion;
			bool m_isClickable;

			explicit Component(Entity *const t_parent);

		public:
			Component() = delete;

			virtual Component* GetType();

			bool IsClickable() const;
			void SetClickable(const bool t_clickable);

			bool IsForDeletion() const;

			virtual void Update(float t_deltaTime) = 0;
			virtual void Render() = 0;

			virtual ~Component();
	};

} }

#endif // !ENTITY_H