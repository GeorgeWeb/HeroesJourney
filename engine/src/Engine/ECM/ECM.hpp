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
			bool m_alive; ///> should be updated
			bool m_visible; ///> should be rendered
			bool m_forDeletion; ///> should be deleted
		
		public:
			Entity() = default;
			virtual ~Entity() = default;

			std::map<std::string, std::shared_ptr<Component>> GetCompsDictionary() { return m_components; }

			virtual void Update(const float t_deltaTime);
			virtual void Render();

			const sf::Vector2f& GetPosition() const;
			void SetPosition(const sf::Vector2f& t_position);
			
			float GetRotation() const;
			void SetRotation(float t_rotation);
			
			void Move(const sf::Vector2f& t_position, float t_rotation);

			bool IsAlive() const;
			void SetAlive(bool t_alive);

			bool IsVisible() const;
			void SetVisible(bool t_visible);

			void SetForDelete();

			template<class T, class... Targs>
			std::shared_ptr<T> AddComponent(const std::string& t_name, Targs... t_params)
			{
				static_assert(std::is_base_of<Component, T>::value, "must be a component");
				std::shared_ptr<T> comp(std::make_shared<T>(this, t_params...));
				m_components.insert_or_assign(t_name, comp);
				return comp;
			}

			std::shared_ptr<Component> GetComponent(const std::string t_name)
			{
				//if ()
				return m_components[t_name];
			}
	};

	class Component
	{
		protected:
			Entity* const m_parent;
			bool m_forDeletion;
			
			explicit Component(Entity *const t_parent);

		public:
			Component() = delete;

			bool m_isForDeletion() const;

			virtual void Update(float t_deltaTime) = 0;
			virtual void Render() = 0;
			// Just need it too much atm! Will design it better later.
			virtual sf::Shape& GetShape() { return sf::CircleShape(); }
			virtual sf::Text& GetText() { return sf::Text(); };
			virtual sf::Sprite& GetSprite() { sf::Sprite sp; return sp; }
			virtual System::Animation& GetAnimation() { return System::Animation(); }

			virtual ~Component();
	};

} }

#endif // !ENTITY_H
