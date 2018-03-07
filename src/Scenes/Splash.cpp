#include "Splash.hpp"
#include "MainMenu.hpp"

#include <sstream>
#include <iostream>

#include <Engine/ECM/Components/ShapeComponent.hpp>
#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>

namespace HJ {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	SplashScene::SplashScene(GameDataRef t_data)
		: m_data(t_data)
	{
		// Won't use for more initialization, hence I will use the Init() func
	}

	void SplashScene::Init()
	{
		// Load resources
		m_data->assets.LoadTexture("Tex_SplashBG", SPLASH_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_LogoSheet", SPLASH_GAME_LOGO_SPRITESHEET);
		m_data->assets.LoadFont("Font_Pixel", GAME_FONT);

		// Create entities ...
		// Background
		auto bg = std::make_shared<Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_SplashBGSprite");
		// define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SplashBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 155));
		// set properties
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		// Logo
		m_logo = std::make_shared<AnimatedLogo>();
		// initialize data
		m_logo->SetSprite(m_data->assets.GetTexture("Tex_LogoSheet"), sf::IntRect(0, 0, 550, 250));
		// set more properties
		m_logo->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_logo->GetSpriteComponent()->GetSprite().getGlobalBounds().width) * 0.5f, 50.0f));
		m_logo->GetAnimatorComponent()->AddAnimation("Anim_GameLogo", Animation(&m_data->assets.GetTexture("Tex_LogoSheet"), sf::Vector2u(6, 7), 0.05f, true, false));
		m_logo->GetAnimatorComponent()->GetAnimation("Anim_GameLogo").SetRow(0);
		m_logo->Init();

		// Add to ents (local) map
		AddEntity("E_zSplashBG", bg);
		AddEntity("E_GameLogo", m_logo);
	}

	void SplashScene::HandleInput()
	{
		sf::Event event;
		while (Renderer::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Renderer::GetWin().close();

			// Keyboard input
			auto bgSprite = m_data->ents.Find<Entity>("E_zSplashBG")->GetComponent<SpriteComponent>("C_SplashBGSprite");
			// 'Press ANY key OR button to continue!' type of game
			if (event.type == sf::Event::EventType::KeyPressed ||
				m_data->input.isClicked(bgSprite->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_shouldFade = true;
			}
		}
	}

	void SplashScene::Update(float t_delatTime)
	{
		auto bgSpriteComp = m_data->ents.Find<Entity>("E_zSplashBG")->GetComponent<SpriteComponent>("C_SplashBGSprite");
		if (m_shouldFade)
		{
			auto fadedColor = sf::Color(bgSpriteComp->GetSprite().getColor().r,
				bgSpriteComp->GetSprite().getColor().g,
				bgSpriteComp->GetSprite().getColor().b,
				bgSpriteComp->GetSprite().getColor().a - t_delatTime * 100.0f);

			bgSpriteComp->GetSprite().setColor(fadedColor);

			if (bgSpriteComp->GetSprite().getColor().a == 0)
			{
				m_shouldFade = false;
				
				// Switch scenes (to Main Menu)
				auto mainMenuState = std::make_unique<MainMenuScene>(MainMenuScene(m_data));
				m_data->machine.AddState(std::move(mainMenuState));
			}
		}

		// animate logo
		m_logo->Animate("Anim_GameLogo");

		// update all entities
		m_data->ents.Update(m_entities, t_delatTime);
	}

	void SplashScene::Draw(float t_deltaTime)
	{
		// render all entities
		m_data->ents.Render(m_entities);
	}

	void SplashScene::AddEntity(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}

}