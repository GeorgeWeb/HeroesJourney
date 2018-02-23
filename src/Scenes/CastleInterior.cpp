#include "CastleInterior.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	CastleScene::CastleScene(GameDataRef t_data)
		:m_data(t_data)
	{
		//not used
	}

	void CastleScene::Init()
	{
		m_data->assets.LoadTexture("Tex_CastleBG", MAP_SCENE_BACKGROUD);
		m_data->assets.LoadTexture("Tex_Infirmary", MAP_SCENE_INFIRMARY);
		m_data->assets.LoadTexture("Tex_Blacksmith", MAP_SCENE_BLACKSMITH);
		m_data->assets.LoadTexture("Tex_Library", MAP_SCENE_LIBRARY);
		m_data->assets.LoadTexture("Tex_Inn", MAP_SCENE_INN);
		m_data->assets.LoadTexture("Tex_GeneralStore", MAP_SCENE_GENERAL_STORE);
		m_data->assets.LoadTexture("Tex_BackArrow", MAP_SCENE_BACK_ARROW);

		// Entity manager to non-visible ents
		for (auto ent : m_data->ents.GetEntsDictionary()) ent.second->SetVisible(false);

		// background
		auto bg = std::make_shared < ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_CastleBGSprite");
		
		// define
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_CastleBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		
		// properties
		bgSprite->GetSprite().scale(1, 0.96f);
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		//infirmary
		m_infirmary = std::make_shared<Infirmary>("C_InfirmarySprite");
		//initialize data
		m_infirmary->Init(m_data->assets.GetTexture("Tex_Infirmary"));
		//more properties
		m_infirmary->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_infirmary->GetComponent<SpriteComponent>("C_InfirmarySprite")->GetSprite().getGlobalBounds().width) * 0.1f,
			(SCREEN_HEIGHT - m_infirmary->GetComponent<SpriteComponent>("C_InfirmarySprite")->GetSprite().getGlobalBounds().height) * 0.7));

		//Text
		auto text = std::make_shared <Entity> ();
		auto infTextFont = text->AddComponent<TextComponent>("C_Text");
		//define
		infTextFont->SetFont(m_data->assets.GetFont("Font_Pixel"));
		text->SetPosition(sf::Vector2f(m_infirmary->GetPosition().x, m_infirmary->GetPosition().y + m_infirmary->GetComponent<SpriteComponent>("C_InfirmarySprite")->GetSprite().getGlobalBounds().height + 20.0f));
		//Properties
		text->SetVisible(false);
		text->SetAlive(true);
		text->GetComponent<TextComponent>("C_Text")->GetText().setString("CHOOSE A BUILDING!!!");
		//blacksmith
		m_blacksmith = std::make_shared<Blacksmith>("C_BlacksmithSprite");
		//initialize data
		m_blacksmith->Init(m_data->assets.GetTexture("Tex_Blacksmith"));
		//more properties
		m_blacksmith->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_blacksmith->GetComponent<SpriteComponent>("C_BlacksmithSprite")->GetSprite().getGlobalBounds().width) * 0.15f,
			(SCREEN_HEIGHT - m_blacksmith->GetComponent<SpriteComponent>("C_BlacksmithSprite")->GetSprite().getGlobalBounds().height) * 0.35));

		//Library
		m_library = std::make_shared<Library>("C_LibrarySprite");
		//initialize data
		m_library->Init(m_data->assets.GetTexture("Tex_Library"));
		//more properties
		m_library->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_library->GetComponent<SpriteComponent>("C_LibrarySprite")->GetSprite().getGlobalBounds().width) * 0.5f,
			(SCREEN_HEIGHT - m_library->GetComponent<SpriteComponent>("C_LibrarySprite")->GetSprite().getGlobalBounds().height) * 0.2));

		//Inn
		m_inn = std::make_shared<Inn>("C_InnSprite");
		//initialize data
		m_inn->Init(m_data->assets.GetTexture("Tex_Inn"));
		//more properties
		m_inn->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_inn->GetComponent<SpriteComponent>("C_InnSprite")->GetSprite().getGlobalBounds().width) * 0.8f,
			(SCREEN_HEIGHT - m_inn->GetComponent<SpriteComponent>("C_InnSprite")->GetSprite().getGlobalBounds().height) * 0.3));

		//General STore
		m_generalStore = std::make_shared<GeneralStore>("C_GeneralStore");
		//initialize data
		m_generalStore->Init(m_data->assets.GetTexture("Tex_GeneralStore"));
		//more properties
		m_generalStore->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_generalStore->GetComponent<SpriteComponent>("C_GeneralStore")->GetSprite().getGlobalBounds().width) * 0.85f,
			(SCREEN_HEIGHT - m_generalStore->GetComponent<SpriteComponent>("C_GeneralStore")->GetSprite().getGlobalBounds().height) * 0.6));



		// backArrow
		auto backArrow = std::make_shared<ECM::Entity>();
		auto backArrowSprite = backArrow->AddComponent<SpriteComponent>("C_BackArrow");
		
		// define backArrow sprite
		backArrowSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_BackArrow"));
		backArrowSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		
		// backArrow properties
		backArrow->SetPosition(sf::Vector2f((SCREEN_WIDTH - backArrowSprite->GetSprite().getGlobalBounds().width) * 0.05, (SCREEN_HEIGHT - backArrowSprite->GetSprite().getGlobalBounds().height) * 0.01));
		backArrow->SetVisible(true);
		backArrow->SetAlive(true);

		

		// Local entities map container
		std::map<std::string, std::shared_ptr<ECM::Entity>> ents;

		ents.insert_or_assign("E_zCastleBG", bg);
		ents.insert_or_assign("E_BackArrow", backArrow);
		ents.insert_or_assign("E_Blacksmith", m_blacksmith);
		ents.insert_or_assign("E_Infirmary", m_infirmary);
		ents.insert_or_assign("E_Text", text);
		ents.insert_or_assign("E_Library", m_library);
		ents.insert_or_assign("E_Inn", m_inn);
		ents.insert_or_assign("E_GeneralStore", m_generalStore);

		//:if entity is not in the entity manager, then add
		m_data->ents.PopulateEntsDictionary(ents);

	}

	void CastleScene::HandleInput()
	{
		sf::Event event;
		while (Renderer::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Renderer::GetWin().close();

			//Check if infirmary is clicked
			auto infComp = m_data->ents.Find<Infirmary>("E_Infirmary")->GetComponent<SpriteComponent>("C_InfirmarySprite");
			if (m_data->input.isClicked(infComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_infirmary->isClicked = true;
				m_data->ents.Find<Entity>("E_Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("INFIRMARY HAS BEEN CLICKED!!!");
				m_data->ents.Find<Entity>("E_Text")->SetVisible(true);
			}
			//Check if Blacksmith is clicked
			auto blacksmithComp = m_data->ents.Find<Blacksmith>("E_Blacksmith")->GetComponent<SpriteComponent>("C_BlacksmithSprite");
			if (m_data->input.isClicked(blacksmithComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_blacksmith->isClicked = true;
				m_data->ents.Find<Entity>("E_Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("BLACKSMITH HAS BEEN CLICKED!!!");
				m_data->ents.Find<Entity>("E_Text")->SetVisible(true);

			}			//Check if Library is clicked
			auto libraryComp = m_data->ents.Find<Library>("E_Library")->GetComponent<SpriteComponent>("C_LibrarySprite");
			if (m_data->input.isClicked(libraryComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_library->isClicked = true;
				m_data->ents.Find<Entity>("E_Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("LIBRARY HAS BEEN CLICKED!!!");
				m_data->ents.Find<Entity>("E_Text")->SetVisible(true);

			}			//Check if Inn is clicked
			auto innComp = m_data->ents.Find<Inn>("E_Inn")->GetComponent<SpriteComponent>("C_InnSprite");
			if (m_data->input.isClicked(innComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_inn->isClicked = true;
				m_data->ents.Find<Entity>("E_Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("INN HAS BEEN CLICKED!!!");
				m_data->ents.Find<Entity>("E_Text")->SetVisible(true);

			}			//Check if Library is clicked
			auto genStoreComp = m_data->ents.Find<GeneralStore>("E_GeneralStore")->GetComponent<SpriteComponent>("C_GeneralStore");
			if (m_data->input.isClicked(genStoreComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_generalStore->isClicked = true;
				m_data->ents.Find<Entity>("E_Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("GENERAL STORE HAS BEEN CLICKED!!!");
				m_data->ents.Find<Entity>("E_Text")->SetVisible(true);

			}			//check if back arrow is clicked			auto arrowComp = m_data->ents.Find<Entity>("E_BackArrow")->GetComponent<SpriteComponent>("C_BackArrow");			if (m_data->input.isClicked(arrowComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_click = true;
			}			
		}
	}

	void CastleScene::Update(float t_delatTime)
	{
		m_data->ents.Update(t_delatTime);

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
		if (m_time <0.0f && m_unClick)
		{

			arrowComp->GetSprite().setColor(sf::Color(arrowComp->GetSprite().getColor().r + 100,
				arrowComp->GetSprite().getColor().g + 100,
				arrowComp->GetSprite().getColor().b + 100,
				arrowComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_unClick = false;
			m_click = false;
			std::cout << "Works" << std::endl;
			
		}


	}

	void CastleScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render();

	}
}