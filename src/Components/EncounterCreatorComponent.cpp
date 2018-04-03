#include "EncounterCreatorComponent.hpp"
#include <Engine/Input/InputManager.hpp>
#include <Engine/System/Renderer.hpp>

namespace HJ { namespace Components {

	using namespace Engine;
	using namespace System;

	EncounterCreatorComponent::EncounterCreatorComponent(ECM::Entity* t_parent)
		: ECM::Component(t_parent)
	{ }

	EncounterCreatorComponent* EncounterCreatorComponent::GetType()
	{
		return this;
	}

	void EncounterCreatorComponent::Update(float t_deltaTime)
	{
		if (m_parent->IsAlive())
		{

		}
	}

	void EncounterCreatorComponent::Render()
	{
		if (m_parent->IsVisible())
		{

		}
	}

} }