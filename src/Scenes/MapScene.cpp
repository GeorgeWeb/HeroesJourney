#include "MapScene.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	using namespace Engine::Components;

	
	sf::Clock Clock;
	float Time = 0.1f;
	bool unClick = false;

	HJ::MapScene::MapScene(GameDataRef t_data)
		:m_data(t_data)
	{
		//not used
	}

	void HJ::MapScene::Init()
	{
		m_data->assets.LoadTexture("Tex_MapBG", MAIN_GAME_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_Castle", MAIN_GAME_CASTLE);
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
		castle->SetPosition(sf::Vector2f((SCREEN_WIDTH - castleSprite->GetSprite().getGlobalBounds().width) * 0.3f, (SCREEN_HEIGHT - castleSprite->GetSprite().getGlobalBounds().height) * 0.3f));
		castle->SetVisible(true);
		castle->SetAlive(true);

		//add to local ents map
		ents.insert_or_assign("E_MapBG", bg);
		ents.insert_or_assign("E_Castle", castle);
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

			auto castleComp = m_data->ents.Find("E_Castle")->GetComponent("C_CastleSprite");

			if (m_data->input.isClicked(castleComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_castleClick = true;
			}
		}
	}

	void HJ::MapScene::Update(float t_delatTime)
	{
		
		m_data->ents.Update(t_delatTime);
		auto castleComp = m_data->ents.Find("E_Castle")->GetComponent("C_CastleSprite");
		
	
		if (m_castleClick )
		{
			castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r - 100,
				castleComp->GetSprite().getColor().g - 100,
				castleComp->GetSprite().getColor().b - 100,
				castleComp->GetSprite().getColor().a));
			
			m_castleClick = false;
			unClick = true;

		}
		
		if (unClick)
		{
			Time -= t_delatTime;
		}
		
		if (unClick && Time <0.0f)
		{
			castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r + 100,
				castleComp->GetSprite().getColor().g + 100,
				castleComp->GetSprite().getColor().b + 100,
				castleComp->GetSprite().getColor().a));

			Time = 0.1f;
			unClick = false;
		}
		

	}

	void HJ::MapScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render();
	}
}