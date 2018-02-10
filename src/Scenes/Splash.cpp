#include "Splash.hpp"

#include <sstream>
#include <iostream>

#include <Engine/ECM/BaseComponents/SpriteComponent.hpp>
#include <Engine/ECM/BaseComponents/AnimatorComponent.hpp>

namespace HJ {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::Components;
	//using namespace HJ::Components;

	SplashScene::SplashScene(GameDataRef t_data)
		: m_data(t_data)
	{
		// Won't use for more initialization, hence I will use the Init() func
	}

	void SplashScene::Init()
	{
		// Load resources
		m_data->assets.LoadTexture("Tex_SplashBG", SPLASH_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_HeroSheet", MAIN_HERO_SPRITESHEET);
		m_data->assets.LoadFont("Font_GameTitle", GAME_TITLE_FONT);

		// Restore entity manager to non-visible ents
		for (auto ent : m_data->ents.GetEntsDictionary()) ent.second->SetVisible(false);

		// Declare local entities map container
		std::map<std::string, std::shared_ptr<ECM::Entity>> ents;

		// Create entities ...
		// Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_SplashBGSprite");
		// define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SplashBG"));
		bgSprite->GetSprite().setColor(sf::Color(128, 200, 128, 200));
		bgSprite->GetSprite().setOrigin(bgSprite->GetSprite().getScale().x, bgSprite->GetSprite().getScale().y);
		// set properties
		bg->SetVisible(true);
		bg->SetAlive(true);

		// Hero
		auto hero = std::make_shared<ECM::Entity>();
		auto heroSprite = hero->AddComponent<SpriteComponent>("C_HeroSprite");
		auto heroAnim = hero->AddComponent<AnimatorComponent>("C_HeroAnimator");
		// define hero sprite
		heroSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_HeroSheet"));
		heroSprite->GetSprite().setOrigin(heroSprite->GetSprite().getScale().x, heroSprite->GetSprite().getScale().y);
		heroSprite->GetSprite().setScale(sf::Vector2f(3.0f, 3.0f));
		// define hero animation
		heroAnim->SetAnimation(&m_data->assets.GetTexture("Tex_HeroSheet"), sf::Vector2u(4, 4), 0.3f);
		// set properties
		hero->SetPosition(sf::Vector2f((SCREEN_WIDTH - heroSprite->GetSprite().getGlobalBounds().width) * 0.5f,
									(SCREEN_HEIGHT - heroSprite->GetSprite().getGlobalBounds().height) * 0.5f));
		hero->SetVisible(true);
		hero->SetAlive(true);

		// Add to ents (local) map		
		ents.insert_or_assign("E_SplashBG", bg);
		ents.insert_or_assign("E_Hero", hero);
		
		// :if entity is not in the entity manager, then it will be added:
		m_data->ents.PopulateEntsDictionary(ents);
	}

	void SplashScene::HandleInput()
	{
		sf::Event event;
		while (Renderer::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Renderer::GetWin().close();

			// Keyboard input
			auto bgSpriteComp = m_data->ents.Find("E_SplashBG")->GetComponent("C_SplashBGSprite");

			// 'Press ANY key OR button to continue!' type of game
			if (event.type == sf::Event::EventType::KeyPressed || 
				m_data->input.isClicked(bgSpriteComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				std::cout << "Wassup :P finally worked! :D\n";
				m_shouldFade = true;
			}
		}
	}

	void SplashScene::Update(float t_delatTime)
	{
		auto bgSpriteComp = m_data->ents.Find("E_SplashBG")->GetComponent("C_SplashBGSprite");
		if (m_shouldFade)
		{
			auto fadedColor = sf::Color(bgSpriteComp->GetSprite().getColor().r,
										bgSpriteComp->GetSprite().getColor().g,
										bgSpriteComp->GetSprite().getColor().b,
										bgSpriteComp->GetSprite().getColor().a - t_delatTime);

			bgSpriteComp->GetSprite().setColor(fadedColor);

			if (bgSpriteComp->GetSprite().getColor().a == 0)
			{
				m_shouldFade = false;
				
				// Switch scenes (to Main Menu)
				//auto mainMenuState = std::make_unique<MainMenuScene>(MainMenuScene(m_data));
				//m_data->machine.AddState(std::move(mainMenuState));
			}
		}

		m_data->ents.Update(t_delatTime);

		m_data->ents.Find("E_Hero")->GetComponent("C_HeroSprite")->GetSprite().setTextureRect(
			m_data->ents.Find("E_Hero")->GetComponent("C_HeroAnimator")->GetAnimation().uvRect);
	}

	void SplashScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render();
	}

}