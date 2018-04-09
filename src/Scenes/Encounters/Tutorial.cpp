#include "Tutorial.hpp"
#include "../PauseMenu.hpp"
#include "../MapScene.hpp"

#include <Engine/ECM/Components/ClickableComponent.hpp>
#include "../../States/BaseStates.hpp"

namespace HJ { namespace Encounters {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace Entities;

	TutorialScene::TutorialScene(GameDataRef t_data)
		: m_data(t_data)
	{
		InitSceneView();
	}

	void TutorialScene::Init()
	{
		m_data->assets.LoadTexture("Tex_TutorialBG", TUTORIAL_ENCOUNTER);
	
		// populate the active heroes list with the currently unlocked ones before the battle starts
		m_activeHeroes.push_back(m_data->gm.hBard);
		m_activeHeroes.push_back(m_data->gm.hKnight);
		// set the turn count to the size of all active heroes
		m_hTurnCount = m_activeHeroes.size();

		// Background
		auto bg = std::make_shared<Entity>();
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
		// Add HP/MP UI Component
		// TODO: ...

		// no unlocked heroes apart from the main character - the Knight
		m_data->gm.hBard->SetSprite(m_data->assets.GetTexture("Tex_HeroKnight"), sf::IntRect(0, 0, 32, 32));
		m_data->gm.hBard->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_data->gm.hBard->GetSpriteComponent()->GetSprite().getGlobalBounds().width) * 0.1f,
			(SCREEN_HEIGHT - m_data->gm.hBard->GetSpriteComponent()->GetSprite().getGlobalBounds().height) * 0.1f));
		m_data->gm.hBard->Init();
		// Add HP/MP UI Component
		// TODO: ...

		// tutorial's evil ai - frost golem
		m_frostGolem = std::make_shared<Hero>("Frost Golem", HERO_TYPE::EVIL, 100, 20, 10);
		m_frostGolem->SetSprite(m_data->assets.GetTexture("Tex_EvilFrostGolem"), sf::IntRect(0, 0, 135, 188));
		m_frostGolem->GetSpriteComponent()->GetSprite().scale(sf::Vector2f(.25f, .4f));
		m_frostGolem->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_frostGolem->GetSpriteComponent()->GetSprite().getGlobalBounds().width) * 0.7f,
			(SCREEN_HEIGHT - m_frostGolem->GetSpriteComponent()->GetSprite().getGlobalBounds().height) * 0.1f));
		m_frostGolem->Init();
		/*
		m_frostGolem->GetSMComponent()->AddState("Idle", std::make_shared<States::BaseIdleState>());
		m_frostGolem->GetSMComponent()->AddState("StepIn", std::make_shared<States::BaseStepInState>(sf::Vector2f(SCREEN_WIDTH / 1.75f, m_frostGolem->GetPosition().y), 7.5f));
		m_frostGolem->GetSMComponent()->AddState("StepBack", std::make_shared<States::BaseStepBackState>(sf::Vector2f(m_frostGolem->GetPosition()), 7.5f));
		m_frostGolem->GetSMComponent()->AddState("Attack", std::make_shared<States::BaseAttackState>(m_activeHeroes, m_frostGolem->GetDmg()));
		// m_frostGolem->GetSMComponent()->AddState("ChooseTarget", std::make_shared<States::BaseFinishState>(m_activeHeroes, { m_frostGolem }));
		m_frostGolem->GetSMComponent()->ChangeState("Idle");
		*/
		// Add HP UI Component
		// TODO: ...

		// create an event-like action resolver for hero/ai - [actions/events]
		m_actionResolver = std::make_shared<ActionResolver>();

		/*** CREATE UI ELEMENTS ***/

		// ui frame
		auto uiFrame = std::make_shared<Entity>();
		auto uiFrameSprite = uiFrame->AddComponent<SpriteComponent>("C_EncounterUIFrameSprite");
		uiFrameSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		uiFrameSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_EncounterUIFrame"));
		//properties
		uiFrame->SetPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT * 0.63f));
		uiFrame->SetVisible(true);
		uiFrame->SetAlive(true);
		uiFrame->Init();
		m_allUIcomps.push_back(uiFrameSprite.get());

		// Attack button
		auto atkBtn = std::make_shared<Button>();
		auto atkBtnSprite = atkBtn->GetSpriteComponent();
		atkBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		atkBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_BasicAttackBtn"));
		//properties
		atkBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.035f, SCREEN_HEIGHT * 0.67f));
		atkBtn->Init();
		//clickable component
		m_allUIcomps.push_back(atkBtnSprite.get());

		// Defend button
		auto defBtn = std::make_shared<Button>();
		auto defBtnSprite = defBtn->GetSpriteComponent();
		defBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		defBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_DefendBtn"));
		//properties
		defBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.16f, SCREEN_HEIGHT * 0.67f));
		defBtn->SetVisible(true);
		defBtn->SetAlive(true);
		defBtn->Init();
		m_allUIcomps.push_back(defBtnSprite.get());

		// HP button
		auto hpBtn = std::make_shared<Button>();
		// sprite
		auto hpBtnSprite = hpBtn->GetSpriteComponent();
		hpBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		hpBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UseHPBtn"));
		hpBtnSprite->GetSprite().scale(3.0f, 3.0f);
		//properties
		hpBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.035f, SCREEN_HEIGHT * 0.81f));
		hpBtn->Init();
		m_allUIcomps.push_back(hpBtnSprite.get());

		// MP button
		auto mpBtn = std::make_shared<Button>();
		// sprite
		auto mpBtnSprite = mpBtn->GetSpriteComponent();
		mpBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		mpBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UseMPBtn"));
		mpBtnSprite->GetSprite().scale(3.0f, 3.0f);
		//properties
		mpBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.16f, SCREEN_HEIGHT * 0.81f));
		mpBtn->Init();
		m_allUIcomps.push_back(mpBtnSprite.get());

		// Skill1 button
		auto skill1Btn = std::make_shared<Button>();
		// sprite
		auto skill1BtnSprite = skill1Btn->GetSpriteComponent();
		skill1BtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		skill1BtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_TestSkillBtn"));
		// text
		auto skill1BtnText = skill1Btn->GetTextComponent();
		skill1BtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		skill1BtnText->GetText().setStyle(sf::Text::Bold);
		skill1BtnText->GetText().setString("Skill 1");
		skill1BtnText->GetText().setCharacterSize(18);
		//properties
		skill1Btn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.335f, SCREEN_HEIGHT * 0.669f));
		skill1Btn->Init();
		skill1BtnText->GetText().setPosition(skill1Btn->GetPosition().x, skill1Btn->GetPosition().y + 220.0f);
		m_allUIcomps.push_back(skill1BtnSprite.get());

		// Skill2 button
		auto skill2Btn = std::make_shared<Button>();
		// sprite
		auto skill2BtnSprite = skill2Btn->GetSpriteComponent();
		skill2BtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		skill2BtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_TestSkillBtn"));
		// text
		auto skill2BtnText = skill2Btn->GetTextComponent();
		skill2BtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		skill2BtnText->GetText().setStyle(sf::Text::Bold);
		skill2BtnText->GetText().setString("Skill 2");
		skill2BtnText->GetText().setCharacterSize(18);
		// general properties
		skill2Btn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.567f, SCREEN_HEIGHT * 0.669f));
		skill2Btn->Init();
		skill2BtnText->GetText().setPosition(skill2Btn->GetPosition().x, skill2Btn->GetPosition().y + 220.0f);
		m_allUIcomps.push_back(skill2BtnSprite.get());

		// Pause button
		auto pauseBtn = std::make_shared<Button>();
		// sprite
		auto pauseBtnSprite = pauseBtn->GetSpriteComponent();
		pauseBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		pauseBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		pauseBtnSprite->GetSprite().scale(0.75f, 0.75f);
		// text
		auto pauseBtnText = pauseBtn->GetTextComponent();
		pauseBtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		pauseBtnText->GetText().setString("Pause");
		pauseBtnText->GetText().scale(0.75f, 0.75f);
		pauseBtnText->GetText().setCharacterSize(24);
		// general properties
		pauseBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.67f));
		pauseBtn->Init();
		// center text
		pauseBtnText->GetText().setPosition(pauseBtn->GetPosition().x + pauseBtnText->GetText().getGlobalBounds().width * 0.7f, 
								pauseBtn->GetPosition().y + pauseBtnText->GetText().getGlobalBounds().height * 1.2f);
		m_allUIcomps.push_back(pauseBtnSprite.get());

		// Concede button
		auto concedeBtn = std::make_shared<Button>();
		// sprite
		auto concedeBtnSprite = concedeBtn->GetSpriteComponent();
		concedeBtnSprite->GetSprite().setColor(sf::Color(155, 155, 155, 55));
		concedeBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		concedeBtnSprite->GetSprite().scale(0.75f, 0.75f);
		// text
		auto concedeBtnText = concedeBtn->GetTextComponent();
		concedeBtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		concedeBtnText->GetText().setColor(sf::Color(155, 155, 155, 55));
		concedeBtnText->GetText().setString("Concede");
		concedeBtnText->GetText().scale(0.75f, 0.75f);
		concedeBtnText->GetText().setCharacterSize(24);
		// general properties
		concedeBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.81f));
		concedeBtn->Init();
		// center text
		concedeBtnText->GetText().setPosition(concedeBtn->GetPosition().x + concedeBtnText->GetText().getGlobalBounds().width * 0.375f,
			concedeBtn->GetPosition().y + concedeBtnText->GetText().getGlobalBounds().height * 1.125f);
		m_allUIcomps.push_back(concedeBtnSprite.get());

		// Text indicating who is on turn
		auto turnTxt = std::make_shared<Entity>();
		auto turnTxtComp = turnTxt->AddComponent<TextComponent>("C_CharacterTurnText");
		turnTxtComp->GetText().setFont(m_data->assets.GetFont("Font_Pixel"));
		turnTxtComp->GetText().setCharacterSize(14);
		turnTxtComp->GetText().setString(m_charOnTurn);
		turnTxtComp->GetText().setColor(sf::Color::White);
		turnTxtComp->GetText().setStyle(sf::Text::Bold);
		turnTxt->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.035f, SCREEN_HEIGHT * 0.965f));
		turnTxt->SetAlive(true);
		turnTxt->SetVisible(true);
		turnTxt->Init();

		AddEntity("E_zTutorialBG", bg);
		AddEntity("E_HeroKnight", m_data->gm.hKnight);
		AddEntity("E_HeroBard", m_data->gm.hBard);
		AddEntity("E_EvilFrostGolem", m_frostGolem);
		AddEntity("E_xTutorialUiFrame", uiFrame);
		AddEntity("E_aAtkBtn", atkBtn);
		AddEntity("E_aDefBtn", defBtn);
		AddEntity("E_aHPBtn", hpBtn);
		AddEntity("E_aMPBtn", mpBtn);
		AddEntity("E_aSkill1Btn", skill1Btn);
		AddEntity("E_aSkill2Btn", skill2Btn);
		AddEntity("E_aPauseBtn", pauseBtn);
		AddEntity("E_aConcedeBtn", concedeBtn);
		AddEntity("E_aTurnTxt", turnTxt);

		// list of the UI button sprites to be disabled/enabled on turn change
		std::vector<SpriteComponent*> battleBtnSprites { atkBtnSprite.get(), defBtnSprite.get(), hpBtnSprite.get(), mpBtnSprite.get(), skill1BtnSprite.get(), skill2BtnSprite.get() };
		m_battleUIButtons.insert(m_battleUIButtons.end(), battleBtnSprites.begin(), battleBtnSprites.end());

		// begin the battle
		m_status = BATTLE_STATUS::PLAYING;
		// the main hero - Knight, always starts first
		NextTurn();
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
			auto pauseBtnSprite = m_data->ents.Find<Button>("E_aPauseBtn")->GetSpriteComponent();
			auto pauseBtnBtn = m_data->ents.Find<Button>("E_aPauseBtn")->GetClickableComponent();
			if (pauseBtnSprite->IsClickable() && m_data->input.isClicked(pauseBtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				pauseBtnBtn->SetClicked(true);
			}
#pragma endregion

#pragma region BATTLE BUTTONS CLICKED CHECKS
			// check if attack button is clicked
			auto atkBtnSprite = m_data->ents.Find<Button>("E_aAtkBtn")->GetSpriteComponent();
			auto atkBtnBtn = m_data->ents.Find<Button>("E_aAtkBtn")->GetClickableComponent();
			if (atkBtnSprite->IsClickable() && m_data->input.isClicked(atkBtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				atkBtnBtn->SetClicked(true);
			}

			// check if defend button is clicked
			auto defBtnSprite = m_data->ents.Find<Button>("E_aDefBtn")->GetSpriteComponent();
			auto defBtnBtn = m_data->ents.Find<Button>("E_aDefBtn")->GetClickableComponent();
			if (defBtnSprite->IsClickable() && m_data->input.isClicked(defBtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				defBtnBtn->SetClicked(true);
			}

			// check if use HP button is clicked
			auto hpBtnSprite = m_data->ents.Find<Button>("E_aHPBtn")->GetSpriteComponent();
			auto hpBtnBtn = m_data->ents.Find<Button>("E_aHPBtn")->GetClickableComponent();
			if (hpBtnSprite->IsClickable() && m_data->input.isClicked(hpBtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				hpBtnBtn->SetClicked(true);
			}

			// check if use MP button is clicked
			auto mpBtnSprite = m_data->ents.Find<Button>("E_aMPBtn")->GetSpriteComponent();
			auto mpBtnBtn = m_data->ents.Find<Button>("E_aMPBtn")->GetClickableComponent();
			if (mpBtnSprite->IsClickable() && m_data->input.isClicked(mpBtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				mpBtnBtn->SetClicked(true);
			}

			// check if use HP button is clicked
			auto skill1BtnSprite = m_data->ents.Find<Button>("E_aSkill1Btn")->GetSpriteComponent();
			auto skill1BtnBtn = m_data->ents.Find<Button>("E_aSkill1Btn")->GetClickableComponent();
			if (skill1BtnSprite->IsClickable() && m_data->input.isClicked(skill1BtnSprite->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				skill1BtnBtn->SetClicked(true);
			}

			// check if use MP button is clicked
			auto skill2BtnSprite = m_data->ents.Find<Button>("E_aSkill2Btn")->GetSpriteComponent();
			auto skill2BtnBtn = m_data->ents.Find<Button>("E_aSkill2Btn")->GetClickableComponent();
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
		auto pauseBtnBtn = m_data->ents.Find<Button>("E_aPauseBtn")->GetClickableComponent();
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
		auto atkBtnSprite = m_data->ents.Find<Button>("E_aAtkBtn")->GetSpriteComponent();
		auto defBtnSprite = m_data->ents.Find<Button>("E_aDefBtn")->GetSpriteComponent();
		auto hpBtnSprite = m_data->ents.Find<Button>("E_aHPBtn")->GetSpriteComponent();
		auto mpBtnSprite = m_data->ents.Find<Button>("E_aMPBtn")->GetSpriteComponent();
		auto skill1BtnSprite = m_data->ents.Find<Button>("E_aSkill1Btn")->GetSpriteComponent();
		auto skill2BtnSprite = m_data->ents.Find<Button>("E_aSkill2Btn")->GetSpriteComponent();

		// clickable components
		auto atkBtnBtn = m_data->ents.Find<Button>("E_aAtkBtn")->GetClickableComponent();
		auto defBtnBtn = m_data->ents.Find<Button>("E_aDefBtn")->GetClickableComponent();
		auto hpBtnBtn = m_data->ents.Find<Button>("E_aHPBtn")->GetClickableComponent();
		auto mpBtnBtn = m_data->ents.Find<Button>("E_aMPBtn")->GetClickableComponent();
		auto skill1BtnBtn = m_data->ents.Find<Button>("E_aSkill1Btn")->GetClickableComponent();
		auto skill2BtnBtn = m_data->ents.Find<Button>("E_aSkill2Btn")->GetClickableComponent();
#pragma endregion
		
		// check if a hero is dead
		// CheckForDeaths();

		// check for condition to exit the battle (win/lose)
		CheckForBattleOutcome();

		// check if any disabled UI elemnts can be reset to enabled (after AI turn)
		UpdateUI();

		/*
		// initial hero state properties FOR action behaviour preparation
		static sf::Vector2f heroInitPos = m_heroOnTurn->GetPosition();
		HandleHeroActions(heroInitPos);
		*/

		// update turn
		m_turn = !chosen ? BATTLE_TURN::EVIL : BATTLE_TURN::HERO;
		// update hero on turn
		switch (m_turn)
		{
			case BATTLE_TURN::HERO:
				//m_charOnTurn = typeid(m_heroOnTurn).name();
				if (atkBtnBtn->CanResolve() && !m_actionResolver->IsActive())
				{
					// heroStepIn = true;
				}

				// resolve defend button click
				if (defBtnBtn->CanResolve() && !m_actionResolver->IsActive())
				{
					std::cout << "Hero defending!\n";
					m_heroOnTurn->ExecuteSkill(m_heroOnTurn->GetSkillComponent()->FindSkill(SKILL_NAME::BASIC_DEFENCE), m_heroOnTurn);

					// next hero turn
					NextTurn();

					defBtnBtn->SetResolve(false);
				}

				// resolve use HP button click
				if (hpBtnBtn->CanResolve() && !m_actionResolver->IsActive())
				{
					std::cout << "Hero used HP potion!\n";

					hpBtnBtn->SetResolve(false);
				}

				// resolve use MP button click
				if (mpBtnBtn->CanResolve() && !m_actionResolver->IsActive())
				{
					std::cout << "Hero used MP potion!\n";

					mpBtnBtn->SetResolve(false);
				}

				// resolve skill1 button click
				if (skill1BtnBtn->CanResolve() && !m_actionResolver->IsActive())
				{
					// heroStepIn = true;
				}

				// resolve skill2 button click
				if (skill2BtnBtn->CanResolve() && !m_actionResolver->IsActive())
				{
					// heroStepIn = true;
				}
				break;
			case BATTLE_TURN::EVIL:
				// disable player's battle UI buttons
				DisableUIButtons();
				// reset heroes original texture color
				for (auto hero : m_activeHeroes)
					if (hero->GetHealth() > 0) hero->GetSpriteComponent()->GetSprite().setColor(sf::Color(255, 255, 255, 255));
				// start state machine
				if (!m_actionResolver->IsActive() && m_actionResolver->GetSMComponent()->CurrentState() == "Idle")
				{
					m_actionResolver->Activate(m_frostGolem, m_activeHeroes);
				}
				else if (!m_actionResolver->IsActive() && m_actionResolver->GetSMComponent()->CurrentState() == "Finish"
				 && !isEvalComplete)
				{
					m_turn = BATTLE_TURN::BETWEEN;
					// evaluate the round & check win condition
					Evaluate();
				}
				else if (!m_actionResolver->IsActive() && m_actionResolver->GetSMComponent()->CurrentState() == "Finish"
					&& isEvalComplete)
				{
					isEvalComplete = false;
					// stop the action resolver after evaluation is complete
					m_actionResolver->Stop();
					// change turn
					m_hTurnCount = m_activeHeroes.size();
					std::cout << "NEXT TURN!\n";
					NextTurn();
				}
				break;
			default:
			case BATTLE_TURN::BETWEEN:
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

	void TutorialScene::DisableUIButtons()
	{
		for (auto uiBtn : m_battleUIButtons)
		{
			uiBtn->GetSprite().setColor(sf::Color(155, 155, 155, 55));
			uiBtn->SetClickable(false);
		}
	}

	void TutorialScene::EnableUIButtons()
	{
		for (auto uiBtn : m_battleUIButtons)
		{
			uiBtn->GetSprite().setColor(sf::Color(255, 255, 255, 255));
			uiBtn->SetClickable(true);
		}
	}

	void TutorialScene::UpdateUI()
	{
		// update the who is on turn text indicator for [EVIL]
		if (m_turn == BATTLE_TURN::EVIL)
		{
			m_charOnTurn = m_frostGolem->className();
			std::string evilHP = std::to_string(m_frostGolem->GetHealth()) + "/" + std::to_string(m_frostGolem->GetMaxHealth()) + "HP";
			m_data->ents.Find<Entity>("E_aTurnTxt")->GetComponent<TextComponent>("C_CharacterTurnText")->GetText().setString(m_charOnTurn + ": " + evilHP);
			m_data->ents.Find<Entity>("E_aTurnTxt")->GetComponent<TextComponent>("C_CharacterTurnText")->GetText().setColor(sf::Color::Red);
		}
		// update the who is on turn text indicator & battle UI sprite textures for [HERO]
		if (m_turn == BATTLE_TURN::HERO)
		{
			// update text indicator
			m_charOnTurn = m_heroOnTurn->className();
			std::string heroHP = std::to_string(m_heroOnTurn->GetHealth()) + "/" + std::to_string(m_heroOnTurn->GetMaxHealth()) + "HP";
			std::string heroMP = std::to_string(m_heroOnTurn->GetMana()) + "/" + std::to_string(m_heroOnTurn->GetMaxMana()) + "MP";
			m_data->ents.Find<Entity>("E_aTurnTxt")->GetComponent<TextComponent>("C_CharacterTurnText")->GetText().setString(m_charOnTurn + ": " + heroHP + " | " + heroMP);
			m_data->ents.Find<Entity>("E_aTurnTxt")->GetComponent<TextComponent>("C_CharacterTurnText")->GetText().setColor(sf::Color::White);
			// update battle UI sprite textures
			sf::Texture& basicAttTex = m_data->assets.GetTexture(m_heroOnTurn->GetSkillComponent()->FindSkill(SKILL_NAME::BASIC_ATTACK)->textureRefName);
			sf::Texture& basicDefTex = m_data->assets.GetTexture(m_heroOnTurn->GetSkillComponent()->FindSkill(SKILL_NAME::BASIC_DEFENCE)->textureRefName);
			m_data->ents.Find<Button>("E_aAtkBtn")->GetSpriteComponent()->GetSprite().setTexture(basicAttTex);
			m_data->ents.Find<Button>("E_aDefBtn")->GetSpriteComponent()->GetSprite().setTexture(basicDefTex);
		}
	}

	/*
	void TutorialScene::CheckForDeaths()
	{
		// the golem died ;)
		if (m_frostGolem->GetHealth() <= 0)
		{
			DisableUIButtons();
			if (m_frostGolem->GetSMComponent()->CurrentState() == "Idle")
			{
				for (auto uiComp : m_allUIcomps)
				{
					uiComp->GetSprite().setColor(sf::Color(
						uiComp->GetSprite().getColor().r,
						uiComp->GetSprite().getColor().g,
						uiComp->GetSprite().getColor().b,
						uiComp->GetSprite().getColor().a - 1
					));

					// if the last UI component has faded out -> go to WON status resolving
					if (m_allUIcomps.at(m_allUIcomps.size() - 1)->GetSprite().getColor().a <= 0)
						m_status = BATTLE_STATUS::WON;
				}
			}
		}

		// count how many heroes died (if any)
		if (m_heroOnTurn != nullptr && m_heroOnTurn->GetHealth() <= 0)
		{
			if (m_hDeathCount < m_activeHeroes.size())
			{
				m_hDeathCount++;
			}
			else
			{
				DisableUIButtons();
				if (m_frostGolem->GetSMComponent()->CurrentState() == "Idle")
				{
					for (auto uiComp : m_allUIcomps)
					{
						uiComp->GetSprite().setColor(sf::Color(
							uiComp->GetSprite().getColor().r,
							uiComp->GetSprite().getColor().g,
							uiComp->GetSprite().getColor().b,
							uiComp->GetSprite().getColor().a - 1
						));

						// if the last UI component has faded out -> go to LOST status resolving
						if (m_allUIcomps.at(m_allUIcomps.size() - 1)->GetSprite().getColor().a <= 0)
							m_status = BATTLE_STATUS::LOST;
					}
				}
			}
		}
	}
	*/

	void TutorialScene::CheckForBattleOutcome()
	{
		// Initialize outcome state(screen)
		SM::StateRef outcomeState;
		switch (m_status)
		{
			case BATTLE_STATUS::LOST:
				// Load lose screen
				outcomeState = std::make_unique<MapScene>(MapScene(m_data));
				m_data->machine.AddState(std::move(outcomeState), true);
				break;
			case BATTLE_STATUS::WON:
				m_data->gm.gold += 100;
				m_data->gm.healthPot += 1;
				m_data->gm.manaPot += 1;
				// Load win screen
				outcomeState = std::make_unique<MapScene>(MapScene(m_data));
				m_data->machine.AddState(std::move(outcomeState), true);
				break;
			default:
			case BATTLE_STATUS::PLAYING:
				break;
		}
	}

	void TutorialScene::NextTurn()
	{
		chosen = false;
		do
		{
			std::cout << m_hTurnCount << std::endl;
			if (m_hTurnCount == 0) { }
			else
			{
				// select the hero to be on turn
				m_heroOnTurn = m_activeHeroes[m_hTurnCount - 1];
				if (!m_heroOnTurn || m_heroOnTurn->GetHealth() <= 0)
				{
					std::cout << "This hero is dead.\n";
				}
				else if (m_heroOnTurn->GetStatusComponent()->GetEffect(EFFECT_TYPE::STUN) != nullptr 
					&& m_heroOnTurn->GetStatusComponent()->GetEffect(EFFECT_TYPE::STUN)->active)
				{
					// unfade hero on turn
					m_heroOnTurn->GetSpriteComponent()->GetSprite().setColor(sf::Color(255, 255, 255, 255));
					for (auto effect : m_heroOnTurn->GetStatusComponent()->GetEffects())
						effect.second->active = false;	
				}
				else
				{
					// fade the rest of the heroes in the party
					for (auto hero : m_activeHeroes)
					{
						if (hero->className() != m_heroOnTurn->className())
							hero->GetSpriteComponent()->GetSprite().setColor(sf::Color(255, 255, 255, 100));
					}
					// unfade hero on turn
					m_heroOnTurn->GetSpriteComponent()->GetSprite().setColor(sf::Color(255, 255, 255, 255));
					// choose this hero
					chosen = true;
					// Enable UI
					EnableUIButtons();
				}
				m_hTurnCount--;
			}
		} while (m_hTurnCount - 1 >= 0 && !chosen);
	}

	// TODO:
	void TutorialScene::Evaluate()
	{

	}
	
	/*
	void TutorialScene::HandleHeroActions(const sf::Vector2f& t_initPos)
	{
		auto atkBtnBtn = m_data->ents.Find<Button>("E_aAtkBtn")->GetClickableComponent();
		auto skill1BtnBtn = m_data->ents.Find<Button>("E_aSkill1Btn")->GetClickableComponent();
		auto skill2BtnBtn = m_data->ents.Find<Button>("E_aSkill2Btn")->GetClickableComponent();
		
		// move right if attacking
		if (heroStepIn && m_heroOnTurn->GetPosition().x <= SCREEN_WIDTH / 3.5f)
		{
			DisableUIButtons();
			m_heroOnTurn->Move(sf::Vector2f(10.0f, 0.0f));
		}

		// stop moving when destination is reached
		if (m_heroOnTurn->GetPosition().x >= SCREEN_WIDTH / 3.5f)
		{
			// cannot step in
			heroStepIn = false;

			// [ATTACK]
			if (atkBtnBtn->CanResolve())
			{
				std::cout << "Hero attacking!\n";
				m_heroOnTurn->ExecuteSkill(m_heroOnTurn->GetSkillComponent()->FindSkill(SKILL_NAME::BASIC_ATTACK), m_frostGolem);
				// reset button's resolve
				atkBtnBtn->SetResolve(false);
			}

			// [SKILL 1]
			if (skill1BtnBtn->CanResolve())
			{
				std::cout << "Hero used Skill 1!\n";
				m_heroOnTurn->ExecuteSkill(m_heroOnTurn->GetSkillComponent()->FindSkill(SKILL_NAME::SPECIAL_SKILL_1), m_frostGolem);
				// reset button's resolve
				skill1BtnBtn->SetResolve(false);
			}

			// [SKILL 2]
			if (skill2BtnBtn->CanResolve())
			{
				std::cout << "Hero used Skill 2!\n";
				m_heroOnTurn->ExecuteSkill(m_heroOnTurn->GetSkillComponent()->FindSkill(SKILL_NAME::SPECIAL_SKILL_2), m_frostGolem);
				// reset button's resolve
				skill2BtnBtn->SetResolve(false);
			}

			heroReturn = true;
		}

		// check if the action has been executed
		if (heroReturn && m_heroOnTurn->GetPosition().x >= t_initPos.x)
		{
			m_heroOnTurn->Move(sf::Vector2f(-10.0f, 0.0f));
		}

		if (m_heroOnTurn->GetPosition().x <= t_initPos.x && heroReturn)
		{
			// next hero turn
			heroReturn = false;
			std::cout << "I HAVE RETURNED!\n";
			NextTurn();
		}
	}

	*/

} }