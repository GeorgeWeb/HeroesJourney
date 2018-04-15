#include "Controls.hpp"
#include <stdexcept>

namespace HJ {

	std::map<std::string, sf::Keyboard::Key> Controls::m_keysTable;
	std::map<std::string, sf::Mouse::Button> Controls::m_btnsTable;

	void Controls::Init()
	{
		Controls::SetKey("Skip", sf::Keyboard::Space);
		Controls::SetKey("Back", sf::Keyboard::Escape);
		Controls::SetKey("Pause", sf::Keyboard::P);
		Controls::SetButton("Select", sf::Mouse::Left);
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

	sf::Mouse::Button Controls::GetButton(const std::string& t_action)
	{
		auto button = m_btnsTable.find(t_action);
		if (button != m_btnsTable.end())
			return button->second;
		else
			throw std::invalid_argument("Action not known.");
	}

	void Controls::SetButton(const std::string& t_action, sf::Mouse::Button t_button)
	{
		m_btnsTable[t_action] = t_button;
	}

}