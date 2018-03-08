#include "ECM.hpp"

namespace Engine { namespace ECM {
	
	std::map<std::string, std::shared_ptr<Component>> Entity::GetComponents()
	{
		return m_components;
	}

	Entity* Entity::GetType()
	{
		return this;
	}
	
	void Entity::Init()
	{
		m_forDeletion = false;
	}

	void Entity::Update(float t_deltaTime)
	{ 
		if (m_alive)
		{
			for (const auto& comp : m_components)
				comp.second->Update(t_deltaTime);
		}
	}

	void Entity::Render()
	{
		if (m_visible)
		{
			for (const auto& comp : m_components)
				comp.second->Render();
		}
	}

	const sf::Vector2f& Entity::GetPosition() const
	{
		return m_position;
	}

	void Entity::SetPosition(const sf::Vector2f& t_position) 
	{ 
		m_position = t_position; 
	}

	void Entity::Move(const sf::Vector2f& t_position)
	{
		m_position += t_position;
	}

	bool Entity::IsAlive() const
	{
		return m_alive;
	}

	void Entity::SetAlive(bool t_alive)
	{
		m_alive = t_alive;
	}

	bool Entity::IsVisible() const
	{
		return m_visible;
	}

	void Entity::SetVisible(bool t_visible)
	{
		m_visible = t_visible;
	}

	bool Entity::IsForDeletion() const
	{
		return m_forDeletion;
	}

	void Entity::SetForDelete()
	{
		m_forDeletion = true;
	}

 } }