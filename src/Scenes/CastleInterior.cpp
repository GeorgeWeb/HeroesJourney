#include "CastleInterior.hpp"
#include "PauseMenu.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	CastleScene::CastleScene(GameDataRef t_data) : 
		m_data(t_data)
	{ }

	void CastleScene::Init()
	{
		m_data->assets.LoadTexture("Tex_CastleBG", MAP_SCENE_BACKGROUD);
		m_data->assets.LoadTexture("Tex_Infirmary", MAP_SCENE_INFIRMARY);
		m_data->assets.LoadTexture("Tex_Blacksmith", MAP_SCENE_BLACKSMITH);
		m_data->assets.LoadTexture("Tex_Library", MAP_SCENE_LIBRARY);
		m_data->assets.LoadTexture("Tex_Inn", MAP_SCENE_INN);
		m_data->assets.LoadTexture("Tex_GeneralStore", MAP_SCENE_GENERAL_STORE);
		m_data->assets.LoadTexture("Tex_BackArrow", MAP_SCENE_BACK_ARROW);

		// background
		auto bg = std::make_shared<Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_CastleBGSprite");
		// define
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_CastleBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		// properties
		bgSprite->GetSprite().scale(1, 0.96f);
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		// infirmary
		m_infirmary = std::make_shared<Infirmary>("C_InfirmarySprite");
		// initialize data
		m_infirmary->SetSprite(m_data->assets.GetTexture("Tex_Infirmary"));
		// more properties
		m_infirmary->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_infirmary->GetComponent<SpriteComponent>("C_InfirmarySprite")->GetSprite().getGlobalBounds().width) * 0.1f,
			(SCREEN_HEIGHT - m_infirmary->GetComponent<SpriteComponent>("C_InfirmarySprite")->GetSprite().getGlobalBounds().height) * 0.7));
		m_infirmary->Init();

		// blacksmith
		m_blacksmith = std::make_shared<Blacksmith>("C_BlacksmithSprite");
		// initialize data
		m_blacksmith->SetSprite(m_data->assets.GetTexture("Tex_Blacksmith"));
		// more properties
		m_blacksmith->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_blacksmith->GetComponent<SpriteComponent>("C_BlacksmithSprite")->GetSprite().getGlobalBounds().width) * 0.15f,
			(SCREEN_HEIGHT - m_blacksmith->GetComponent<SpriteComponent>("C_BlacksmithSprite")->GetSprite().getGlobalBounds().height) * 0.35));
		m_blacksmith->Init();

		// Library
		m_library = std::make_shared<Library>("C_LibrarySprite");
		// initialize data
		m_library->SetSprite(m_data->assets.GetTexture("Tex_Library"));
		// more properties
		m_library->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_library->GetComponent<SpriteComponent>("C_LibrarySprite")->GetSprite().getGlobalBounds().width) * 0.5f,
			(SCREEN_HEIGHT - m_library->GetComponent<SpriteComponent>("C_LibrarySprite")->GetSprite().getGlobalBounds().height) * 0.2));
		m_library->Init();

		// Inn
		m_inn = std::make_shared<Inn>("C_InnSprite");
		// initialize data
		m_inn->SetSprite(m_data->assets.GetTexture("Tex_Inn"));
		// more properties
		m_inn->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_inn->GetComponent<SpriteComponent>("C_InnSprite")->GetSprite().getGlobalBounds().width) * 0.8f,
			(SCREEN_HEIGHT - m_inn->GetComponent<SpriteComponent>("C_InnSprite")->GetSprite().getGlobalBounds().height) * 0.3));
		m_inn->Init();

		// General Store
		m_generalStore = std::make_shared<GeneralStore>("C_GeneralStore");
		// initialize data
		m_generalStore->SetSprite(m_data->assets.GetTexture("Tex_GeneralStore"));
		// more properties
		m_generalStore->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_generalStore->GetComponent<SpriteComponent>("C_GeneralStore")->GetSprite().getGlobalBounds().width) * 0.85f,
			(SCREEN_HEIGHT - m_generalStore->GetComponent<SpriteComponent>("C_GeneralStore")->GetSprite().getGlobalBounds().height) * 0.6));
		m_generalStore->Init();

		// backArrow
		auto backArrow = std::make_shared<Entity>();
		auto backArrowSprite = backArrow->AddComponent<SpriteComponent>("C_BackArrow");		
		// define backArrow sprite
		backArrowSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_BackArrow"));
		backArrowSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		// backArrow properties
		backArrow->SetPosition(sf::Vector2f((SCREEN_WIDTH - backArrowSprite->GetSprite().getGlobalBounds().width) * 0.05, 
			(SCREEN_HEIGHT - backArrowSprite->GetSprite().getGlobalBounds().height) * 0.01));
		backArrow->SetVisible(true);
		backArrow->SetAlive(true);

		// Text
		auto text = std::make_shared<Entity>();
		auto infTextFont = text->AddComponent<TextComponent>("C_Text");
		// define
		infTextFont->SetFont(m_data->assets.GetFont("Font_Pixel"));
		text->SetPosition(sf::Vector2f(m_infirmary->GetPosition().x, m_infirmary->GetPosition().y + m_infirmary->GetComponent<SpriteComponent>("C_InfirmarySprite")->GetSprite().getGlobalBounds().height + 20.0f));
		// properties
		text->showOnCreate = false;
		text->SetVisible(false);
		text->SetAlive(true);

		AddEntity("E_zCastleBG", bg);
		AddEntity("E_Blacksmith", m_blacksmith);
		AddEntity("E_Infirmary", m_infirmary);
		AddEntity("E_Library", m_library);
		AddEntity("E_Inn", m_inn);
		AddEntity("E_GeneralStore", m_generalStore);
		AddEntity("E_BackArrow", backArrow);
		AddEntity("E_Text", text);
	}

	void CastleScene::HandleInput()
	{
		sf::Event event;

		while (Renderer::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Renderer::GetWin().close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				// Switch scenes (to Pause Menu)
				auto pauseMenuState = std::make_unique<PauseMenuScene>(PauseMenuScene(m_data));
				m_data->machine.AddState(std::move(pauseMenuState), false);
			}

			//Check if infirmary is clicked
			auto infComp = m_infirmary->GetComponent<SpriteComponent>("C_InfirmarySprite");
			if (m_data->input.isClicked(infComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_infirmary->isClicked = true;
				m_data->ents.Find<Entity>("E_Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("INFIRMARY HAS BEEN CLICKED!!!");
				m_data->ents.Find<Entity>("E_Text")->SetVisible(true);
			}

			//Check if Blacksmith is clicked
			auto blacksmithComp = m_blacksmith->GetComponent<SpriteComponent>("C_BlacksmithSprite");
			if (m_data->input.isClicked(blacksmithComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_blacksmith->isClicked = true;
				m_data->ents.Find<Entity>("E_Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("BLACKSMITH HAS BEEN CLICKED!!!");
				m_data->ents.Find<Entity>("E_Text")->SetVisible(true);
			}

			//Check if Library is clicked
			auto libraryComp = m_library->GetComponent<SpriteComponent>("C_LibrarySprite");
			if (m_data->input.isClicked(libraryComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_library->isClicked = true;
				m_data->ents.Find<Entity>("E_Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("LIBRARY HAS BEEN CLICKED!!!");
				m_data->ents.Find<Entity>("E_Text")->SetVisible(true);
			}

			//Check if Inn is clicked
			auto innComp = m_inn->GetComponent<SpriteComponent>("C_InnSprite");
			if (m_data->input.isClicked(innComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_inn->isClicked = true;
				m_data->ents.Find<Entity>("E_Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("INN HAS BEEN CLICKED!!!");
				m_data->ents.Find<Entity>("E_Text")->SetVisible(true);
			}

			//Check if Library is clicked
			auto genStoreComp = m_generalStore->GetComponent<SpriteComponent>("C_GeneralStore");
			if (m_data->input.isClicked(genStoreComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_generalStore->isClicked = true;
				m_data->ents.Find<Entity>("E_Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("GENERAL STORE HAS BEEN CLICKED!!!");
				m_data->ents.Find<Entity>("E_Text")->SetVisible(true);
			}

			//check if back arrow is clicked
			auto arrowComp = m_data->ents.Find<Entity>("E_BackArrow")->GetComponent<SpriteComponent>("C_BackArrow");
			if (m_data->input.isClicked(arrowComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_click = true;
			}
		}
	}

	void CastleScene::Update(float t_delatTime)
	{
		auto arrowComp = m_data->ents.Find<Entity>("E_BackArrow")->GetComponent<SpriteComponent>("C_BackArrow");

		if (m_click && !m_unClick)
		{
			arrowComp->GetSprite().setColor(sf::Color(arrowComp->GetSprite().getColor().r - 100,
				arrowComp->GetSprite().getColor().g - 100,
				arrowComp->GetSprite().getColor().b - 100,
				arrowComp->GetSprite().getColor().a));
			m_unClick = true;
		}

		if (m_unClick)
		{
			m_time -= t_delatTime;
		}
		
		if (m_time < 0.0f && m_unClick)
		{
			arrowComp->GetSprite().setColor(sf::Color(arrowComp->GetSprite().getColor().r + 100,
				arrowComp->GetSprite().getColor().g + 100,
				arrowComp->GetSprite().getColor().b + 100,
				arrowComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_unClick = false;
			m_click = false;

			// go back to map scene
			m_data->machine.RemoveState();
		}

		m_data->ents.Update(m_entities, t_delatTime);
	}

	void CastleScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void CastleScene::AddEntity(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}
}