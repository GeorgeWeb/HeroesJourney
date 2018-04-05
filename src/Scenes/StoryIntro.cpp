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
	{ 
		InitSceneView();
	}

	void StoryIntroScene::Init()
	{
		// load assets
		m_data->assets.LoadTexture("Tex_StoryIntroBG", STORY_INTRO_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_StoryMainHero", STORY_INTRO_SCENE_HERO);
		m_data->assets.LoadTexture("Tex_StoryCaptain", STORY_INTRO_SCENE_CAPATIN);
		m_data->assets.LoadTexture("Tex_StoryMainHeroIcon", STORY_INTRO_SCENE_HERO_ICON);
		m_data->assets.LoadTexture("Tex_StoryCaptainIcon", STORY_INTRO_SCENE_CAPATIN_ICON);

		//Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_zDialogBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StoryIntroBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		bgSprite->GetSprite().scale(0.9f, 0.85f);
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);
		bg->Init();

		// create entities
		m_dialog = std::make_shared<Dialog>();
		// Conversation
		m_dialog->AddConversation({ 
			"Hero: Test line #1", "- Test line #2", // LEFT CHAR
			"Captain: Test line #3", "- Test line #4", // RIGHT CHAR
			"Hero: Test line #5", "- Test line #6", // LEFT CHAR
			"Captain: Test line #7", "- Test line #8"  // RIGHT CHAR
		});
		m_dialog->DisplayConvo(0, 2, m_data->assets.GetFont("Font_Pixel"));
		m_offset += 2;
		// dialog characters
		m_dialog->SetLeftCharacterImage(m_data->assets.GetTexture("Tex_StoryMainHero"));
		m_dialog->SetRightCharacterImage(m_data->assets.GetTexture("Tex_StoryCaptain"));
		// sprites settings
		auto hero = m_dialog->GetComponent<SpriteComponent>("C_DialogLCharacterSprite");
		hero->GetSprite().setPosition(sf::Vector2f(500.0f, 350.0f));
		hero->GetSprite().scale(3.0f, 3.0f);
		auto captain = m_dialog->GetComponent<SpriteComponent>("C_DialogRCharacterSprite");
		captain->GetSprite().scale(3.0f, 3.0f);
		captain->GetSprite().setPosition(sf::Vector2f(700.0f, 350.0f));
		// Initialise dialog properties
		m_dialog->Init();
		
		// populate the entities container
		AddEntity("E_zDialogBG", bg);
		AddEntity("E_mStoryIntroDialog", m_dialog);
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				////switch to tutorial scene
				//auto tutorial = std::make_unique<Encounters::TutorialScene>(Encounters::TutorialScene(m_data));
				//m_data->machine.AddState(std::move(tutorial));

				auto mapscene = std::make_unique<MapScene>(MapScene(m_data));
				m_data->machine.AddState(std::move(mapscene));
			}

			auto bgSprite = m_data->ents.Find<Entity>("E_zDialogBG")->GetComponent<SpriteComponent>("C_zDialogBGSprite");
			if (bgSprite->IsClickable() && m_data->input.isClicked(bgSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				std::cout << m_offset << std::endl;
				// Conversation
				m_dialog->DisplayConvo(0 + m_offset, 2 + m_offset, m_data->assets.GetFont("Font_Pixel"));
				m_offset += 2;

				m_turn = (m_turn == DIALOG_TURN::LEFT) ? DIALOG_TURN::RIGHT : m_turn = DIALOG_TURN::LEFT;
			}
		}
	}

	void StoryIntroScene::Update(float t_delatTime)
	{
		if (m_dialog->HasFinished())
		{
			//switch to tutorial scene
			auto tutorial = std::make_unique<Encounters::TutorialScene>(Encounters::TutorialScene(m_data));
			m_data->machine.AddState(std::move(tutorial));
		}
		else
		{
			switch (m_turn)
			{
				case DIALOG_TURN::LEFT:
					// Conversation
					// HIGHLIGHT (& IF NEEDED CHANGE) TEXTURE
					m_dialog->GetLeftCharacter()->GetSprite().setColor(sf::Color::Green);
					m_dialog->GetRightCharacter()->GetSprite().setColor(sf::Color::White);
					break;
				case DIALOG_TURN::RIGHT:
					// Conversation
					// HIGHLIGHT (& IF NEEDED CHANGE) TEXTURE
					m_dialog->GetRightCharacter()->GetSprite().setColor(sf::Color::Green);
					m_dialog->GetLeftCharacter()->GetSprite().setColor(sf::Color::White);
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