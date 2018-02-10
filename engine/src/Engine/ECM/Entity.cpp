#include "ECM.hpp"

namespace Engine { namespace ECM {

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

	float Entity::GetRotation() const
	{
		return m_rotation;
	}

	void Entity::SetRotation(float t_rotation)
	{
		m_rotation = t_rotation;
	}

	void Entity::Move(const sf::Vector2f& t_position, float t_rotation)
	{
		m_position += t_position;
		m_rotation += t_rotation;
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

	void Entity::SetForDelete()
	{
		m_forDeletion = true;
	}

 } }