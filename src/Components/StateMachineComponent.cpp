#include "StateMachineComponent.hpp"

namespace HJ { namespace Components {

	using namespace Engine;
	using namespace ECM;
	using namespace States;

	StateMachineComponent::StateMachineComponent(Entity* t_parent) : 
		m_currentState(nullptr), 
		Component(t_parent)
	{ }

	void StateMachineComponent::Update(float t_deltaTime)
	{
		if (m_parent->IsAlive())
		{
			if (m_currentState != nullptr && m_isInTransition)
				m_currentState->Execute(m_parent, t_deltaTime);
		}
	}

	void StateMachineComponent::AddState(const std::string& t_name, std::shared_ptr<State> t_state)
	{
		m_states.insert_or_assign(t_name, t_state);
		m_states.at(t_name)->InitSM(this);
	}

	std::shared_ptr<State> StateMachineComponent::GetState(const std::string& t_name) const
	{
		auto found = m_states.find(t_name);
		if (found != m_states.end())
			return found->second;
		else
			return nullptr;
	}

	void StateMachineComponent::RemoveState(const std::string& t_name)
	{
		m_states.erase(t_name);
	}

	void StateMachineComponent::ChangeState(const std::string& t_name)
	{
		auto found = m_states.find(t_name);
		if (found != m_states.end())
		{
			m_currentState = found->second;
			m_currentState->EnterState(m_parent);
			m_currentStateName = t_name;
		}
	}

} }