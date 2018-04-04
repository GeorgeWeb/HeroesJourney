#include "Tutorial.hpp"
#include "../PauseMenu.hpp"

#include <Engine/ECM/Components/ClickableComponent.hpp>

namespace HJ { namespace Encounters {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	TutorialScene::TutorialScene(GameDataRef t_data)
		: m_data(t_data)
	{
		InitSceneView();
	}

	void TutorialScene::Init()
	{
		m_data->assets.LoadTexture("Tex_TutorialBG", TUTORIAL_ENCOUNTER);
		m_data->assets.LoadTexture("Tex_TestSkill1Btn", TEST_SKILL1_BTN);
		m_data->assets.LoadTexture("Tex_TestSkill2Btn", TEST_SKILL2_BTN);

		// Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_TutorialBGSprite");
		// define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_TutorialBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		// properties
		bgSprite->GetSprite().scale(0.9f, 0.85f);
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);
		bg->Init();

		// no unlocked heroes apart from the main character - the Knight
		m_data->gm.hKnight->SetSprite(m_data->assets.GetTexture("Tex_HeroKnight"), sf::IntRect(0, 0, 32, 32));
		m_data->gm.hKnight->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_data->gm.hKnight->GetSpriteComponent()->GetSprite().getGlobalBounds().width) * 0.1f,
			(SCREEN_HEIGHT - m_data->gm.hKnight->GetSpriteComponent()->GetSprite().getGlobalBounds().height) * 0.4f));
		m_data->gm.hKnight->Init();

		// tutorial's evil ai - frost golem
		m_data->gm.eFrostGolem = std::move(std::make_shared<EvilFrostMage>("C_FrostGolemSprite"));
		m_data->gm.eFrostGolem->SetSprite(m_data->assets.GetTexture("Tex_EvilFrostGolem"), sf::IntRect(0, 0, 135, 188));
		m_data->gm.eFrostGolem->GetSpriteComponent()->GetSprite().scale(sf::Vector2f(.25f, .2f));
		m_data->gm.eFrostGolem->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_data->gm.eFrostGolem->GetSpriteComponent()->GetSprite().getGlobalBounds().width) * 0.7f, 
			(SCREEN_HEIGHT - m_data->gm.eFrostGolem->GetSpriteComponent()->GetSprite().getGlobalBounds().height) * 0.35f));
		m_data->gm.eFrostGolem->Init();

		// ui frame
		auto uiFrame = std::make_shared<ECM::Entity>();
		auto uiFrameSprite = uiFrame->AddComponent<SpriteComponent>("C_EncounterUIFrameSprite");
		uiFrameSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		uiFrameSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_EncounterUIFrame"));
		//properties
		uiFrame->SetPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT * 0.63f));
		uiFrame->SetVisible(true);
		uiFrame->SetAlive(true);
		uiFrame->Init();

		// Attack button
		auto atkBtn = std::make_shared<ECM::Entity>();
		auto atkBtnSprite = atkBtn->AddComponent<SpriteComponent>("C_AtkBtnSprite");
		atkBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		atkBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_BasicAttackBtn"));
		//properties
		atkBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.035f, SCREEN_HEIGHT * 0.67f));
		atkBtn->SetVisible(true);
		atkBtn->SetAlive(true);
		atkBtn->Init();
		//clickable component
		auto atkBtnBtn = atkBtn->AddComponent<ClickableComponent>("C_AtkBtnBtn");
		atkBtnBtn->SetSpriteTarget(atkBtnSprite.get());

		// Defend button
		auto defBtn = std::make_shared<ECM::Entity>();
		auto defBtnSprite = defBtn->AddComponent<SpriteComponent>("C_DefBtnSprite");
		defBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		defBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_DefendBtn"));
		//properties
		defBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.16f, SCREEN_HEIGHT * 0.67f));
		defBtn->SetVisible(true);
		defBtn->SetAlive(true);
		defBtn->Init();
		//clickable component
		auto defBtnBtn = defBtn->AddComponent<ClickableComponent>("C_DefBtnBtn");
		defBtnBtn->SetSpriteTarget(defBtnSprite.get());

		// HP button
		auto hpBtn = std::make_shared<ECM::Entity>();
		auto hpBtnSprite = hpBtn->AddComponent<SpriteComponent>("C_HPBtnSprite");
		hpBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		hpBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UseHPBtn"));
		//properties
		hpBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.035f, SCREEN_HEIGHT * 0.81f));
		hpBtn->SetVisible(true);
		hpBtn->SetAlive(true);
		hpBtn->Init();
		//clickable component
		auto hpBtnBtn = hpBtn->AddComponent<ClickableComponent>("C_HPBtnBtn");
		hpBtnBtn->SetSpriteTarget(hpBtnSprite.get());

		// MP button
		auto mpBtn = std::make_shared<ECM::Entity>();
		auto mpBtnSprite = mpBtn->AddComponent<SpriteComponent>("C_MPBtnSprite");
		mpBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		mpBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UseMPBtn"));
		//properties
		mpBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.16f, SCREEN_HEIGHT * 0.81f));
		mpBtn->SetVisible(true);
		mpBtn->SetAlive(true);
		mpBtn->Init();
		//clickable component
		auto mpBtnBtn = mpBtn->AddComponent<ClickableComponent>("C_MPBtnBtn");
		mpBtnBtn->SetSpriteTarget(mpBtnSprite.get());

		// Skill1 button
		auto skill1Btn = std::make_shared<ECM::Entity>();
		auto skill1BtnSprite = skill1Btn->AddComponent<SpriteComponent>("C_Skill1BtnSprite");
		skill1BtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		skill1BtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_TestSkill1Btn"));
		//properties
		skill1Btn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.335f, SCREEN_HEIGHT * 0.669f));
		skill1Btn->SetVisible(true);
		skill1Btn->SetAlive(true);
		skill1Btn->Init();
		//clickable component
		auto skill1BtnBtn = skill1Btn->AddComponent<ClickableComponent>("C_Skill1BtnBtn");
		skill1BtnBtn->SetSpriteTarget(skill1BtnSprite.get());

		// Skill2 button
		auto skill2Btn = std::make_shared<ECM::Entity>();
		auto skill2BtnSprite = skill2Btn->AddComponent<SpriteComponent>("C_Skill2BtnSprite");
		skill2BtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		skill2BtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_TestSkill2Btn"));
		//properties
		skill2Btn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.567f, SCREEN_HEIGHT * 0.669f));
		skill2Btn->SetVisible(true);
		skill2Btn->SetAlive(true);
		skill2Btn->Init();
		//clickable component
		auto skill2BtnBtn = skill2Btn->AddComponent<ClickableComponent>("C_Skill2BtnBtn");
		skill2BtnBtn->SetSpriteTarget(skill2BtnSprite.get());
		
		// Pause button
		auto pauseBtn = std::make_shared<ECM::Entity>();
		auto pauseBtnSprite = pauseBtn->AddComponent<SpriteComponent>("C_PauseBtnSprite");
		pauseBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		pauseBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_PauseBtn"));
		//properties
		pauseBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.88f, SCREEN_HEIGHT * 0.65f));
		pauseBtn->SetVisible(true);
		pauseBtn->SetAlive(true);
		pauseBtn->Init();
		//clickable component
		auto pauseBtnBtn = pauseBtn->AddComponent<ClickableComponent>("C_PauseBtnBtn");
		pauseBtnBtn->SetSpriteTarget(pauseBtnSprite.get());

		// Concede button
		auto concedeBtn = std::make_shared<ECM::Entity>();
		auto concedeBtnSprite = concedeBtn->AddComponent<SpriteComponent>("C_ConcedeBtnSprite");
		concedeBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 128));
		concedeBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_ConcedeBtn"));
		//properties
		concedeBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.88f, SCREEN_HEIGHT * 0.82f));
		concedeBtn->SetVisible(true);
		concedeBtn->SetAlive(true);
		concedeBtn->Init();
		//clickable component
		auto concedeBtnBtn = concedeBtn->AddComponent<ClickableComponent>("C_ConcedeBtnBtn");
		concedeBtnBtn->SetSpriteTarget(concedeBtnSprite.get());

		AddEntity("E_zTutorialBG", bg);
		AddEntity("E_HeroKnight", m_data->gm.hKnight);
		AddEntity("E_EvilFrostGolem", m_data->gm.eFrostGolem);
		AddEntity("E_xTutorialUiFrame", uiFrame);
		AddEntity("E_aAtkBtn", atkBtn);
		AddEntity("E_aDefBtn", defBtn);
		AddEntity("E_aHPBtn", hpBtn);
		AddEntity("E_aMPBtn", mpBtn);
		AddEntity("E_aSkill1Btn", skill1Btn);
		AddEntity("E_aSkill2Btn", skill2Btn);
		AddEntity("E_aPauseBtn", pauseBtn);
		AddEntity("E_aConcedeBtn", concedeBtn);

		m_data->gm.unlockedHeroes.push_back(m_data->gm.hKnight);
		m_hCount = m_data->gm.unlockedHeroes.size();
	}

	void TutorialScene::HandleInput()
	{
		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView(event.size.width, event.size.height);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				// Switch scenes (to Pause Menu)
				auto pauseMenuState = std::make_unique<PauseMenuScene>(PauseMenuScene(m_data));
				m_data->machine.AddState(std::move(pauseMenuState), false);
			}
			
			#pragma region OPTIONS BUTTONS CLICKED CHECKS
			// check if pause button is clicked
			auto pauseBtnSprite = m_data->ents.Find<Entity>("E_aPauseBtn")->GetComponent<SpriteComponent>("C_PauseBtnSprite");
			auto pauseBtnBtn = m_data->ents.Find<Entity>("E_aPauseBtn")->GetComponent<ClickableComponent>("C_PauseBtnBtn");
			if (pauseBtnSprite->IsClickable() && m_data->input.isClicked(pauseBtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				pauseBtnBtn->SetClicked(true);
			}
			#pragma endregion

			#pragma region BATTLE BUTTONS CLICKED CHECKS
			// check if attack button is clicked
			auto atkBtnSprite = m_data->ents.Find<Entity>("E_aAtkBtn")->GetComponent<SpriteComponent>("C_AtkBtnSprite");
			auto atkBtnBtn = m_data->ents.Find<Entity>("E_aAtkBtn")->GetComponent<ClickableComponent>("C_AtkBtnBtn");
			if (atkBtnSprite->IsClickable() && m_data->input.isClicked(atkBtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				atkBtnBtn->SetClicked(true);
			}

			// check if defend button is clicked
			auto defBtnSprite = m_data->ents.Find<Entity>("E_aDefBtn")->GetComponent<SpriteComponent>("C_DefBtnSprite");
			auto defBtnBtn = m_data->ents.Find<Entity>("E_aDefBtn")->GetComponent<ClickableComponent>("C_DefBtnBtn");
			if (defBtnSprite->IsClickable() && m_data->input.isClicked(defBtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				defBtnBtn->SetClicked(true);
			}

			// check if use HP button is clicked
			auto hpBtnSprite = m_data->ents.Find<Entity>("E_aHPBtn")->GetComponent<SpriteComponent>("C_HPBtnSprite");
			auto hpBtnBtn = m_data->ents.Find<Entity>("E_aHPBtn")->GetComponent<ClickableComponent>("C_HPBtnBtn");
			if (hpBtnSprite->IsClickable() && m_data->input.isClicked(hpBtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				hpBtnBtn->SetClicked(true);
			}

			// check if use MP button is clicked
			auto mpBtnSprite = m_data->ents.Find<Entity>("E_aMPBtn")->GetComponent<SpriteComponent>("C_MPBtnSprite");
			auto mpBtnBtn = m_data->ents.Find<Entity>("E_aMPBtn")->GetComponent<ClickableComponent>("C_MPBtnBtn");
			if (mpBtnSprite->IsClickable() && m_data->input.isClicked(mpBtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				mpBtnBtn->SetClicked(true);
			}

			// check if use HP button is clicked
			auto skill1BtnSprite = m_data->ents.Find<Entity>("E_aSkill1Btn")->GetComponent<SpriteComponent>("C_Skill1BtnSprite");
			auto skill1BtnBtn = m_data->ents.Find<Entity>("E_aSkill1Btn")->GetComponent<ClickableComponent>("C_Skill1BtnBtn");
			if (skill1BtnSprite->IsClickable() && m_data->input.isClicked(skill1BtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				skill1BtnBtn->SetClicked(true);
			}

			// check if use MP button is clicked
			auto skill2BtnSprite = m_data->ents.Find<Entity>("E_aSkill2Btn")->GetComponent<SpriteComponent>("C_Skill2BtnSprite");
			auto skill2BtnBtn = m_data->ents.Find<Entity>("E_aSkill2Btn")->GetComponent<ClickableComponent>("C_Skill2BtnBtn");
			if (skill2BtnSprite->IsClickable() && m_data->input.isClicked(skill2BtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				skill2BtnBtn->SetClicked(true);
			}
			#pragma endregion
		}
	}

	void TutorialScene::Update(float t_delatTime)
	{
		#pragma region OPTIONS BUTTONS
		// resolve pause button click
		auto pauseBtnBtn = m_data->ents.Find<Entity>("E_aPauseBtn")->GetComponent<ClickableComponent>("C_PauseBtnBtn");
		if (pauseBtnBtn->CanResolve())
		{
			// Switch scenes (to Pause Menu)
			auto pauseMenuState = std::make_unique<PauseMenuScene>(PauseMenuScene(m_data));
			m_data->machine.AddState(std::move(pauseMenuState), false);

			pauseBtnBtn->SetResolve(false);
		}
		#pragma endregion

		#pragma region BATTLE BUTTONS
		// sprite components
		auto atkBtnSprite = m_data->ents.Find<Entity>("E_aAtkBtn")->GetComponent<SpriteComponent>("C_AtkBtnSprite");
		auto defBtnSprite = m_data->ents.Find<Entity>("E_aDefBtn")->GetComponent<SpriteComponent>("C_DefBtnSprite");
		auto hpBtnSprite = m_data->ents.Find<Entity>("E_aHPBtn")->GetComponent<SpriteComponent>("C_HPBtnSprite");
		auto mpBtnSprite = m_data->ents.Find<Entity>("E_aMPBtn")->GetComponent<SpriteComponent>("C_MPBtnSprite");
		auto skill1BtnSprite = m_data->ents.Find<Entity>("E_aSkill1Btn")->GetComponent<SpriteComponent>("C_Skill1BtnSprite");
		auto skill2BtnSprite = m_data->ents.Find<Entity>("E_aSkill2Btn")->GetComponent<SpriteComponent>("C_Skill2BtnSprite");

		// clickable components
		auto atkBtnBtn = m_data->ents.Find<Entity>("E_aAtkBtn")->GetComponent<ClickableComponent>("C_AtkBtnBtn");
		auto defBtnBtn = m_data->ents.Find<Entity>("E_aDefBtn")->GetComponent<ClickableComponent>("C_DefBtnBtn");
		auto hpBtnBtn = m_data->ents.Find<Entity>("E_aHPBtn")->GetComponent<ClickableComponent>("C_HPBtnBtn");
		auto mpBtnBtn = m_data->ents.Find<Entity>("E_aMPBtn")->GetComponent<ClickableComponent>("C_MPBtnBtn");
		auto skill1BtnBtn = m_data->ents.Find<Entity>("E_aSkill1Btn")->GetComponent<ClickableComponent>("C_Skill1BtnBtn");
		auto skill2BtnBtn = m_data->ents.Find<Entity>("E_aSkill2Btn")->GetComponent<ClickableComponent>("C_Skill2BtnBtn");
		#pragma endregion

		// list of the UI button sprites to be disabled/enabled on turn change
		static std::vector<SpriteComponent*> battleUIButtons = { atkBtnSprite, defBtnSprite, hpBtnSprite, mpBtnSprite, skill1BtnSprite, skill2BtnSprite };

		// [TEMP] initial enemy state properties
		static sf::Vector2f enemyInitPos = m_data->gm.eFrostGolem->GetPosition();
		static bool enemyMoveLeft = false;
		static bool enemyMoveRight = false;
		static bool canEnemyAttack = false;

		// update turn
		m_turn = (m_hCount > 0) ? BATTLE_TURN::HERO : BATTLE_TURN::EVIL;
		switch (m_turn)
		{
			case BATTLE_TURN::HERO:
				// resolve attack button click
				if (atkBtnBtn->CanResolve())
				{
					std::cout << "Button has been clicked!\n";

					// next player turn
					m_hCount--;

					DisableUIButtons(battleUIButtons);

					// set enemy movement state
					enemyMoveLeft = true;

					atkBtnBtn->SetResolve(false);
				}

				// resolve defend button click
				if (defBtnBtn->CanResolve())
				{
					std::cout << "Button has been clicked!\n";

					// next player turn
					m_hCount--;

					DisableUIButtons(battleUIButtons);

					// set enemy movement state
					enemyMoveLeft = true;

					defBtnBtn->SetResolve(false);
				}

				// resolve use HP button click
				if (hpBtnBtn->CanResolve())
				{
					std::cout << "Button has been clicked!\n";

					hpBtnBtn->SetResolve(false);
				}

				// resolve use MP button click
				if (mpBtnBtn->CanResolve())
				{
					std::cout << "Button has been clicked!\n";

					mpBtnBtn->SetResolve(false);
				}

				// resolve use HP button click
				if (skill1BtnBtn->CanResolve())
				{
					std::cout << "Button has been clicked!\n";

					// next player turn
					m_hCount--;
					
					DisableUIButtons(battleUIButtons);

					// set enemy movement state
					enemyMoveLeft = true;

					skill1BtnBtn->SetResolve(false);
				}

				// resolve use MP button click
				if (skill2BtnBtn->CanResolve())
				{
					std::cout << "Button has been clicked!\n";

					// next player turn
					m_hCount--;

					DisableUIButtons(battleUIButtons);

					// set enemy movement state
					enemyMoveLeft = true;

					skill2BtnBtn->SetResolve(false);
				}
				break;
			case BATTLE_TURN::EVIL:
				// move to attacking position
				// TODO: ABSTRACT IN A MOVEMENT COMPONENT
				if (enemyMoveLeft)
					m_data->gm.eFrostGolem->Move(sf::Vector2f(-10.0f, 0.0f));
				if (enemyMoveRight)
					m_data->gm.eFrostGolem->Move(sf::Vector2f(10.0f, 0.0f));

				// check for destination reached -> go back -> rest heroes turn count
				if (m_data->gm.eFrostGolem->GetPosition().x <= SCREEN_WIDTH / 2.0f && enemyMoveLeft)
				{
					enemyMoveLeft = false;
					enemyMoveRight = true;
				}
				else canEnemyAttack = true;

				if (m_data->gm.eFrostGolem->GetPosition().x >= enemyInitPos.x && canEnemyAttack)
				{
					// reset to initial position if not accurately there
					m_data->gm.eFrostGolem->SetPosition(enemyInitPos);

					std::cout << "Attacking\n";
					// STATE MACHINES ...
					// ATTACK ...

					EnableUIButtons(battleUIButtons);

					// reset heroes count for turn update
					m_hCount = m_data->gm.unlockedHeroes.size();

					// reset enemy states
					enemyMoveRight = false;
					canEnemyAttack = false;
				}

				break;
			default:
				break;
		}		
		m_data->ents.Update(m_entities, t_delatTime);
	}

	void TutorialScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void TutorialScene::AddEntity(const std::string & t_name, std::shared_ptr<ECM::Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}

	void TutorialScene::DisableUIButtons(std::vector<Components::SpriteComponent*> t_buttons)
	{
		for (auto btn : t_buttons)
		{
			btn->GetSprite().setColor(sf::Color(255, 255, 255, 128));
			btn->SetClickable(false);
		}
	}

	void TutorialScene::EnableUIButtons(std::vector<Components::SpriteComponent*> t_buttons)
	{
		for (auto btn : t_buttons)
		{
			btn->GetSprite().setColor(sf::Color(255, 255, 255, 255));
			btn->SetClickable(true);
		}
	}

} }