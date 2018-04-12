#include "PauseMenu.hpp"
#include "Encounters/Tutorial.hpp"
#include "MapScene.hpp"

#include <sstream>
#include <iostream>

#include <Engine/ECM/Components/TextComponent.hpp>
#include <Engine/ECM/Components/SpriteComponent.hpp>
#include "MeetRogue.hpp"
#include "FinalStory.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	MeetRogueScene::MeetRogueScene(GameDataRef t_data) :
		m_data(t_data),
		m_turn(DIALOG_TURN::LEFT)
	{
		InitSceneView();
	}

	void MeetRogueScene::Init()
	{
		// load assets
		m_data->assets.LoadTexture("Tex_MeetRogueBG", MEET_ROGUE_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_StoryMainHero", STORY_INTRO_SCENE_HERO);
		m_data->assets.LoadTexture("Tex_StoryCaptain", HERO_ROGUE_SPRITE);
		m_data->assets.LoadTexture("Tex_StoryMainHeroIcon", STORY_INTRO_SCENE_HERO_ICON);
		m_data->assets.LoadTexture("Tex_StoryCaptainIcon", HERO_ROGUE_SPRITE);
		m_data->assets.LoadTexture("Tex_MeetRogueUIFrame", ENCOUNTER_UI_FRAME);


		//Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_zDialogBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_MeetRogueBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
	
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);
		bg->Init();

		// create entities
		m_dialog = std::make_shared<Dialog>();
		// Conversation
		m_dialog->AddConversation({
			"Rogue: Greetings adventurers! That cyclops was making this mountain ", "Unpassable. You have my thanks ", // LEFT CHAR
			"Knight: We had no choice. Our journey to defeat the evil frost mage ", "Led us to the mountain pass. ", // RIGHT CHAR
			"Rogue: Regradless I am greatful. Allow me to offer my bow to  ", "Your party. The frost mage must be brought to justice. ", // LEFT CHAR
			"Knight: We require all the aid we can get. You are welcome woodsman. ", "We head to the coast next! "  // RIGHT CHAR
			});
		m_dialog->DisplayConvo(0, 2, m_data->assets.GetFont("Font_Pixel"));
		m_offset += 2;
		// dialog characters
		m_dialog->SetLeftCharacterImage(m_data->assets.GetTexture("Tex_StoryCaptain"));
		m_dialog->SetRightCharacterImage(m_data->assets.GetTexture("Tex_StoryMainHero")); 
		// sprites settings
		auto hero = m_dialog->GetComponent<SpriteComponent>("C_DialogLCharacterSprite");
		hero->GetSprite().setPosition(sf::Vector2f(350.0f, 250.0f));
		hero->GetSprite().scale(5.0f, 5.0f);
		auto captain = m_dialog->GetComponent<SpriteComponent>("C_DialogRCharacterSprite");
		captain->GetSprite().scale(5.0f, 5.0f);
		captain->GetSprite().setPosition(sf::Vector2f(800.0f, 250.0f));
		// Initialise dialog properties
		m_dialog->Init();

		// ui frame
		auto uiFrame = std::make_shared<Entity>();
		auto uiFrameSprite = uiFrame->AddComponent<SpriteComponent>("C_MeetRogueUIFrameSprite");
		uiFrameSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		uiFrameSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_MeetRogueUIFrame"));
		uiFrameSprite->GetSprite().scale(1.0f, 0.9f);
		//properties
		uiFrame->SetPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - uiFrameSprite->GetSprite().getGlobalBounds().height));
		uiFrame->SetVisible(true);
		uiFrame->SetAlive(true);
		uiFrame->Init();

		// populate the entities container
		AddEntity("E_zMeetRogueDialogBG", bg);
		AddEntity("E_mMeetRogueDialog", m_dialog);
		AddEntity("E_xMeetRogueUIFrame", uiFrame);

	}

	void MeetRogueScene::HandleInput()
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
				////switch to tutorial scene
				//auto tutorial = std::make_unique<Encounters::TutorialScene>(Encounters::TutorialScene(m_data));
				//m_data->machine.AddState(std::move(tutorial));

				auto mapscene = std::make_unique<MapScene>(MapScene(m_data));
				m_data->machine.AddState(std::move(mapscene));
			}

			auto bgSprite = m_data->ents.Find<Entity>("E_zMeetRogueDialogBG")->GetComponent<SpriteComponent>("C_zDialogBGSprite");
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
				m_turn = (m_turn == DIALOG_TURN::LEFT) ? DIALOG_TURN::RIGHT : m_turn = DIALOG_TURN::LEFT;

			}
		}
	}

	void MeetRogueScene::Update(float t_delatTime)
	{
		if (m_dialog->HasFinished())
		{
			//switch to tutorial scene
			auto FinalStory = std::make_unique<FinalStoryScene>(FinalStoryScene(m_data));
			m_data->machine.AddState(std::move(FinalStory));

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

	void MeetRogueScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void MeetRogueScene::AddEntity(const std::string & t_name, std::shared_ptr<ECM::Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}

}