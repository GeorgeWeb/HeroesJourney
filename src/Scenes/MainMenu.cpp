#include "MainMenu.hpp"
#include "StoryIntro.hpp"
#include "../DEFINITIONS.hpp"
#include "MapScene.hpp"
#include "SettingsScene.hpp"
#include <Engine/ECM/Components/ClickableComponent.hpp>
#include "../Entities/Button.hpp"


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
		InitSceneView();
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
		auto mbtn = std::make_shared<Button>();
		auto mbtnSprite = mbtn->GetSpriteComponent();
			//define bg sprite
		mbtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		mbtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		mbtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - mbtnSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(SCREEN_HEIGHT - mbtnSprite->GetSprite().getGlobalBounds().height) * 0.4f));
		//mbtnSprite->GetSprite().scale(0.75f, 1.0f);
		mbtn->SetVisible(true);
		mbtn->SetAlive(true);
		//text
		auto mbtnText = mbtn->GetTextComponent();
		mbtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		mbtnText->GetText().setString("PLAY");
		//mbtnText->GetText().scale(0.75f, 0.75f);
		mbtnText->GetText().setCharacterSize(24);
		//click component
		mbtn->Init();
		//center text
		mbtnText->GetText().setPosition(mbtn->GetPosition().x +(mbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5) - mbtnText->GetText().getGlobalBounds().width * 0.5,
			mbtn->GetPosition().y + (mbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.5) - mbtnText->GetText().getGlobalBounds().height * 0.5 );

		//Settings Button
		auto setbtn = std::make_shared<Button>();
		auto setBtnSprite = setbtn->GetSpriteComponent();
		//define bg sprite
		setBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		setBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		setbtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - setBtnSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(SCREEN_HEIGHT - setBtnSprite->GetSprite().getGlobalBounds().height) * 0.6f));
		//setBtnSprite->GetSprite().scale(0.75f, 1.0f);
		//text
		auto setText = setbtn->GetTextComponent();
		setText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		setText->GetText().setString("SETTINGS");
		setText->GetText().scale(0.75f, 0.75f);
		setText->GetText().setCharacterSize(24);
		//properties
		setbtn->SetVisible(true);
		setbtn->SetAlive(true);
		setbtn->Init();
		//center text
		setText->GetText().setPosition(setbtn->GetPosition().x + (setbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5) - setText->GetText().getGlobalBounds().width * 0.5,
			setbtn->GetPosition().y + (setbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.5) - setText->GetText().getGlobalBounds().height * 0.5);


		//Quit Button
		auto qbtn = std::make_shared<Button>();
		auto qbtnSprite = qbtn->GetSpriteComponent();
		//define bg sprite
		qbtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		qbtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		qbtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - qbtnSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(SCREEN_HEIGHT - qbtnSprite->GetSprite().getGlobalBounds().height) * 0.8f));
		//qbtnSprite->GetSprite().scale(0.75f, 1.0f);
		//text
		auto qText = qbtn->GetTextComponent();
		qText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		qText->GetText().setString("QUIT");
		//qText->GetText().scale(0.75f, 0.75f);
		qText->GetText().setCharacterSize(24);
		//properties
		qbtn->SetVisible(true);
		qbtn->SetAlive(true);
		qbtn->Init();
		//center text
		qText->GetText().setPosition(qbtn->GetPosition().x + (qbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5) - qText->GetText().getGlobalBounds().width * 0.5,
			qbtn->GetPosition().y + (qbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.5) - qText->GetText().getGlobalBounds().height * 0.5);

		//add to local ents map
		AddEntity("E_zMainBG", bg);
		AddEntity("E_xBtn", mbtn);
		AddEntity("E_xSetBtn", setbtn);
		AddEntity("E_xQBtn", qbtn);
	}

	void MainMenuScene::HandleInput()
	{
		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView(event.size.width, event.size.height);

			//check if start is clicked
			auto startComp = m_data->ents.Find<Button>("E_xBtn")->GetSpriteComponent();
			auto startBtn = m_data->ents.Find<Button>("E_xBtn")->GetClickableComponent();
			if (m_data->input.isClicked(startComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				startBtn->SetClicked(true);
			}


			auto setComp = m_data->ents.Find<Button>("E_xSetBtn")->GetSpriteComponent();
			auto setBtn = m_data->ents.Find<Button>("E_xSetBtn")->GetClickableComponent();
			if (m_data->input.isClicked(setComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				std::cout << "button has been clicked" << std::endl;
				setBtn->SetClicked(true);
			}

			auto quitComp = m_data->ents.Find<Button>("E_xQBtn")->GetSpriteComponent();
			auto quitBtn = m_data->ents.Find<Button>("E_xQBtn")->GetClickableComponent();
			if (m_data->input.isClicked(quitComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				quitBtn->SetClicked(true);
			}
		}
	}

	void MainMenuScene::Update(float t_delatTime)
	{
		m_data->ents.Update(m_entities, t_delatTime);
		auto startBtn = m_data->ents.Find<Button>("E_xBtn")->GetClickableComponent();
		if (startBtn->CanResolve())
		{
			startBtn->SetResolve(false);
			// change scene to Story intro
			auto storyIntro = std::make_unique<StoryIntroScene>(StoryIntroScene(m_data));
			m_data->machine.AddState(std::move(storyIntro));
		}

		auto setBtn = m_data->ents.Find<Button>("E_xSetBtn")->GetClickableComponent();
		if (setBtn->CanResolve())
		{
			setBtn->SetResolve(false);
			// change scene to Settings
			auto SettingsScreen = std::make_unique<SettingsScene>(SettingsScene(m_data));
			m_data->machine.AddState(std::move(SettingsScreen), false);
		}

		auto quitBtn = m_data->ents.Find<Button>("E_xQBtn")->GetClickableComponent();
		if (quitBtn->CanResolve())
		{
			quitBtn->SetResolve(false);
			// exit game (window)
			Engine2D::GetWin().close();
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