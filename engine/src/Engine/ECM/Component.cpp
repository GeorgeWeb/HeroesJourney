#include "ECM.hpp"

namespace Engine { namespace ECM 
{
	Component::Component(Entity* const t_parent)
		: m_parent(t_parent)
	{ }

	Component::~Component()
	{ }

	bool Component::m_isForDeletion() const
	{
		return m_forDeletion;
	}

} }