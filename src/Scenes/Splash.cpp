#include "Splash.hpp"
#include "MainMenu.hpp"

#include <sstream>
#include <iostream>

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>
#include <Engine/ECM/Components/TextComponent.hpp>

namespace HJ {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	SplashScene::SplashScene(GameDataRef t_data) : m_data(t_data)
	{
		InitSceneView();
	}

	void SplashScene::Init()
	{
		/* < GLOBAL PRE-LOAD */

		// Load resources (to be used repeatingly)
		// General assets
		m_data->assets.LoadFont("Font_Pixel", GAME_FONT);
		m_data->assets.LoadTexture("Tex_StandardBtn", STANDARD_BTN);
		// Building assets
		m_data->assets.LoadTexture("Tex_Infirmary", CASTLE_SCENE_INFIRMARY);
		m_data->assets.LoadTexture("Tex_Blacksmith", CASTLE_SCENE_BLACKSMITH);
		m_data->assets.LoadTexture("Tex_Library", CASTLE_SCENE_LIBRARY);
		m_data->assets.LoadTexture("Tex_Inn", CASTLE_SCENE_INN);
		m_data->assets.LoadTexture("Tex_GeneralStore", CASTLE_SCENE_GENERAL_STORE);
		// Hero assets
		m_data->assets.LoadTexture("Tex_HeroKnight", HERO_KNIGHT_SPRITE);
		m_data->assets.LoadTexture("Tex_HeroBard", HERO_BARD_SPRITE);
		m_data->assets.LoadTexture("Tex_HeroSorc", HERO_SORC_SPRITE);
		m_data->assets.LoadTexture("Tex_HeroRogue", HERO_ROGUE_SPRITE);
		// Evil assets
		m_data->assets.LoadTexture("Tex_EvilFrostGolem", EVIL_FROST_GOLEM_SPRITE);
		m_data->assets.LoadTexture("Tex_EvilFrostMage", EVIL_FROST_MAGE_SPRITE);
		// Encounter assets
		m_data->assets.LoadTexture("Tex_EncounterUIFrame", ENCOUNTER_UI_FRAME);
		m_data->assets.LoadTexture("Tex_BasicAttackBtn", BASIC_ATTACK_BTN);
		m_data->assets.LoadTexture("Tex_DefendBtn", DEFFEND_BTN);
		m_data->assets.LoadTexture("Tex_UseHPBtn", USE_HP_BTN);
		m_data->assets.LoadTexture("Tex_UseMPBtn", USE_MP_BTN);

		// create serializable game entities
		// buildings
		m_data->gm.infirmary = std::make_shared<Infirmary>();
		m_data->gm.blacksmith = std::make_shared<Blacksmith>();
		m_data->gm.library = std::make_shared<Library>();
		m_data->gm.inn = std::make_shared<Inn>();
		m_data->gm.store = std::make_shared<GeneralStore>();
		// heroes
		m_data->gm.hKnight = std::make_shared<Knight>();
		m_data->gm.hBard = std::make_shared<Bard>();
		m_data->gm.hSorceress = std::make_shared<Sorceress>();
		m_data->gm.hRogue = std::make_shared<Rogue>();

		/* /> GLOBAL PRE-LOAD */

		// Load Splash screen assets
		m_data->assets.LoadTexture("Tex_SplashBG", SPLASH_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_LogoSheet", SPLASH_GAME_LOGO_SPRITESHEET);

		// Splash screen entities
		// Background
		auto bg = std::make_shared<Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_SplashBGSprite");
		// define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SplashBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 200));
		// set properties
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		// Logo
		m_logo = std::make_shared<AnimatedLogo>();
		// initialize data
		m_logo->SetSprite(m_data->assets.GetTexture("Tex_LogoSheet"), sf::IntRect(0, 0, 550, 250));
		// set more properties
		m_logo->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_logo->GetSpriteComponent()->GetSprite().getGlobalBounds().width) * 0.5f, 
			(SCREEN_HEIGHT - m_logo->GetSpriteComponent()->GetSprite().getGlobalBounds().height) * 0.5f));
		m_logo->GetAnimatorComponent()->AddAnimation("Anim_GameLogo", Animation(&m_data->assets.GetTexture("Tex_LogoSheet"), sf::Vector2u(6, 7), 0.04f, true, true));
		m_logo->GetAnimatorComponent()->GetAnimation("Anim_GameLogo").SetRow(0);
		m_logo->Init();

		// Text
		auto text = std::make_shared<Entity>();
		auto splashTxt = text->AddComponent<TextComponent>("C_Text");
		// define
		splashTxt->SetFont(m_data->assets.GetFont("Font_Pixel"));
		text->SetPosition(sf::Vector2f((SCREEN_WIDTH - splashTxt->GetText().getGlobalBounds().width) * 0.325f,
			(SCREEN_HEIGHT - splashTxt->GetText().getGlobalBounds().height) * 0.55f));
		splashTxt->SetFont(m_data->assets.GetFont("Font_Pixel"));
		splashTxt->GetText().setCharacterSize(24);
		splashTxt->GetText().setString("Press any key to continue ...");
		// properties
		text->showOnCreate = false;
		text->SetVisible(false);
		text->SetAlive(true);
		text->Init();

		// Add to ents (local) map
		AddEntity("E_zSplashBG", bg);
		AddEntity("E_xSplashText", text);
		AddEntity("E_GameLogo", m_logo);

		// allow proceeding to after-loading 'stop-frame' animation
		// not async, thread-safe logic this way but will fix it in the 'future' ;)
		m_canDelay = true;
	}

	void SplashScene::HandleInput()
	{
		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView(event.size.width, event.size.height);

			if (m_canInput)
			{
				// Keyboard input
				auto bgSprite = m_data->ents.Find<Entity>("E_zSplashBG")->GetComponent<SpriteComponent>("C_SplashBGSprite");
				// 'Press ANY key OR button to continue!' type of game
				if (event.type == sf::Event::EventType::KeyPressed ||
					m_data->input.isClicked(bgSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
				{
					m_shouldFade = true;
				}
			}
		}
	}

	void SplashScene::Update(float t_delatTime)
	{
		if (m_canDelay)
		{
			if (m_pressDelay.getElapsedTime().asSeconds() > 1.0f)
			{
				m_logo->GetAnimatorComponent()->GetAnimation("Anim_GameLogo").ExitLoop();
				m_canMove = true;
				m_canDelay = false;
			}
		}

		if (m_canMove && m_logo->GetAnimatorComponent()->GetAnimation("Anim_GameLogo").GetRow() >= 6)
			m_logo->Move(sf::Vector2f(0.0f, -1.0f));

		if (m_logo->GetPosition().y <= (SCREEN_HEIGHT - m_logo->GetSpriteComponent()->GetSprite().getGlobalBounds().height) * 0.3f)
		{
			m_data->ents.Find<Entity>("E_xSplashText")->SetVisible(true);
			m_canInput = true;
			m_canMove = false;
		}

		auto bgSpriteComp = m_data->ents.Find<Entity>("E_zSplashBG")->GetComponent<SpriteComponent>("C_SplashBGSprite");
		if (m_shouldFade)
		{
			m_data->ents.Find<Entity>("E_xSplashText")->SetVisible(false);
			auto fadedColorBG = sf::Color(bgSpriteComp->GetSprite().getColor().r,
				bgSpriteComp->GetSprite().getColor().g,
				bgSpriteComp->GetSprite().getColor().b,
				bgSpriteComp->GetSprite().getColor().a - t_delatTime * 100.0f);

			auto fadedColorLogo = sf::Color(bgSpriteComp->GetSprite().getColor().r,
				bgSpriteComp->GetSprite().getColor().g,
				bgSpriteComp->GetSprite().getColor().b,
				bgSpriteComp->GetSprite().getColor().a - t_delatTime * 0.01f);

			bgSpriteComp->GetSprite().setColor(fadedColorBG);
			m_logo->GetSpriteComponent()->GetSprite().setColor(fadedColorLogo);

			if (bgSpriteComp->GetSprite().getColor().a <= 0)
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