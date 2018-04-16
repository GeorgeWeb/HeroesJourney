#include "PauseMenu.hpp"
#include "Encounters/Tutorial.hpp"
#include "MapScene.hpp"

#include <sstream>
#include <iostream>

#include <Engine/ECM/Components/TextComponent.hpp>
#include <Engine/ECM/Components/SpriteComponent.hpp>
#include "FinalStory.hpp"
#include "MeetBard.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	FinalStoryScene::FinalStoryScene(GameDataRef t_data) :
		m_data(t_data),
		m_turn(DIALOG_TURN::LEFT)
	{ }

	void FinalStoryScene::Init()
	{
		// load assets
		m_data->assets.LoadTexture("Tex_FinalStoryBG", FINAL_STORY_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_StoryMainHero", STORY_INTRO_SCENE_HERO);
		m_data->assets.LoadTexture("Tex_StoryCaptain", STORY_INTRO_SCENE_CAPATIN);
		m_data->assets.LoadTexture("Tex_StoryMainHeroIcon", STORY_INTRO_SCENE_HERO_ICON);
		m_data->assets.LoadTexture("Tex_StoryCaptainIcon", STORY_INTRO_SCENE_CAPATIN_ICON);

		//Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_zDialogBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_FinalStoryBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);
		bg->Init();

		// Click to continue text
		auto continueTxt = std::make_shared<Entity>();
		auto titleTxtComp = continueTxt->AddComponent<TextComponent>("C_ContinueText");
		titleTxtComp->GetText().setFont(m_data->assets.GetFont("Font_Pixel"));
		titleTxtComp->GetText().setCharacterSize(18);
		titleTxtComp->GetText().setString("Click to continue...");
		titleTxtComp->GetText().setStyle(sf::Text::Bold);
		titleTxtComp->GetText().setColor(sf::Color(55, 55, 55, 255));
		continueTxt->SetPosition(sf::Vector2f(
			(SCREEN_WIDTH - titleTxtComp->GetText().getGlobalBounds().width) * .97f,
			(SCREEN_HEIGHT - titleTxtComp->GetText().getGlobalBounds().height) * 0.03f));
		continueTxt->SetAlive(true);
		continueTxt->SetVisible(true);

		// create entities
		m_dialog = std::make_shared<Dialog>();
		// Conversation
		m_dialog->AddConversation({
			"Knight: The evil frost mage have been slain, ", "The Castle of Ice is in ruins and the kingdom is finally at peace. ", // LEFT CHAR
			"", "", // RIGHT CHAR
			"Anton: Thank you adventurer for joining us. We hope you had as much fun , ", " playing the game as we did making it.", // LEFT CHAR
			"", "",  // RIGHT CHAR
			"Georgi: Sam if you are reading this, congratulations. ", "Also i have lost a bet. :)" //LEFT CHAR

			});
		m_dialog->DisplayConvo(0, 2, m_data->assets.GetFont("Font_Pixel"));
		m_offset += 2;
		// dialog characters
		m_dialog->SetLeftCharacterImage(m_data->assets.GetTexture("Tex_StoryMainHero"));
		m_dialog->SetRightCharacterImage(m_data->assets.GetTexture("Tex_StoryCaptain"));
		// sprites settings
		auto hero = m_dialog->GetComponent<SpriteComponent>("C_DialogLCharacterSprite");
		hero->GetSprite().setPosition(sf::Vector2f(500.0f, 250.0f));
		hero->GetSprite().scale(5.0f, 5.0f);
		auto captain = m_dialog->GetComponent<SpriteComponent>("C_DialogRCharacterSprite");
		captain->GetSprite().scale(0.0001f, 0.0001f);
		captain->GetSprite().setPosition(sf::Vector2f(700.0f, 250.0f));
		// Initialise dialog properties
		m_dialog->Init();

		// ui frame
		auto uiFrame = std::make_shared<Entity>();
		auto uiFrameSprite = uiFrame->AddComponent<SpriteComponent>("C_FinalStoryUIFrameSprite");
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
		AddEntity("E_zFinalStoryDialogBG", bg);
		AddEntity("E_aFinalStoryContinueText", continueTxt);
		AddEntity("E_mFinalStoryDialog", m_dialog);
		AddEntity("E_xFinalStoryUIFrame", uiFrame);


		//
		m_data->gm.battlePassed = true;
	}

	void FinalStoryScene::HandleInput()
	{
		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView(event.size.width, event.size.height);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				auto mapscene = std::make_unique<MapScene>(MapScene(m_data));
				m_data->machine.AddState(std::move(mapscene));
			}
			auto bgSprite = m_data->ents.Find<Entity>("E_zFinalStoryDialogBG")->GetComponent<SpriteComponent>("C_zDialogBGSprite");
			if (bgSprite->IsClickable() && m_data->input.isClicked(bgSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				std::cout << m_offset << std::endl;
				// Conversation
				if (m_dialog->GetTexts().size() > 2 + m_offset)
				{
					if (m_dialog->GetTexts()[m_offset] == "")
					{
						m_offset += 2;
						std::cout << "empty /n";
					}
				}

				m_dialog->DisplayConvo(0 + m_offset, 2 + m_offset, m_data->assets.GetFont("Font_Pixel"));
				m_offset += 2;
				std::cout << "not empty /n";
				//m_turn = (m_turn == DIALOG_TURN::LEFT) ? DIALOG_TURN::RIGHT : m_turn = DIALOG_TURN::LEFT;

			}
		}
	}

	void FinalStoryScene::Update(float t_delatTime)
	{
		if (m_dialog->HasFinished())
		{
			auto mapscene = std::make_shared<MapScene>(MapScene(m_data));
			m_data->machine.AddState(mapscene);

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
	void FinalStoryScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void FinalStoryScene::AddEntity(const std::string & t_name, std::shared_ptr<ECM::Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}

}