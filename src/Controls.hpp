#ifndef CONTROLS_H
#define CONTROLS_H

#include <SFML/Graphics.hpp>
#include <map>

namespace HJ {

	class Controls final
	{
		private:
			static std::map<std::string, sf::Keyboard::Key> m_keysTable;
			static std::map<std::string, sf::Mouse::Button> m_btnsTable;

		public:
			static void Init();
			static sf::Keyboard::Key GetKey(const std::string& t_action);
			static void SetKey(const std::string& t_action, sf::Keyboard::Key t_key);

			static sf::Mouse::Button GetButton(const std::string& t_action);
			static void SetButton(const std::string& t_action, sf::Mouse::Button t_button);

			static std::string KeyToString(sf::Keyboard::Key t_key);
			static std::string BtnToString(sf::Keyboard::Key t_btn);
	};

}

#endif // !CONTROLS_H
