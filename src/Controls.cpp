#include "Controls.hpp"
#include <stdexcept>

namespace HJ {

	std::map<std::string, sf::Keyboard::Key> Controls::m_keysTable;

	void Controls::Init()
	{
		Controls::SetKey("Return", sf::Keyboard::Escape);
		Controls::SetKey("Back", sf::Keyboard::Escape);
		Controls::SetKey("Pause", sf::Keyboard::P);
		Controls::SetKey("Skip", sf::Keyboard::Space);
		Controls::SetKey("Skip", sf::Keyboard::X);
	}

	sf::Keyboard::Key Controls::GetKey(const std::string& t_action)
	{
		auto key = m_keysTable.find(t_action);
		if (key != m_keysTable.end())
			return key->second;
		else 
			throw std::invalid_argument("Action not known.");
	}

	void Controls::SetKey(const std::string& t_action, sf::Keyboard::Key t_key)
	{
		m_keysTable[t_action] = t_key;
	}

}