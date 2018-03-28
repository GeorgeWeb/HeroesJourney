#include "MainMenu.hpp"
#include "StoryIntro.hpp"
#include "../DEFINITIONS.hpp"
#include "MapScene.hpp"
#include "SettingsScene.hpp"
#include <Engine/ECM/Components/ClickableComponent.hpp>


namespace HJ {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;
	
	MainMenuScene::MainMenuScene(GameDataRef t_data)
		: m_data(t_data)
	{
		// Will not be used for more initialization
	}

	void MainMenuScene::Init()
	{
		// Load resources
		m_data->assets.LoadTexture("Tex_MainBG", MAINMENU_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_StartBtn", MAINMENU_STARTGAME_BUTTON);
		m_data->assets.LoadTexture("Tex_SettingsBtn", MAINMENU_SETTINGS_BUTTON);
		m_data->assets.LoadTexture("Tex_QuitBtn", MAINMENU_QUITGAME_BUTTON);

		//Background
		auto bg = std::make_shared<Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_MainBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_MainBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);
		
		//Start Button
		auto mbtn = std::make_shared<ECM::Entity>();
		auto mbtnSprite = mbtn->AddComponent<SpriteComponent>("C_BtnSprite");
		//define bg sprite
		mbtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StartBtn"));
		mbtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		mbtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - mbtnSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(SCREEN_HEIGHT - mbtnSprite->GetSprite().getGlobalBounds().height) * 0.4f));
		mbtn->SetVisible(true);
		mbtn->SetAlive(true);
		//click component
		auto startBtn = mbtn->AddComponent<ClickableComponent>("C_MBtnBtn");
		startBtn->SetSpriteTarget(mbtnSprite.get());
		

		//Settings Button
		auto setbtn = std::make_shared<ECM::Entity>();
		auto setBtnSprite = setbtn->AddComponent<SpriteComponent>("C_SetBtnSprite");
		//define bg sprite
		setBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SettingsBtn"));
		setBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		setbtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - setBtnSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(SCREEN_HEIGHT - setBtnSprite->GetSprite().getGlobalBounds().height) * 0.6f));
		setbtn->SetVisible(true);
		setbtn->SetAlive(true);
		auto setClick = setbtn->AddComponent<ClickableComponent>("C_SetBtnBtn");
		setClick->SetSpriteTarget(setBtnSprite.get());
		

		//Quit Button
		auto qbtn = std::make_shared<ECM::Entity>();
		auto qbtnSprite = qbtn->AddComponent<SpriteComponent>("C_QuitBtnSprite");
		//define bg sprite
		qbtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_QuitBtn"));
		qbtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		qbtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - qbtnSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(SCREEN_HEIGHT - qbtnSprite->GetSprite().getGlobalBounds().height) * 0.8f));
		qbtn->SetVisible(true);
		qbtn->SetAlive(true);
		auto qClick = qbtn->AddComponent<ClickableComponent>("C_QBtn");
		qClick->SetSpriteTarget(qbtnSprite.get());

		//add to local ents map
		AddEntity("E_zMainBG", bg);
		AddEntity("E_xBtn", mbtn);
		AddEntity("E_xSetBtn", setbtn);
		AddEntity("E_xQBtn", qbtn);
	}

	void MainMenuScene::HandleInput()
	{
		sf::Event event;
		while (Renderer::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Renderer::GetWin().close();
			//check if start is clicked
			auto startComp = m_data->ents.Find<Entity>("E_xBtn")->GetComponent<SpriteComponent>("C_BtnSprite");
			auto startBtn = m_data->ents.Find<Entity>("E_xBtn")->GetComponent<ClickableComponent>("C_MBtnBtn");
			if (m_data->input.isClicked(startComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				startBtn->SetClicked(true);
			}


			auto setComp = m_data->ents.Find<Entity>("E_xSetBtn")->GetComponent<SpriteComponent>("C_SetBtnSprite");
			auto setBtn = m_data->ents.Find<Entity>("E_xSetBtn")->GetComponent<ClickableComponent>("C_SetBtnBtn");
			if (m_data->input.isClicked(setComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				std::cout << "button has been clicked" << std::endl;
				setBtn->SetClicked(true);
			}

			auto quitComp = m_data->ents.Find<Entity>("E_xQBtn")->GetComponent<SpriteComponent>("C_QuitBtnSprite");
			auto quitBtn = m_data->ents.Find<Entity>("E_xQBtn")->GetComponent<ClickableComponent>("C_QBtn");
			if (m_data->input.isClicked(quitComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				quitBtn->SetClicked(true);
			}
		}
	}

	void MainMenuScene::Update(float t_delatTime)
	{
		m_data->ents.Update(m_entities, t_delatTime);
		auto startBtn = m_data->ents.Find<Entity>("E_xBtn")->GetComponent<ClickableComponent>("C_MBtnBtn");
		if (startBtn->CanResolve())
		{
			auto storyIntro = std::make_unique<StoryIntroScene>(StoryIntroScene(m_data));
			m_data->machine.AddState(std::move(storyIntro));

			startBtn->SetResolve(false);
		}

		auto setBtn = m_data->ents.Find<Entity>("E_xSetBtn")->GetComponent<ClickableComponent>("C_SetBtnBtn");
		if (setBtn->CanResolve())
		{
			std::cout << "button responds!" << std::endl;
			auto SettingsScreen = std::make_unique<SettingsScene>(SettingsScene(m_data));
			m_data->machine.AddState(std::move(SettingsScreen), false);

			setBtn->SetResolve(false);
			std::cout << "button set to false" << std::endl;
		}

		auto quitBtn = m_data->ents.Find<Entity>("E_xQBtn")->GetComponent<ClickableComponent>("C_QBtn");
		if (quitBtn->CanResolve())
		{
			Renderer::GetWin().close();
			
			quitBtn->SetResolve(false);
		}

	}

	void MainMenuScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void MainMenuScene::AddEntity(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}
}