#include "MainMenu.hpp"
#include "StoryIntro.hpp"
#include "Encounters/Tutorial.hpp"
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
	{ }

	void MainMenuScene::Init()
	{
		// Load resources
		m_data->assets.LoadTexture("Tex_MainBG", SPLASH_SCENE_BACKGROUND);
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

		// Title
		auto title = std::make_shared<Entity>();
		auto titleComp = title->AddComponent<TextComponent>("C_MainMenuText");
		titleComp->GetText().setFont(m_data->assets.GetFont("Font_Pixel"));
		titleComp->GetText().setCharacterSize(66);
		titleComp->GetText().setString("HEROES JOURNEY");
		titleComp->GetText().setColor(sf::Color(255, 255, 255, 155));
		title->SetPosition(sf::Vector2f(
			(SCREEN_WIDTH - titleComp->GetText().getGlobalBounds().width) * .5f,
			(SCREEN_HEIGHT - titleComp->GetText().getGlobalBounds().height) * 0.1f));
		title->SetAlive(true);
		title->SetVisible(true);

		//Start Button
		auto mbtn = std::make_shared<Button>();
		auto mbtnSprite = mbtn->GetSpriteComponent();
			//define bg sprite
		mbtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		mbtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		mbtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - mbtnSprite->GetSprite().getGlobalBounds().width) * 0.45f,
			(SCREEN_HEIGHT - mbtnSprite->GetSprite().getGlobalBounds().height) * 0.3f));
		mbtnSprite->GetSprite().scale(1.5f, 1.0f);
		mbtn->SetVisible(true);
		mbtn->SetAlive(true);
		//text
		auto mbtnText = mbtn->GetTextComponent();
		mbtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		mbtnText->GetText().setString("NEW GAME");
		mbtnText->GetText().setStyle(sf::Text::Bold);
		mbtnText->GetText().setCharacterSize(24);
		//click component
		mbtn->Init();
		//center text
		mbtnText->GetText().setPosition(mbtn->GetPosition().x +(mbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5f) - mbtnText->GetText().getGlobalBounds().width * 0.5f,
			mbtn->GetPosition().y + (mbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - mbtnText->GetText().getGlobalBounds().height * 0.6f);

		// Load Button
		auto lbtn = std::make_shared<Button>();
		auto lbtnSprite = lbtn->GetSpriteComponent();
		//define bg sprite
		lbtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		lbtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		lbtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - lbtnSprite->GetSprite().getGlobalBounds().width) * 0.45f,
			(SCREEN_HEIGHT - lbtnSprite->GetSprite().getGlobalBounds().height) * 0.5f));
		lbtnSprite->GetSprite().scale(1.5f, 1.0f);
		lbtn->SetVisible(true);
		lbtn->SetAlive(true);
		//text
		auto lbtnText = lbtn->GetTextComponent();
		lbtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		lbtnText->GetText().setString("CONTINUE...");
		lbtnText->GetText().setStyle(sf::Text::Bold);
		lbtnText->GetText().setCharacterSize(24);
		//click component
		lbtn->Init();
		//center text
		lbtnText->GetText().setPosition(lbtn->GetPosition().x + (lbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5f) - lbtnText->GetText().getGlobalBounds().width * 0.5f,
			lbtn->GetPosition().y + (lbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - lbtnText->GetText().getGlobalBounds().height * 0.6f);

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
		setText->GetText().setString("< SETTINGS />");
		setText->GetText().setStyle(sf::Text::Bold);
		setText->GetText().scale(0.75f, 0.75f);
		setText->GetText().setCharacterSize(24);
		//properties
		setbtn->SetVisible(true);
		setbtn->SetAlive(true);
		setbtn->Init();
		//center text
		setText->GetText().setPosition(setbtn->GetPosition().x + (setbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5f) - setText->GetText().getGlobalBounds().width * 0.5f,
			setbtn->GetPosition().y + (setbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - setText->GetText().getGlobalBounds().height * 0.6f);


		//Quit Button
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
		qText->GetText().setString("EXIT GAME");
		qText->GetText().setStyle(sf::Text::Bold);
		qText->GetText().setCharacterSize(24);
		//properties
		qbtn->SetVisible(true);
		qbtn->SetAlive(true);
		qbtn->Init();
		//center text
		qText->GetText().setPosition(qbtn->GetPosition().x + (qbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5f) - qText->GetText().getGlobalBounds().width * 0.5f,
			qbtn->GetPosition().y + (qbtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - qText->GetText().getGlobalBounds().height * 0.6f);

		//add to local ents map
		AddEntity("E_zMainBG", bg);
		AddEntity("E_aMainMenuTitle", title);
		AddEntity("E_xStartBtn", mbtn);
		AddEntity("E_xLoadBtn", lbtn);
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

			auto startComp = m_data->ents.Find<Button>("E_xStartBtn")->GetSpriteComponent();
			auto startBtn = m_data->ents.Find<Button>("E_xStartBtn")->GetClickableComponent();
			if (m_data->input.isClicked(startComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				startBtn->SetClicked(true);
			}

			auto loadComp = m_data->ents.Find<Button>("E_xLoadBtn")->GetSpriteComponent();
			auto loadBtn = m_data->ents.Find<Button>("E_xLoadBtn")->GetClickableComponent();
			if (m_data->input.isClicked(loadComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				loadBtn->SetClicked(true);
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
		auto startBtn = m_data->ents.Find<Button>("E_xStartBtn")->GetClickableComponent();
		if (startBtn->CanResolve())
		{
			startBtn->SetResolve(false);
			// change scene to Story intro
			auto storyIntro = std::make_unique<Encounters::TutorialScene>(Encounters::TutorialScene(m_data));
			m_data->machine.AddState(std::move(storyIntro));
		}

		auto loadBtn = m_data->ents.Find<Button>("E_xLoadBtn")->GetClickableComponent();
		if (loadBtn->CanResolve())
		{
			loadBtn->SetResolve(false);
			// change scene to Story intro
			auto storyIntro = std::make_unique<Encounters::TutorialScene>(Encounters::TutorialScene(m_data));
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