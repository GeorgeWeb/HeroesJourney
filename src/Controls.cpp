#include "Controls.hpp"
#include <stdexcept>
#include <string>

#define KEY_ITEM(k) case sf::Keyboard::##k : ret = #k; break;
#define BTN_ITEM(b) case sf::Mouse::##b : ret = #b; break;

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

	std::string Controls::KeyToString(sf::Keyboard::Key t_key)
	{
		std::string ret = "";
		switch (t_key)
		{
			KEY_ITEM(A);
			KEY_ITEM(B);
			KEY_ITEM(C);
			KEY_ITEM(D);
			KEY_ITEM(E);
			KEY_ITEM(F);
			KEY_ITEM(G);
			KEY_ITEM(H);
			KEY_ITEM(I);
			KEY_ITEM(J);
			KEY_ITEM(K);
			KEY_ITEM(L);
			KEY_ITEM(M);
			KEY_ITEM(N);
			KEY_ITEM(O);
			KEY_ITEM(P);
			KEY_ITEM(Q);
			KEY_ITEM(R);
			KEY_ITEM(S);
			KEY_ITEM(T);
			KEY_ITEM(U);
			KEY_ITEM(V);
			KEY_ITEM(W);
			KEY_ITEM(X);
			KEY_ITEM(Z);
			KEY_ITEM(Space);
			KEY_ITEM(BackSpace);
			KEY_ITEM(Slash);
			KEY_ITEM(BackSlash);
			KEY_ITEM(Dash);
			KEY_ITEM(Return);
			KEY_ITEM(Escape);
			KEY_ITEM(Comma);
			KEY_ITEM(SemiColon);
			KEY_ITEM(Delete);
			KEY_ITEM(Up);
			KEY_ITEM(Down);
			KEY_ITEM(Left);
			KEY_ITEM(Right);
			KEY_ITEM(PageDown);
			KEY_ITEM(End);
			KEY_ITEM(Equal);
			KEY_ITEM(Subtract);
			KEY_ITEM(Add);
			KEY_ITEM(Divide);
			KEY_ITEM(Multiply);
			KEY_ITEM(Home);
			KEY_ITEM(Insert);
			KEY_ITEM(LAlt);
			KEY_ITEM(RAlt);
			KEY_ITEM(LBracket);
			KEY_ITEM(RBracket);
			KEY_ITEM(LControl);
			KEY_ITEM(RControl);
			KEY_ITEM(RShift);
			KEY_ITEM(LShift);
			KEY_ITEM(LSystem);
			KEY_ITEM(RSystem);
			KEY_ITEM(Tab);
			KEY_ITEM(Menu);
			KEY_ITEM(Num0);
			KEY_ITEM(Num1);
			KEY_ITEM(Num2);
			KEY_ITEM(Num3);
			KEY_ITEM(Num4);
			KEY_ITEM(Num5);
			KEY_ITEM(Num6);
			KEY_ITEM(Num7);
			KEY_ITEM(Num8);
			KEY_ITEM(Num9);
			KEY_ITEM(Numpad0);
			KEY_ITEM(Numpad1);
			KEY_ITEM(Numpad2);
			KEY_ITEM(Numpad3);
			KEY_ITEM(Numpad4);
			KEY_ITEM(Numpad5);
			KEY_ITEM(Numpad6);
			KEY_ITEM(Numpad7);
			KEY_ITEM(Numpad8);
			KEY_ITEM(Numpad9);
			KEY_ITEM(F1);
			KEY_ITEM(F2);
			KEY_ITEM(F3);
			KEY_ITEM(F4);
			KEY_ITEM(F5);
			KEY_ITEM(F6);
			KEY_ITEM(F7);
			KEY_ITEM(F8);
			KEY_ITEM(F9);
			KEY_ITEM(F10);
			KEY_ITEM(F11);
			KEY_ITEM(F12);
			KEY_ITEM(F13);
			KEY_ITEM(F14);
		}
		return ret;
	}

	std::string Controls::BtnToString(sf::Keyboard::Key t_btn)
	{
		std::string ret = "";
		switch (t_btn)
		{
			BTN_ITEM(Left);
			BTN_ITEM(Right);
			BTN_ITEM(Middle);
		}
		return ret;
	}

}