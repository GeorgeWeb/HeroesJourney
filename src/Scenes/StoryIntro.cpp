#include "PauseMenu.hpp"
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

	StoryIntroScene::StoryIntroScene(GameDataRef t_data)
		: m_data(t_data)
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

		// create entities
		m_dialog = std::make_shared<Dialog>();
		m_dialog->AddConversation(2);
		m_dialog->SetBackgroundImage(m_data->assets.GetTexture("Tex_StoryIntroBG"));
		m_dialog->SetLeftCharacterImage(m_data->assets.GetTexture("Tex_StoryMainHero"));
		m_dialog->SetRightCharacterImage(m_data->assets.GetTexture("Tex_StoryCaptain"));
		// sprites settings
		auto bg = m_dialog->GetComponent<SpriteComponent>("C_zDialogBGSprite");
		bg->GetSprite().setPosition(sf::Vector2f(0.0f, 0.0f));
		auto hero = m_dialog->GetComponent<SpriteComponent>("C_DialogLCharacterSprite");
		hero->GetSprite().setPosition(sf::Vector2f(400.0f, 250.0f));
		auto captain = m_dialog->GetComponent<SpriteComponent>("C_DialogRCharacterSprite");
		captain->GetSprite().setPosition(sf::Vector2f(600.0f, 250.0f));
		// conversation text settings
		auto text1 = m_dialog->GetConversation().back();
		text1->SetFont(m_data->assets.GetFont("Font_Pixel"));
		text1->GetText().setString("Test conversation line.");
		text1->GetText().setPosition(sf::Vector2f(300.0f, 400.0f));
		//text1->independent = true;
		// Initialise stuff
		m_dialog->Init();
		
		std::cout << m_dialog->GetConversation().size() << std::endl;
		std::cout << text1->GetText().getPosition().x << " , " << text1->GetText().getPosition().y << std::endl;
		std::cout << "Independent? " << text1->independent << std::endl;
		
		std::string txt = text1->GetText().getString();
		std::cout << txt << std::endl;
		
		// populate the entities container
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				//switch to map
				auto gameMap = std::make_unique<MapScene>(MapScene(m_data));
				m_data->machine.AddState(std::move(gameMap));
			}
		}
	}

	void StoryIntroScene::Update(float t_delatTime)
	{
		// TODO: Timers and stuff...

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