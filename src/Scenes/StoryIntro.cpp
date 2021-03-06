#include "PauseMenu.hpp"
#include "Encounters/Tutorial.hpp"
#include "MapScene.hpp"

#include <sstream>
#include <iostream>

#include <Engine/ECM/Components/TextComponent.hpp>
#include <Engine/ECM/Components/SpriteComponent.hpp>
#include "StoryIntro.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	StoryIntroScene::StoryIntroScene(GameDataRef t_data) :
		m_data(t_data),
		m_turn(DIALOG_TURN::LEFT)
	{ }

	void StoryIntroScene::Init()
	{
		// load assets
		m_data->assets.LoadTexture("Tex_StoryIntroBG", STORY_INTRO_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_StoryMainHero", STORY_INTRO_SCENE_HERO);
		m_data->assets.LoadTexture("Tex_StoryCaptain", STORY_INTRO_SCENE_CAPATIN);
		m_data->assets.LoadTexture("Tex_StoryMainHeroIcon", STORY_INTRO_SCENE_HERO_ICON);
		m_data->assets.LoadTexture("Tex_StoryCaptainIcon", STORY_INTRO_SCENE_CAPATIN_ICON);
		m_data->assets.LoadTexture("Tex_UIFrame", ENCOUNTER_UI_FRAME);

		//Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_zDialogBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StoryIntroBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);
		bg->Init();

		// Click to continue text
		auto continueTxt = std::make_shared<Entity>();
		auto continueTxtComp = continueTxt->AddComponent<TextComponent>("C_ContinueText");
		continueTxtComp->GetText().setFont(m_data->assets.GetFont("Font_Pixel"));
		continueTxtComp->GetText().setCharacterSize(18);
		continueTxtComp->GetText().setString("Click to continue...");
		continueTxtComp->GetText().setStyle(sf::Text::Bold);
		continueTxtComp->GetText().setColor(sf::Color(255, 255, 255, 255));
		continueTxt->SetPosition(sf::Vector2f(
			(SCREEN_WIDTH - continueTxtComp->GetText().getGlobalBounds().width) * .5f,
			(SCREEN_HEIGHT - continueTxtComp->GetText().getGlobalBounds().height) * 0.03f));
		continueTxt->SetAlive(true);
		continueTxt->SetVisible(true);

		// create entities
		m_dialog = std::make_shared<Dialog>();
		// Conversation
		m_dialog->AddConversation({
			"Narrator: Welcome dear adventurer. Join me as i tell you the story", "- of how you lead the heroes of this land on their epic quest", // LEFT CHAR
			"", "", // RIGHT CHAR
			"Narrator: against the evil frost mage and his minions. ", "", // LEFT CHAR
			"", "",  // RIGHT CHAR
			"Narrator: Our story begins with the kingdom of our heroes besieged ", "by the forces of the evil frost mage. ", //LEFT CHAR
			"","", //Right char
			"Narrator: The brave Knight takes up arms to defend the castle. ",""
			});
		m_dialog->DisplayConvo(0, 2, m_data->assets.GetFont("Font_Pixel"));
		m_offset += 2;
		// dialog characters
		m_dialog->SetLeftCharacterImage(m_data->assets.GetTexture("Tex_StoryMainHero"));
		m_dialog->SetRightCharacterImage(m_data->assets.GetTexture("Tex_StoryCaptain"));
		// sprites settings
		auto hero = m_dialog->GetComponent<SpriteComponent>("C_DialogLCharacterSprite");
		hero->GetSprite().setPosition(sf::Vector2f(500.0f, 200.0f));
		hero->GetSprite().scale(5.0f, 5.0f);

		// Initialise dialog properties
		m_dialog->Init();

		// ui frame
		auto uiFrame = std::make_shared<Entity>();
		auto uiFrameSprite = uiFrame->AddComponent<SpriteComponent>("C_StoryIntroUIFrameSprite");
		uiFrameSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		uiFrameSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UIFrame"));
		uiFrameSprite->GetSprite().scale(1.0f, 0.9f);
		//properties
		uiFrame->SetPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - uiFrameSprite->GetSprite().getGlobalBounds().height));
		uiFrame->SetVisible(true);
		uiFrame->SetAlive(true);
		uiFrame->Init();

		// Regulate main theme
		m_data->assets.GetMusic("AdventureTheme").pause();
		m_data->assets.GetMusic("AdventureTheme").setVolume(15);
		m_data->assets.GetMusic("AdventureTheme").play();

		// populate the entities container
		AddEntity("E_zDialogBG", bg);
		AddEntity("E_aStoryIntroContinueText", continueTxt);
		AddEntity("E_mStoryIntroDialog", m_dialog);
		AddEntity("E_xStoryIntroUIFrame", uiFrame);
	}

	void StoryIntroScene::HandleInput()
	{
		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView(event.size.width, event.size.height);

			if (sf::Keyboard::isKeyPressed(Controls::GetKey("Skip")))
			{
				// switch to tutorial scene
				auto tutorial = std::make_shared<Encounters::TutorialScene>(Encounters::TutorialScene(m_data));
				m_data->machine.AddState(tutorial);
			}

			auto bgSprite = m_data->ents.Find<Entity>("E_zDialogBG")->GetComponent<SpriteComponent>("C_zDialogBGSprite");
			if (bgSprite->IsClickable() && m_data->input.isClicked(bgSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				// Conversation
				if (m_dialog->GetTexts().size() > 2 + m_offset)
				{
					if (m_dialog->GetTexts()[m_offset] == "")
					{
						m_offset += 2;
					}
				}

				m_dialog->DisplayConvo(0 + m_offset, 2 + m_offset, m_data->assets.GetFont("Font_Pixel"));
				m_offset += 2;
				//m_turn = (m_turn == DIALOG_TURN::LEFT) ? DIALOG_TURN::RIGHT : m_turn = DIALOG_TURN::LEFT;
			}
		}
	}

	void StoryIntroScene::Update(float t_delatTime)
	{
		if (m_dialog->HasFinished())
		{
			// switch to tutorial scene
			auto tutorial = std::make_shared<Encounters::TutorialScene>(Encounters::TutorialScene(m_data));
			m_data->machine.AddState(tutorial);
		}
		else
		{
			switch (m_turn)
			{
			case DIALOG_TURN::LEFT:
				// Conversation
				// HIGHLIGHT (& IF NEEDED CHANGE) TEXTURE
				m_dialog->GetLeftCharacter()->GetSprite().setColor(sf::Color::White);
				m_dialog->GetRightCharacter()->GetSprite().setColor(sf::Color::Transparent);
				break;
			case DIALOG_TURN::RIGHT:
				// Conversation
				// HIGHLIGHT (& IF NEEDED CHANGE) TEXTURE
				m_dialog->GetRightCharacter()->GetSprite().setColor(sf::Color::White);
				m_dialog->GetLeftCharacter()->GetSprite().setColor(sf::Color::Transparent);
				break;
			default:
				break;
			}
		}

		m_data->ents.Update(m_entities, t_delatTime);
	}

	void StoryIntroScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void StoryIntroScene::AddEntity(const std::string & t_name, std::shared_ptr<ECM::Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}

}