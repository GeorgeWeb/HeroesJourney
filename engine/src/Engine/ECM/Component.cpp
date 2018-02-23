#include "ECM.hpp"

namespace Engine { namespace ECM 
{
	Component::Component(Entity* const t_parent)
		: m_parent(t_parent)
	{
		m_forDeletion = false;
		m_isClickable = false;
	}

	Component::~Component()
	{ }

	Component* Component::GetType()
	{
		return this;
	}

	bool Component::IsClickable() const
	{
		return m_isClickable;
	}

	void Component::SetClickable(const bool t_clickable)
	{
		m_isClickable = t_clickable;
	}

	bool Component::IsForDeletion() const
	{
		return m_forDeletion;
	}

} }