#include "ShapeComponent.hpp"
#include "../../System/Renderer.hpp"

namespace Engine { namespace Components {

	ShapeComponent::ShapeComponent(ECM::Entity* t_parent) :
		Component(t_parent), 
		m_shape(std::make_shared<sf::CircleShape>())
	{ }

	void ShapeComponent::Update(float t_deltaTime)
	{
		if (m_parent->IsAlive())
		{
			m_shape->setPosition(m_parent->GetPosition());
		}
	}

	void ShapeComponent::Render()
	{
		if (m_parent->IsVisible())
			Engine::System::Renderer::Queue(&(*m_shape));
	}

	sf::Shape& ShapeComponent::GetShape()
	{
		return *m_shape;
	}

} }