#include "PauseMenu.hpp"
#include "SettingsScene.hpp"
#include "MainMenu.hpp"

#include <sstream>
#include <iostream>

#include <Engine/ECM/Components/TextComponent.hpp>
#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/ClickableComponent.hpp>
#include "../Entities/Button.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	PauseMenuScene::PauseMenuScene(GameDataRef t_data)
		: m_data(t_data)
	{ }

	void PauseMenuScene::Init()
	{
		// Background
		auto bg = std::make_shared<Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_PauseBGSprite");
		// define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SplashBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 155));
		// set properties
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		// Title
		auto title = std::make_shared<Entity>();
		auto titleComp = title->AddComponent<TextComponent>("C_PauseMenuText");
		titleComp->GetText().setFont(m_data->assets.GetFont("Font_Pixel"));
		titleComp->GetText().setCharacterSize(66);
		titleComp->GetText().setString("PAUSE MENU");
		titleComp->GetText().setColor(sf::Color(255, 255, 255, 200));
		title->SetPosition(sf::Vector2f(
			(SCREEN_WIDTH - titleComp->GetText().getGlobalBounds().width) * .5f,
			(SCREEN_HEIGHT - titleComp->GetText().getGlobalBounds().height) * 0.1f));
		title->SetAlive(true);
		title->SetVisible(true);

		// Save Button
		auto savebtn = std::make_shared<Button>();
		auto saveBtnSprite = savebtn->GetSpriteComponent();
		//define bg sprite
		saveBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		saveBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		savebtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - saveBtnSprite->GetSprite().getGlobalBounds().width) * 0.45f,
			(SCREEN_HEIGHT - saveBtnSprite->GetSprite().getGlobalBounds().height) * 0.3f));
		saveBtnSprite->GetSprite().scale(1.5f, 1.0f);
		savebtn->SetVisible(true);
		savebtn->SetAlive(true);
		//text
		auto saveBtnText = savebtn->GetTextComponent();
		saveBtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		saveBtnText->GetText().setString("SAVE GAME");
		saveBtnText->GetText().setStyle(sf::Text::Bold);
		saveBtnText->GetText().setCharacterSize(24);
		//click component
		savebtn->Init();
		//center text
		saveBtnText->GetText().setPosition(savebtn->GetPosition().x + (savebtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5f) - saveBtnText->GetText().getGlobalBounds().width * 0.5f,
			savebtn->GetPosition().y + (savebtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - saveBtnText->GetText().getGlobalBounds().height * 0.6f);

		// Main Menu Button
		auto menuBtn = std::make_shared<Button>();
		auto menuBtnSprite = menuBtn->GetSpriteComponent();
		//define bg sprite
		menuBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		menuBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		menuBtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - menuBtnSprite->GetSprite().getGlobalBounds().width) * 0.45f,
			(SCREEN_HEIGHT - menuBtnSprite->GetSprite().getGlobalBounds().height) * 0.5f));
		menuBtnSprite->GetSprite().scale(1.5f, 1.0f);
		menuBtn->SetVisible(true);
		menuBtn->SetAlive(true);
		//text
		auto menuBtnText = menuBtn->GetTextComponent();
		menuBtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		menuBtnText->GetText().setString("EXIT TO MENU");
		menuBtnText->GetText().setStyle(sf::Text::Bold);
		menuBtnText->GetText().setCharacterSize(24);
		//click component
		menuBtn->Init();
		//center text
		menuBtnText->GetText().setPosition(menuBtn->GetPosition().x + (menuBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5f) - menuBtnText->GetText().getGlobalBounds().width * 0.5f,
			menuBtn->GetPosition().y + (menuBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - menuBtnText->GetText().getGlobalBounds().height * 0.6f);

		//Settings Button
		auto setbtn = std::make_shared<Button>();
		auto setBtnSprite = setbtn->GetSpriteComponent();
		//define bg sprite
		setBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		setBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		setbtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - setBtnSprite->GetSprite().getGlobalBounds().width) * 0.45f,
			(SCREEN_HEIGHT - setBtnSprite->GetSprite().getGlobalBounds().height) * 0.7f));
		setBtnSprite->GetSprite().scale(1.5f, 1.0f);
		//text
		auto setText = setbtn->GetTextComponent();
		setText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		setText->GetText().setString("SETTINGS");
		setText->GetText().setStyle(sf::Text::Bold);
		setText->GetText().setCharacterSize(24);
		//properties
		setbtn->SetVisible(true);
		setbtn->SetAlive(true);
		setbtn->Init();
		//center text
		setText->GetText().setPosition(setbtn->GetPosition().x + (setbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5f) - setText->GetText().getGlobalBounds().width * 0.5f,
			setbtn->GetPosition().y + (setbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - setText->GetText().getGlobalBounds().height * 0.6f);

		// Return Button
		auto qbtn = std::make_shared<Button>();
		auto qbtnSprite = qbtn->GetSpriteComponent();
		//define bg sprite
		qbtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		qbtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		qbtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - qbtnSprite->GetSprite().getGlobalBounds().width) * 0.45f,
			(SCREEN_HEIGHT - qbtnSprite->GetSprite().getGlobalBounds().height) * 0.9f));
		qbtnSprite->GetSprite().scale(1.5f, 1.0f);
		//text
		auto qText = qbtn->GetTextComponent();
		qText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		qText->GetText().setString("GO BACK");
		qText->GetText().setStyle(sf::Text::Bold);
		qText->GetText().setCharacterSize(24);
		//properties
		qbtn->SetVisible(true);
		qbtn->SetAlive(true);
		qbtn->Init();
		//center text
		qText->GetText().setPosition(qbtn->GetPosition().x + (qbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5f) - qText->GetText().getGlobalBounds().width * 0.5f,
			qbtn->GetPosition().y + (qbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - qText->GetText().getGlobalBounds().height * 0.6f);

		AddEntity("E_zPauseMenuBG", bg);
		AddEntity("E_aPauseMenuTitle", title);
		AddEntity("E_xPauseSaveBtn", savebtn);
		AddEntity("E_xPauseMainMenuBtn", menuBtn);
		AddEntity("E_xPauseSettingsBtn", setbtn);
		AddEntity("E_xPauseReturnBtn", qbtn);
	}

	void PauseMenuScene::HandleInput()
	{
		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView(event.size.width, event.size.height);

			// Resume to the last Game Screen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_data->machine.RemoveState();

			auto saveComp = m_data->ents.Find<Button>("E_xPauseSaveBtn")->GetSpriteComponent();
			auto saveBtn = m_data->ents.Find<Button>("E_xPauseSaveBtn")->GetClickableComponent();
			if (saveBtn->IsClickable() && m_data->input.isClicked(saveComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				saveBtn->SetClicked(true);
			}

			auto menuComp = m_data->ents.Find<Button>("E_xPauseMainMenuBtn")->GetSpriteComponent();
			auto menuBtn = m_data->ents.Find<Button>("E_xPauseMainMenuBtn")->GetClickableComponent();
			if (menuBtn->IsClickable() && m_data->input.isClicked(menuComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				menuBtn->SetClicked(true);
			}

			auto setComp = m_data->ents.Find<Button>("E_xPauseSettingsBtn")->GetSpriteComponent();
			auto setBtn = m_data->ents.Find<Button>("E_xPauseSettingsBtn")->GetClickableComponent();
			if (m_data->input.isClicked(setComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				std::cout << "button has been clicked" << std::endl;
				setBtn->SetClicked(true);
			}

			auto returnComp = m_data->ents.Find<Button>("E_xPauseReturnBtn")->GetSpriteComponent();
			auto returnBtn = m_data->ents.Find<Button>("E_xPauseReturnBtn")->GetClickableComponent();
			if (returnBtn->IsClickable() && m_data->input.isClicked(returnComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				returnBtn->SetClicked(true);
			}
		}
	}

	void PauseMenuScene::Update(float t_delatTime)
	{
		auto saveBtn = m_data->ents.Find<Button>("E_xPauseSaveBtn")->GetClickableComponent();
		if (saveBtn->CanResolve())
		{
			saveBtn->SetResolve(false);

			// Save the current game data
			m_data->saveData.Save<int>({
				// heroes stats
				/*
				// knight
				m_data->gm.hKnight->GetHealth(),
				m_data->gm.hKnight->GetMaxHealth(),
				m_data->gm.hKnight->GetMana(),
				m_data->gm.hKnight->GetMaxMana(),
				m_data->gm.hKnight->GetArmour(),
				m_data->gm.hKnight->GetDodge(),
				m_data->gm.hKnight->GetCrit(),
				m_data->gm.hKnight->GetDmg(),
				// bard
				m_data->gm.hBard->GetHealth(),
				m_data->gm.hBard->GetMaxHealth(),
				m_data->gm.hBard->GetMana(),
				m_data->gm.hBard->GetMaxMana(),
				m_data->gm.hBard->GetArmour(),
				m_data->gm.hBard->GetDodge(),
				m_data->gm.hBard->GetCrit(),
				m_data->gm.hBard->GetDmg(),
				// rogue
				m_data->gm.hRogue->GetHealth(),
				m_data->gm.hRogue->GetMaxHealth(),
				m_data->gm.hRogue->GetMana(),
				m_data->gm.hRogue->GetMaxMana(),
				m_data->gm.hRogue->GetArmour(),
				m_data->gm.hRogue->GetDodge(),
				m_data->gm.hRogue->GetCrit(),
				m_data->gm.hRogue->GetDmg(),
				// sorceress
				m_data->gm.hSorceress->GetHealth(),
				m_data->gm.hSorceress->GetMaxHealth(),
				m_data->gm.hSorceress->GetMana(),
				m_data->gm.hSorceress->GetMaxMana(),
				m_data->gm.hSorceress->GetArmour(),
				m_data->gm.hSorceress->GetDodge(),
				m_data->gm.hSorceress->GetCrit(),
				m_data->gm.hSorceress->GetDmg(),
				// buidlings stats
				// blacksmith
				m_data->gm.blacksmith->GetLevel(),
				// infirmary
				m_data->gm.infirmary->GetLevel(),
				// library
				m_data->gm.library->GetLevel(),
				// inn
				m_data->gm.inn->GetLevel(),
				// general store
				m_data->gm.store->GetLevel(),
				// resources
				// potions
				m_data->gm.healthPot,
				m_data->gm.manaPot,
				// money
				m_data->gm.gold,
				// unlocked encounters
				m_data->gm.unlockedEncounters
				*/
				// buidlings stats
				// blacksmith
				m_data->gm.blacksmith->GetLevel(),
				// infirmary
				m_data->gm.infirmary->GetLevel(),
				// library
				m_data->gm.library->GetLevel(),
				// inn
				m_data->gm.inn->GetLevel(),
				// general store
				m_data->gm.store->GetLevel()
			}, Utils::DATA_TYPE::GAME_DATA);

			// resume to game scene
			m_data->machine.RemoveState();
		}

		auto menuBtn = m_data->ents.Find<Button>("E_xPauseMainMenuBtn")->GetClickableComponent();
		if (menuBtn->CanResolve())
		{
			menuBtn->SetResolve(false);

			// change scene to Main Menu
			auto SettingsScreen = std::make_unique<MainMenuScene>(MainMenuScene(m_data));
			m_data->machine.AddState(std::move(SettingsScreen));

			// resume to game scene
			m_data->machine.RemoveState();
		}

		auto setBtn = m_data->ents.Find<Button>("E_xPauseSettingsBtn")->GetClickableComponent();
		if (setBtn->CanResolve())
		{
			setBtn->SetResolve(false);
			// change scene to Settings
			auto SettingsScreen = std::make_unique<SettingsScene>(SettingsScene(m_data));
			m_data->machine.AddState(std::move(SettingsScreen), false);
		}

		auto returnBtn = m_data->ents.Find<Button>("E_xPauseReturnBtn")->GetClickableComponent();
		if (returnBtn->CanResolve())
		{
			returnBtn->SetResolve(false);
			// resume to game scene
			m_data->machine.RemoveState();
		}

		m_data->ents.Update(m_entities, t_delatTime);
	}

	void PauseMenuScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void PauseMenuScene::AddEntity(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}

}