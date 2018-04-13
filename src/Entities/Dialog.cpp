#include "Dialog.hpp"
#include "../DEFINITIONS.hpp"

using namespace Engine::ECM;
using namespace Engine::Components;

namespace HJ { namespace Entities {
	
	Dialog::Dialog() :
		m_lCharacter(AddComponent<SpriteComponent>("C_DialogLCharacterSprite")),
		m_rCharacter(AddComponent<SpriteComponent>("C_DialogRCharacterSprite")),
		m_finished(false)
	{ }

	Dialog* Dialog::GetType()
	{
		return this;
	}

	void Dialog::Init()
	{
		// defaults
		SetAlive(true);
		SetVisible(true);
		m_lCharacter->independent = true;
		m_rCharacter->independent = true;
		m_conversation.reserve(100);
	}

	void Dialog::Update(float t_deltaTime)
	{
		Entity::Update(t_deltaTime);
	}

	void Dialog::Render()
	{
		Entity::Render();
	}

	void Dialog::SetLeftCharacterImage(const sf::Texture& t_texture)
	{
		m_lCharacter->GetSprite().setTexture(t_texture);
		m_lCharacter->GetSprite().setColor(sf::Color::White);
	}

	void Dialog::SetRightCharacterImage(const sf::Texture& t_texture)
	{
		m_rCharacter->GetSprite().setTexture(t_texture);
		m_rCharacter->GetSprite().setColor(sf::Color::White);
	}

	void Dialog::AddConversation(std::vector<std::string> t_texts)
	{
		m_texts = t_texts;
		const unsigned int lines = m_texts.size();

		// add the texts
		for (unsigned int i = 0; i < lines; i++)
		{
			auto text = AddComponent<TextComponent>("C_xDialogConvoText" + std::to_string(i));
			text->independent = true;
			m_conversation.push_back(text);
		}
	}

	std::vector<std::shared_ptr<TextComponent>>& Dialog::GetConversation()
	{
		return m_conversation;
	}

	void Dialog::DisplayConvo(int t_start, int t_end, const sf::Font& t_font)
	{
		if (t_start > m_conversation.size()
		|| t_start >= m_conversation.size() && t_end > m_conversation.size()
		|| t_start > t_end) m_finished = true;
		else
		{
			// hide convo txt
			for (auto convo : m_conversation) 
				convo->GetText().setColor(sf::Color(255, 255, 255, 0));

			// show convo txt
			auto count = 0;
			for (int i = t_start; i < t_end; i++)
			{
				auto& convo = m_conversation.at(i);
			

				// show
				convo->GetText().setColor(sf::Color::White);

				/* < Display Logic */
				convo->SetFont(t_font);
				convo->GetText().setString(m_texts.at(i));
				convo->GetText().setStyle(sf::Text::Bold);
				convo->GetText().setCharacterSize(24);
				unsigned int offsetY = count * 50;
				convo->GetText().setPosition(sf::Vector2f((SCREEN_WIDTH * 0.5f - convo->GetText().getGlobalBounds().width * 0.5f) , 590.0f + offsetY));
				/* /> Display Logic */
				count++;
			}
		}
	}

} }