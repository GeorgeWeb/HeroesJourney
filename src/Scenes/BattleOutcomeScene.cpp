#include "BattleOutcomeScene.hpp"
#include "PauseMenu.hpp"
#include "Encounters/Tutorial.hpp"
#include "MapScene.hpp"

#include <sstream>
#include <iostream>

#include <Engine/ECM/Components/TextComponent.hpp>
#include <Engine/ECM/Components/SpriteComponent.hpp>

namespace HJ {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	BattleOutcomeScene::BattleOutcomeScene(GameDataRef t_data) :
		m_data(t_data)

	{ }

	void BattleOutcomeScene::Init()
	{
		// load assets
		m_data->assets.LoadTexture("Tex_VictoryBG", SPLASH_SCENE_BACKGROUND);
		

		//Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_zBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_VictoryBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);
		bg->Init();

		// create entities
		auto victoryText = std::make_shared<Entity>();
		auto infTextFont = victoryText->AddComponent<TextComponent>("C_Text");
		// define
		infTextFont->SetFont(m_data->assets.GetFont("Font_Pixel"));
		infTextFont->GetText().setCharacterSize(66);
		if (m_data->gm.loot == 0)
		{
			// set lose text
			infTextFont->GetText().setString("DEFEAT!");

			// set lose sound
			m_outBfr = m_data->assets.LoadBuffer(DEFEAT_SOUND);
			m_outSnd.setBuffer(*m_outBfr);
		}
		else
		{
			// set win text
			infTextFont->GetText().setString("VICTORY!");

			// set win sound
			m_outBfr = m_data->assets.LoadBuffer(VICTORY_SOUND);
			m_outSnd.setBuffer(*m_outBfr);
		}
		victoryText->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.5f - infTextFont->GetText().getGlobalBounds().width * 0.5f, (SCREEN_HEIGHT * 0.5f) - (infTextFont->GetText().getGlobalBounds().height * 0.5f)));
		// properties
		victoryText->showOnCreate = true;
		victoryText->SetVisible(true);
		victoryText->SetAlive(true);
		victoryText->Init();

		// loot text;
		auto lootText = std::make_shared<Entity>();
		auto lootTextComp = lootText->AddComponent<TextComponent>("C_Text");
		// define
		lootTextComp->SetFont(m_data->assets.GetFont("Font_Pixel"));
		lootTextComp->GetText().setCharacterSize(24);
		lootTextComp->GetText().setString("Reward: " + std::to_string( m_data->gm.loot));
		lootText->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.5f - infTextFont->GetText().getGlobalBounds().width * 0.5f, SCREEN_HEIGHT * 0.5f + infTextFont->GetText().getGlobalBounds().height + lootTextComp->GetText().getGlobalBounds().height));
		// properties
		lootText->showOnCreate = true;
		lootText->SetVisible(true);
		lootText->SetAlive(true);
		lootText->Init();

		//Coin sprite
		auto coin = std::make_shared<Entity>();
		auto coinSprite = coin->AddComponent<SpriteComponent>("C_LootCoin");
		//sprite define
		coinSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Coin"));
		coinSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		coinSprite->GetSprite().scale(2.0f, 2.0f);
		coin->SetPosition(sf::Vector2f(lootText->GetPosition().x + lootTextComp->GetText().getGlobalBounds().width, lootText->GetPosition().y - coinSprite->GetSprite().getGlobalBounds().height * 0.23f));
		//properties
		coin->SetVisible(true);
		coin->SetAlive(true);
		coin->Init();

		// play win/lose sound
		m_outSnd.play();

		// populate the entities container
		AddEntity("E_zVictoryBG", bg);
		AddEntity("E_VictoryText", victoryText);
		AddEntity("E_LootText", lootText);
		AddEntity("E_Coin", coin);
	}

	void BattleOutcomeScene::HandleInput()
	{
		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView(event.size.width, event.size.height);

			auto bgSprite = m_data->ents.Find<Entity>("E_zVictoryBG")->GetComponent<SpriteComponent>("C_zBGSprite");
			if (sf::Keyboard::isKeyPressed(Controls::GetKey("Skip")) || sf::Keyboard::isKeyPressed(Controls::GetKey("Back")) 
				|| (bgSprite->IsClickable() && m_data->input.isClicked(bgSprite->GetSprite(), Controls::GetButton("Select"), Engine2D::GetWin())))
			{
				m_data->gm.gold += m_data->gm.loot;

				if (m_data->gm.nextEncounter == 0 || m_data->gm.loot == 0)
				{
					m_data->gm.battlePassed = true;
					auto map = std::make_shared<MapScene>(MapScene(m_data));
					m_data->machine.AddState(map);
					// reset loot
					m_data->gm.loot = 0;
				}

				else if (m_data->gm.nextEncounter == 1)
				{
					auto meetbard = std::make_shared<MeetBardScene>(MeetBardScene(m_data));
					m_data->machine.AddState(meetbard);
					// reset loot
					m_data->gm.loot = 0;
				}

				else if (m_data->gm.nextEncounter == 2)
				{
					auto meetrogue = std::make_shared<MeetRogueScene>(MeetRogueScene(m_data));
					m_data->machine.AddState(meetrogue);
					// reset loot
					m_data->gm.loot = 0;
				}

				else if (m_data->gm.nextEncounter == 3)
				{
					auto meetsorc = std::make_shared<MeetSorcScene>(MeetSorcScene(m_data));
					m_data->machine.AddState(meetsorc);
					// reset loot
					m_data->gm.loot = 0;
				}

				else if (m_data->gm.nextEncounter == 4)
				{
					auto finalstory = std::make_shared<FinalStoryScene>(FinalStoryScene(m_data));
					m_data->machine.AddState(finalstory);
					// reset loot
					m_data->gm.loot = 0;
				}
			}
		}
	}

	void BattleOutcomeScene::Update(float t_delatTime)
	{
		m_data->ents.Update(m_entities, t_delatTime);
	}

	void BattleOutcomeScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void BattleOutcomeScene::AddEntity(const std::string & t_name, std::shared_ptr<ECM::Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}

}