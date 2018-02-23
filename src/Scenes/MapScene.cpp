#include "MapScene.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	MapScene::MapScene(GameDataRef t_data)
		:m_data(t_data)
	{
		//not used
	}

	void MapScene::Init()
	{
		m_data->assets.LoadTexture("Tex_MapBG", MAIN_GAME_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_Castle", MAIN_GAME_CASTLE);
		m_data->assets.LoadTexture("Tex_Forest", MAIN_GAME_FOREST);
		m_data->assets.LoadTexture("Tex_Mountains", MAIN_GAME_MOUNTAINS);
		m_data->assets.LoadTexture("Tex_Sea", MAIN_GAME_SEA);
		m_data->assets.LoadTexture("Tex_EvilCastle", MAIN_GAME_EVIL_CASTLE);
		m_data->assets.LoadTexture("Tex_Frame", MAIN_GAME_UI_FRAME);

		//Entity manager to non-visible ents
		for (auto ent : m_data->ents.GetEntsDictionary()) ent.second->SetVisible(false);

		//Local entities map container
		std::map<std::string, std::shared_ptr<ECM::Entity>> ents;

		//Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_MapBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_MapBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		bgSprite->GetSprite().scale(0.9f, 0.85f);
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
		castle->SetPosition(sf::Vector2f((SCREEN_WIDTH - castleSprite->GetSprite().getGlobalBounds().width) * 0.1f, (SCREEN_HEIGHT - castleSprite->GetSprite().getGlobalBounds().height) * 0.3f));
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
		mountains->SetPosition(sf::Vector2f((SCREEN_WIDTH - mountainsSprite->GetSprite().getGlobalBounds().width) * 0.5f, (SCREEN_HEIGHT - mountainsSprite->GetSprite().getGlobalBounds().height) * 0.8f));
		mountains->SetVisible(true);
		mountains->SetAlive(true);

		//Sea
		auto sea = std::make_shared<ECM::Entity>();
		auto seaSprite = sea->AddComponent<SpriteComponent>("C_SeaSprite");
		//define castle sprite
		seaSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Sea"));
		seaSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		sea->SetPosition(sf::Vector2f((SCREEN_WIDTH - seaSprite->GetSprite().getGlobalBounds().width) * 0.95f, (SCREEN_HEIGHT - seaSprite->GetSprite().getGlobalBounds().height) * 0.9f));
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

		//UI frame
		auto frame = std::make_shared<ECM::Entity>();
		auto frameSprite = frame->AddComponent<SpriteComponent>("C_FrameSprite");
		//define castle sprite
		frameSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Frame"));
		frameSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		frameSprite->GetSprite().scale(0.9f, 0.9f);
		frame->SetPosition(sf::Vector2f((SCREEN_WIDTH - frameSprite->GetSprite().getGlobalBounds().width*2.4) , (SCREEN_HEIGHT - frameSprite->GetSprite().getGlobalBounds().height) ));
		frame->SetVisible(true);
		frame->SetAlive(true);
		

		//add to local ents map
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! "z" for background "x" for UI
		ents.insert_or_assign("E_zMapBG", bg);
		ents.insert_or_assign("E_Castle", castle);
		ents.insert_or_assign("E_Forest", forest);
		ents.insert_or_assign("E_Mountains", mountains);
		ents.insert_or_assign("E_Sea", sea);
		ents.insert_or_assign("E_EvilCastle", evilCastle);
		ents.insert_or_assign("E_xFrame", frame);
		

		//:if entity is not in the entity manager, then add
		m_data->ents.PopulateEntsDictionary(ents);
	}

	void MapScene::HandleInput()
	{
		sf::Event event;
		while (Renderer::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Renderer::GetWin().close();

			auto bgComp = m_data->ents.Find<Entity>("E_zMapBG")->GetComponent<SpriteComponent>("C_MapBGSprite");
			auto frameComp = m_data->ents.Find<Entity>("E_xFrame")->GetComponent<SpriteComponent>("C_FrameSprite");
			auto castleComp = m_data->ents.Find<Entity>("E_Castle")->GetComponent<SpriteComponent>("C_CastleSprite");
			auto forestComp = m_data->ents.Find<Entity>("E_Forest")->GetComponent<SpriteComponent>("C_ForestSprite");
			auto mountainsComp = m_data->ents.Find<Entity>("E_Mountains")->GetComponent<SpriteComponent>("C_MountainsSprite");
			auto seaComp = m_data->ents.Find<Entity>("E_Sea")->GetComponent<SpriteComponent>("C_SeaSprite");
			auto evilCastleComp = m_data->ents.Find<Entity>("E_EvilCastle")->GetComponent<SpriteComponent>("C_EvilCastleSprite");
			
			//check for castle click
			if (m_data->input.isClicked(castleComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_castleClick = true;
			}
			
			//check for forest click
			if (m_data->input.isClicked(forestComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_forestClick = true;
				// show the encounter popup
				m_encounterPopup = std::make_shared<EncounterPopup>();

				// SET CREATION BEHAVIOUR
				m_encounterPopup->OnCreate([=]()
				{
					// set components
					m_encounterPopup->SetBackgroundImage(m_data->assets.GetTexture("Tex_Sea"));
					m_encounterPopup->GetComponent<SpriteComponent>("C_PopupBGSprite")->GetSprite().scale(3.0f, 2.0f);
					// set panel position
					m_encounterPopup->SetPosition(sf::Vector2f(
						(SCREEN_WIDTH - m_encounterPopup->GetComponent<SpriteComponent>("C_PopupBGSprite")->GetSprite().getGlobalBounds().height) * 0.5f,
						(SCREEN_HEIGHT - m_encounterPopup->GetComponent<SpriteComponent>("C_PopupBGSprite")->GetSprite().getGlobalBounds().height) * 0.5f
					));
					// add to entities
					m_data->ents.Save("E_aEncounterPopup", m_encounterPopup);

					// Fade Entities
					bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 100.0f));
					frameComp->GetSprite().setColor(sf::Color(frameComp->GetSprite().getColor().r, frameComp->GetSprite().getColor().g, frameComp->GetSprite().getColor().b, 10.0f));
					castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r, castleComp->GetSprite().getColor().g, castleComp->GetSprite().getColor().b, 10.0f));
					forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r, forestComp->GetSprite().getColor().g, forestComp->GetSprite().getColor().b, 10.0f));
					mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r, mountainsComp->GetSprite().getColor().g, mountainsComp->GetSprite().getColor().b, 10.0f));
					seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 10.0f));
					evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					
					// Make Entities Unclickable
					// TODO...
				});

				// SET CLOSING BEHAVIOUR
				m_encounterPopup->OnClose = [=]()
				{
					// Unfade Entities
					bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 255.0f));
					frameComp->GetSprite().setColor(sf::Color(frameComp->GetSprite().getColor().r, frameComp->GetSprite().getColor().g, frameComp->GetSprite().getColor().b, 255.0f));
					castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r, castleComp->GetSprite().getColor().g, castleComp->GetSprite().getColor().b, 255.0f));
					forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r, forestComp->GetSprite().getColor().g, forestComp->GetSprite().getColor().b, 255.0f));
					mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r, mountainsComp->GetSprite().getColor().g, mountainsComp->GetSprite().getColor().b, 255.0f));
					seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 255.0f));

					// Make Entities Clickable
					// TODO...
				};
			}

			//check for mountains click
			if (m_data->input.isClicked(mountainsComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_mountainsClick = true;
			}

			//check for sea click
			if (m_data->input.isClicked(seaComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_seaClick = true;
			}

			//check for evil castle click
			if (m_data->input.isClicked(evilCastleComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_evilCastleClick = true;
			}
		}
	}

	void MapScene::Update(float t_delatTime)
	{
		m_data->ents.Update(t_delatTime);

		auto castleComp = m_data->ents.Find<Entity>("E_Castle")->GetComponent<SpriteComponent>("C_CastleSprite");
		auto forestComp = m_data->ents.Find<Entity>("E_Forest")->GetComponent<SpriteComponent>("C_ForestSprite");
		auto mountainsComp = m_data->ents.Find<Entity>("E_Mountains")->GetComponent<SpriteComponent>("C_MountainsSprite");
		auto seaComp = m_data->ents.Find<Entity>("E_Sea")->GetComponent<SpriteComponent>("C_SeaSprite");
		auto evilCastleComp = m_data->ents.Find<Entity>("E_EvilCastle")->GetComponent<SpriteComponent>("C_EvilCastleSprite");

		//show if castle is clicked
		if (m_castleClick)
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
		
		if (m_time < 0.0f && m_castleUnClick)
		{
			castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r + 100,
				castleComp->GetSprite().getColor().g + 100,
				castleComp->GetSprite().getColor().b + 100,
				castleComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_castleUnClick = false;

			auto castleState = std::make_unique<CastleScene>(CastleScene(m_data));
			m_data->machine.AddState(std::move(castleState));

		}

		if (m_time < 0.0f && m_forestUnClick)
		{
			forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r + 100,
				forestComp->GetSprite().getColor().g + 100,
				forestComp->GetSprite().getColor().b + 100,
				forestComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_forestUnClick = false;
		}

		if (m_time < 0.0f && m_mountainsUnClick)
		{
			mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r + 100,
				mountainsComp->GetSprite().getColor().g + 100,
				mountainsComp->GetSprite().getColor().b + 100,
				mountainsComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_mountainsUnClick = false;
		}
		
		if (m_time < 0.0f && m_seaUnClick)
		{
			seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r + 100,
				seaComp->GetSprite().getColor().g + 100,
				seaComp->GetSprite().getColor().b + 100,
				seaComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_seaUnClick = false;
		}
		
		if (m_time < 0.0f && m_evilCastleUnClick)
		{
			evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r + 100,
				evilCastleComp->GetSprite().getColor().g + 100,
				evilCastleComp->GetSprite().getColor().b + 100,
				evilCastleComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_evilCastleUnClick = false;
		}
	}

	void MapScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render();
	}
}