#include "CastleInterior.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	using namespace Engine::Components;

	HJ::CastleScene::CastleScene(GameDataRef t_data)
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
		
		// def
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_CastleBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		
		// properties
		bgSprite->GetSprite().scale(1, 0.96f);
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		// infirmary
		auto infirmary = std::make_shared<ECM::Entity>();
		auto infirmarySprite = infirmary->AddComponent<SpriteComponent>("C_InfirmarySprite");
		//define infirmary sprite
		infirmarySprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Infirmary"));
		infirmarySprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		
		// infirmary properties
		infirmary->SetPosition(sf::Vector2f((SCREEN_WIDTH - infirmarySprite->GetSprite().getGlobalBounds().width) * 0.15, (SCREEN_HEIGHT - infirmarySprite->GetSprite().getGlobalBounds().height) * 0.7));
		infirmary->SetVisible(true);
		infirmary->SetAlive(true);

		// blacksmith
		auto blacksmith = std::make_shared<ECM::Entity>();
		auto blacksmithSprite = blacksmith->AddComponent<SpriteComponent>("C_BlacksmithSprite");
		
		// define blacksmith sprite
		blacksmithSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Blacksmith"));
		blacksmithSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		
		// blacksmith properties
		blacksmith->SetPosition(sf::Vector2f((SCREEN_WIDTH - blacksmithSprite->GetSprite().getGlobalBounds().width) * 0.1, (SCREEN_HEIGHT - blacksmithSprite->GetSprite().getGlobalBounds().height) * 0.35));
		blacksmith->SetVisible(true);
		blacksmith->SetAlive(true);

		// library
		auto library = std::make_shared<ECM::Entity>();
		auto librarySprite = library->AddComponent<SpriteComponent>("C_Library");
		
		// define library sprite
		librarySprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Library"));
		librarySprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		
		// library properties
		library->SetPosition(sf::Vector2f((SCREEN_WIDTH - librarySprite->GetSprite().getGlobalBounds().width) * 0.5, (SCREEN_HEIGHT - librarySprite->GetSprite().getGlobalBounds().height) * 0.2));
		library->SetVisible(true);
		library->SetAlive(true);

		// inn
		auto inn = std::make_shared<ECM::Entity>();
		auto innSprite = inn->AddComponent<SpriteComponent>("C_Inn");
		
		// define inn sprite
		innSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Inn"));
		innSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		
		// inn properties
		inn->SetPosition(sf::Vector2f((SCREEN_WIDTH - innSprite->GetSprite().getGlobalBounds().width) * 0.85, (SCREEN_HEIGHT - innSprite->GetSprite().getGlobalBounds().height) * 0.35));
		inn->SetVisible(true);
		inn->SetAlive(true);

		//generalStore
		auto generalStore = std::make_shared<ECM::Entity>();
		auto generalStoreSprite = generalStore->AddComponent<SpriteComponent>("C_GeneralStore");
		
		// define generalStore sprite
		generalStoreSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_GeneralStore"));
		generalStoreSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		
		// generalStore properties
		generalStore->SetPosition(sf::Vector2f((SCREEN_WIDTH - generalStoreSprite->GetSprite().getGlobalBounds().width) * 0.95, (SCREEN_HEIGHT - generalStoreSprite->GetSprite().getGlobalBounds().height) * 0.7)); 
		generalStore->SetVisible(true);
		generalStore->SetAlive(true);

		// backArrow
		auto backArrow = std::make_shared<ECM::Entity>();
		auto backArrowSprite = backArrow->AddComponent<SpriteComponent>("C_BackArrow");
		
		// define generalStore sprite
		backArrowSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_BackArrow"));
		backArrowSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		
		// generalStore properties
		backArrow->SetPosition(sf::Vector2f((SCREEN_WIDTH - backArrowSprite->GetSprite().getGlobalBounds().width) * 0.05, (SCREEN_HEIGHT - backArrowSprite->GetSprite().getGlobalBounds().height) * 0.01));
		backArrow->SetVisible(true);
		backArrow->SetAlive(true);

		// infirmary text
		auto infText = std::make_shared<ECM::Entity>();
		auto infTextFont = infText->AddComponent<TextComponent>("C_InfText");
		
		// define text font
		infTextFont->SetFont(m_data->assets.GetFont("Font_Pixel"));
		
		// text properties
		infText->SetPosition(sf::Vector2f(infirmary->GetPosition().x, infirmary->GetPosition().y + infirmarySprite->GetSprite().getGlobalBounds().height + 20.0f));
		infText->GetComponent("C_InfText")->GetText().setString("INFIRMARY HAS BEEN CLICKED!!!");
		infText->SetVisible(false);
		infText->SetAlive(true);

		// Local entities map container
		std::map<std::string, std::shared_ptr<ECM::Entity>> ents;

		ents.insert_or_assign("E_zCastleBG", bg);
		ents.insert_or_assign("E_Infirmary", infirmary);
		ents.insert_or_assign("E_Blacksmith", blacksmith);
		ents.insert_or_assign("E_Library", library);
		ents.insert_or_assign("E_Inn",inn);
		ents.insert_or_assign("E_GeneralStore", generalStore);
		ents.insert_or_assign("E_BackArrow", backArrow);
		ents.insert_or_assign("E_aInfText", infText);

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

			auto infComp = m_data->ents.Find("E_Infirmary")->GetComponent("C_InfirmarySprite");
			if (m_data->input.isClicked(infComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_infirmaryClick = true;
			}
		}
	}

	void CastleScene::Update(float t_delatTime)
	{
		m_data->ents.Update(t_delatTime);

		auto infComp = m_data->ents.Find("E_Infirmary")->GetComponent("C_InfirmarySprite");
		if (m_infirmaryClick)
		{
			infComp->GetSprite().setColor(sf::Color(infComp->GetSprite().getColor().r - 100,
				infComp->GetSprite().getColor().g - 100,
				infComp->GetSprite().getColor().b - 100,
				infComp->GetSprite().getColor().a));

			m_infirmaryClick = false;
			m_infirmaryUnClick = true;
		}

		if (m_infirmaryUnClick)
		{
			m_time -= t_delatTime;
		}

		if (m_time <0.0f && m_infirmaryUnClick)
		{
			infComp->GetSprite().setColor(sf::Color(infComp->GetSprite().getColor().r + 100,
				infComp->GetSprite().getColor().g + 100,
				infComp->GetSprite().getColor().b + 100,
				infComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_infirmaryUnClick = false;

			m_data->ents.Find("E_aInfText")->SetVisible(true);
		}

	}

	void CastleScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render();

	}
}