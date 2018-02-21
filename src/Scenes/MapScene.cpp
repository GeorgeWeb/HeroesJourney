#include "MapScene.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	using namespace Engine::Components;

	
	

	HJ::MapScene::MapScene(GameDataRef t_data)
		:m_data(t_data)
	{
		//not used
	}

	void HJ::MapScene::Init()
	{
		m_data->assets.LoadTexture("Tex_MapBG", MAIN_GAME_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_Castle", MAIN_GAME_CASTLE);
		m_data->assets.LoadTexture("Tex_Forest", MAIN_GAME_FOREST);
		m_data->assets.LoadTexture("Tex_Mountains", MAIN_GAME_MOUNTAINS);
		m_data->assets.LoadTexture("Tex_Sea", MAIN_GAME_SEA);
		m_data->assets.LoadTexture("Tex_EvilCastle", MAIN_GAME_EVIL_CASTLE);

		//Entity manager to non-visible ents
		for (auto ent : m_data->ents.GetEntsDictionary()) ent.second->SetVisible(false);

		//Local entities map container
		std::map<std::string, std::shared_ptr<ECM::Entity>> ents;

		//Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_MapBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SplashBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 100));
		//properties
		bgSprite->GetSprite().scale(0.9f, 0.9f);
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		//Castle
		auto castle = std::make_shared<ECM::Entity>();
		auto castleSprite = castle->AddComponent<SpriteComponent>("C_CastleSprite");
		//define castle sprite
		castleSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Castle"));
		castleSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		castle->SetPosition(sf::Vector2f((SCREEN_WIDTH - castleSprite->GetSprite().getGlobalBounds().width) * 0.1f, (SCREEN_HEIGHT - castleSprite->GetSprite().getGlobalBounds().height) * 0.2f));
		castle->SetVisible(true);
		castle->SetAlive(true);

		//Forest
		auto forest = std::make_shared<ECM::Entity>();
		auto forestSprite = forest->AddComponent<SpriteComponent>("C_ForestSprite");
		//define castle sprite
		forestSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Forest"));
		forestSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		forest->SetPosition(sf::Vector2f((SCREEN_WIDTH - forestSprite->GetSprite().getGlobalBounds().width) * 0.35f, (SCREEN_HEIGHT - forestSprite->GetSprite().getGlobalBounds().height) * 0.5f));
		forest->SetVisible(true);
		forest->SetAlive(true);

		//Mountains
		auto mountains = std::make_shared<ECM::Entity>();
		auto mountainsSprite = mountains->AddComponent<SpriteComponent>("C_MountainsSprite");
		//define castle sprite
		mountainsSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Mountains"));
		mountainsSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		mountains->SetPosition(sf::Vector2f((SCREEN_WIDTH - mountainsSprite->GetSprite().getGlobalBounds().width) * 0.6f, (SCREEN_HEIGHT - mountainsSprite->GetSprite().getGlobalBounds().height) * 0.68f));
		mountains->SetVisible(true);
		mountains->SetAlive(true);

		//Sea
		auto sea = std::make_shared<ECM::Entity>();
		auto seaSprite = sea->AddComponent<SpriteComponent>("C_SeaSprite");
		//define castle sprite
		seaSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Sea"));
		seaSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		sea->SetPosition(sf::Vector2f((SCREEN_WIDTH - seaSprite->GetSprite().getGlobalBounds().width) * 0.9f, (SCREEN_HEIGHT - seaSprite->GetSprite().getGlobalBounds().height) * 0.6f));
		sea->SetVisible(true);
		sea->SetAlive(true);

		//Evil Castle
		auto evilCastle = std::make_shared<ECM::Entity>();
		auto evilCastleSprite = evilCastle->AddComponent<SpriteComponent>("C_EvilCastleSprite");
		//define castle sprite
		evilCastleSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_EvilCastle"));
		evilCastleSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		evilCastle->SetPosition(sf::Vector2f((SCREEN_WIDTH - evilCastleSprite->GetSprite().getGlobalBounds().width) * 0.7f, (SCREEN_HEIGHT - evilCastleSprite->GetSprite().getGlobalBounds().height) * 0.2f));
		evilCastle->SetVisible(true);
		evilCastle->SetAlive(true);

		//add to local ents map
		ents.insert_or_assign("E_MapBG", bg);
		ents.insert_or_assign("E_Castle", castle);
		ents.insert_or_assign("E_Forest", forest);
		ents.insert_or_assign("E_Mountains", mountains);
		ents.insert_or_assign("E_Sea", sea);
		ents.insert_or_assign("E_EvilCastle", evilCastle);
		

		//:if entity is not in the entity manager, then add
		m_data->ents.PopulateEntsDictionary(ents);

	}

	void HJ::MapScene::HandleInput()
	{
		sf::Event event;
		while (Renderer::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Renderer::GetWin().close();

			//check for castle click
			auto castleComp = m_data->ents.Find("E_Castle")->GetComponent("C_CastleSprite");

			if (m_data->input.isClicked(castleComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_castleClick = true;
			}
			
			//check for forest click
			auto forestComp = m_data->ents.Find("E_Forest")->GetComponent("C_ForestSprite");

			if (m_data->input.isClicked(forestComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_forestClick = true;
			}

			//check for mountains click
			auto mountainsComp = m_data->ents.Find("E_Mountains")->GetComponent("C_MountainsSprite");

			if (m_data->input.isClicked(mountainsComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_mountainsClick = true;
			}

			//check for sea click
			auto seaComp = m_data->ents.Find("E_Sea")->GetComponent("C_SeaSprite");

			if (m_data->input.isClicked(seaComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_seaClick = true;
			}

			//check for evil castle click
			auto evilCastleComp = m_data->ents.Find("E_EvilCastle")->GetComponent("C_EvilCastleSprite");

			if (m_data->input.isClicked(evilCastleComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_evilCastleClick = true;
			}

		}
	}

	void HJ::MapScene::Update(float t_delatTime)
	{
		
		m_data->ents.Update(t_delatTime);

		auto castleComp = m_data->ents.Find("E_Castle")->GetComponent("C_CastleSprite");
		auto forestComp = m_data->ents.Find("E_Forest")->GetComponent("C_ForestSprite");
		auto mountainsComp = m_data->ents.Find("E_Mountains")->GetComponent("C_MountainsSprite");
		auto seaComp = m_data->ents.Find("E_Sea")->GetComponent("C_SeaSprite");
		auto evilCastleComp = m_data->ents.Find("E_EvilCastle")->GetComponent("C_EvilCastleSprite");

		//show if castle is clicked
		if (m_castleClick )
		{
			castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r - 100,
				castleComp->GetSprite().getColor().g - 100,
				castleComp->GetSprite().getColor().b - 100,
				castleComp->GetSprite().getColor().a));
			
			m_castleClick = false;
			m_castleUnClick = true;

		}
		//show if forest is clicked
		if (m_forestClick)
		{
			forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r - 100,
				forestComp->GetSprite().getColor().g - 100,
				forestComp->GetSprite().getColor().b - 100,
				forestComp->GetSprite().getColor().a));

			m_forestClick = false;
			m_forestUnClick = true;
		}
		//show if mountains are clicked
		if (m_mountainsClick)
		{
			mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r - 100,
				mountainsComp->GetSprite().getColor().g - 100,
				mountainsComp->GetSprite().getColor().b - 100,
				mountainsComp->GetSprite().getColor().a));

			m_mountainsClick = false;
			m_mountainsUnClick = true;
		}
		//show if sea are clicked
		if (m_seaClick)
		{
			seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r - 100,
				seaComp->GetSprite().getColor().g - 100,
				seaComp->GetSprite().getColor().b - 100,
				seaComp->GetSprite().getColor().a));

			m_seaClick = false;
			m_seaUnClick = true;
		}
		//show if sea are clicked
		if (m_evilCastleClick)
		{
			evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r - 100,
				evilCastleComp->GetSprite().getColor().g - 100,
				evilCastleComp->GetSprite().getColor().b - 100,
				evilCastleComp->GetSprite().getColor().a));

			m_evilCastleClick = false;
			m_evilCastleUnClick = true;
		}





		if (m_castleUnClick || m_forestUnClick || m_mountainsUnClick || m_seaUnClick || m_evilCastleUnClick)
		{
			m_time -= t_delatTime;
		}
		
		if ( m_time <0.0f && m_castleUnClick)
		{
			castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r + 100,
				castleComp->GetSprite().getColor().g + 100,
				castleComp->GetSprite().getColor().b + 100,
				castleComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_castleUnClick = false;
		}

		if (m_time <0.0f && m_forestUnClick)
		{
			forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r + 100,
				forestComp->GetSprite().getColor().g + 100,
				forestComp->GetSprite().getColor().b + 100,
				forestComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_forestUnClick = false;
		}

		if (m_time <0.0f && m_mountainsUnClick)
		{
			mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r + 100,
				mountainsComp->GetSprite().getColor().g + 100,
				mountainsComp->GetSprite().getColor().b + 100,
				mountainsComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_mountainsUnClick = false;
		}
		if (m_time <0.0f && m_seaUnClick)
		{
			seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r + 100,
				seaComp->GetSprite().getColor().g + 100,
				seaComp->GetSprite().getColor().b + 100,
				seaComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_seaUnClick = false;
		}
		if (m_time <0.0f && m_evilCastleUnClick)
		{
			evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r + 100,
				evilCastleComp->GetSprite().getColor().g + 100,
				evilCastleComp->GetSprite().getColor().b + 100,
				evilCastleComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_evilCastleUnClick = false;
		}

		

	}

	void HJ::MapScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render();

	}
}