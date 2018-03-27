#include "Dialog.hpp"
#include "../DEFINITIONS.hpp"

using namespace Engine::ECM;
using namespace Engine::Components;

namespace HJ { namespace Entities {
	
	Dialog::Dialog() :
		m_background(AddComponent<SpriteComponent>("C_zDialogBGSprite")),
		m_lCharacter(AddComponent<SpriteComponent>("C_DialogLCharacterSprite")),
		m_rCharacter(AddComponent<SpriteComponent>("C_DialogRCharacterSprite"))
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
		m_background->independent = false;
		m_lCharacter->independent = true;
		m_rCharacter->independent = true;
	}

	void Dialog::Update(float t_deltaTime)
	{
		Entity::Update(t_deltaTime);
	}

	void Dialog::Render()
	{
		Entity::Render();
	}

	void Dialog::SetBackgroundImage(const sf::Texture& t_texture)
	{
		m_background->GetSprite().setTexture(t_texture);
		m_background->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void Dialog::SetLeftCharacterImage(const sf::Texture& t_texture)
	{
		m_lCharacter->GetSprite().setTexture(t_texture);
		m_lCharacter->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void Dialog::SetRightCharacterImage(const sf::Texture& t_texture)
	{
		m_rCharacter->GetSprite().setTexture(t_texture);
		m_rCharacter->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void Dialog::AddConversation(const unsigned int t_lines)
	{
		if (!m_conversation.empty())
		{
			// effect on hide
			FadeOut();

			// empty the vector / erase the current texts
			m_conversation.clear();
		}
		else
		{
			// add the texts
			m_conversation.reserve(t_lines);
			for (unsigned int i = 1; i <= t_lines; i++)
			{
				auto text = AddComponent<TextComponent>("C_aDialogConvoText" + i);
				text->independent = true;
				m_conversation.push_back(text);
			}

			// effect on show
			FadeIn();
		}
	}

	std::vector<std::shared_ptr<TextComponent>>& Dialog::GetConversation()
	{
		return m_conversation;
	}

	void Dialog::FadeIn()
	{
		for (auto convo : m_conversation)
		{
			convo->GetText().setColor(sf::Color(
				convo->GetText().getColor().r,
				convo->GetText().getColor().g,
				convo->GetText().getColor().b,
				255
			));
		}
	}

	void Dialog::FadeOut()
	{
		for (auto convo : m_conversation)
		{
			convo->GetText().setColor(sf::Color(
				convo->GetText().getColor().r,
				convo->GetText().getColor().g,
				convo->GetText().getColor().b,
				0
			));
		}
	}

} }