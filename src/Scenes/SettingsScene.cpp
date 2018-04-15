#include "SettingsScene.hpp"
#include "../DEFINITIONS.hpp"
#include "MainMenu.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	//engine/game compoment namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	SettingsScene::SettingsScene(GameDataRef t_data)
		: m_data(t_data)
	{ }

	void SettingsScene::Init()
	{
		//load resources
		m_data->assets.LoadTexture("Tex_SettingsBG", SETTING_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_SelectBtn", SETTING_SCENE_SELECTEDBTN);
		m_data->assets.LoadTexture("Tex_UnSelectBtn", SETTING_SCENE_UNSELECTEDBTN);

		//background
		auto bg = std::make_shared<Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_SettingsBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SettingsBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		bg->SetPosition(sf::Vector2f(((SCREEN_WIDTH - bgSprite->GetSprite().getGlobalBounds().width) * 0.5f), 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		//Unchecked buttons1
		auto uncheck1 = std::make_shared<Entity>();
		auto uncheck1Sprite = uncheck1->AddComponent<SpriteComponent>("C_UnCheck1Sprite");
		//define sprite
		uncheck1Sprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		uncheck1Sprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		uncheck1->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.5 - bgSprite->GetSprite().getGlobalBounds().width * 0.45, bgSprite->GetSprite().getGlobalBounds().height * 0.1));
		uncheck1->SetVisible(true);
		uncheck1->SetAlive(true);
		auto uncheck1Btn = uncheck1->AddComponent<ClickableComponent>("C_UnCheck1Btn"); 
		uncheck1Btn->SetSpriteTarget(uncheck1Sprite.get());

		//Unchecked buttons2
		auto uncheck2 = std::make_shared<Entity>();
		auto uncheck2Sprite = uncheck2->AddComponent<SpriteComponent>("C_UnCheck2Sprite");
		//define sprite
		uncheck2Sprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		uncheck2Sprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		uncheck2->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.5f - bgSprite->GetSprite().getGlobalBounds().width * 0.25, bgSprite->GetSprite().getGlobalBounds().height * 0.1f));
		uncheck2->SetVisible(true);
		uncheck2->SetAlive(true);
		//clickable component
		auto uncheck2Btn = uncheck2->AddComponent<ClickableComponent>("C_UnCheck2Btn");
		uncheck2Btn->SetSpriteTarget(uncheck2Sprite.get());

		//Unchecked buttons3
		auto uncheck3 = std::make_shared<Entity>();
		auto uncheck3Sprite = uncheck3->AddComponent<SpriteComponent>("C_UnCheck3Sprite");
		//define sprite
		uncheck3Sprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		uncheck3Sprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		uncheck3->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.5f - bgSprite->GetSprite().getGlobalBounds().width * 0.005f, bgSprite->GetSprite().getGlobalBounds().height * 0.1f));
		uncheck3->SetVisible(true);
		uncheck3->SetAlive(true);
		//clickabe component
		auto uncheck3Btn = uncheck3->AddComponent<ClickableComponent>("C_UnCheck3Btn");
		uncheck3Btn->SetSpriteTarget(uncheck3Sprite.get());
		//Unchecked buttons 4
		auto uncheck4 = std::make_shared<Entity>();
		auto uncheck4Sprite = uncheck4->AddComponent<SpriteComponent>("C_UnCheck4Sprite");
		//define sprite
		uncheck4Sprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		uncheck4Sprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		uncheck4->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.5f + bgSprite->GetSprite().getGlobalBounds().width * 0.25f, bgSprite->GetSprite().getGlobalBounds().height * 0.1f));
		uncheck4->SetVisible(true);
		uncheck4->SetAlive(true);
		//clickabe component
		auto uncheck4Btn = uncheck4->AddComponent<ClickableComponent>("C_UnCheck4Btn");
		uncheck4Btn->SetSpriteTarget(uncheck4Sprite.get());

		//Unchecked buttons 5- Fullscreen
		auto uncheck5 = std::make_shared<Entity>();
		auto uncheck5Sprite = uncheck5->AddComponent<SpriteComponent>("C_UnCheck5Sprite");
		//define sprite
		uncheck5Sprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		uncheck5Sprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		uncheck5->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.643f - bgSprite->GetSprite().getGlobalBounds().width * 0.25f, bgSprite->GetSprite().getGlobalBounds().height * 0.273f));
		uncheck5->SetVisible(true);
		uncheck5->SetAlive(true);
		//clickabe component
		auto uncheck5Btn = uncheck5->AddComponent<ClickableComponent>("C_UnCheck5Btn");
		uncheck5Btn->SetSpriteTarget(uncheck5Sprite.get());

		//Save button
		auto save = std::make_shared<Button>();
		auto saveSprite = save->GetSpriteComponent();
		//define sprite
		saveSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		saveSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		save->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.7f - saveSprite->GetSprite().getGlobalBounds().width * 0.5f,
			SCREEN_HEIGHT * 0.925f - saveSprite->GetSprite().getGlobalBounds().height * 0.5f));
		//text
		auto saveText = save->GetTextComponent();
		saveText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		saveText->GetText().setString("SAVE!");
		saveText->GetText().setCharacterSize(26);
		saveText->GetText().setStyle(sf::Text::Bold);
		//properties
		save->SetVisible(true);
		save->SetAlive(true);
		save->Init();
		//center text
		saveText->GetText().setPosition(save->GetPosition().x + (save->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5) - saveText->GetText().getGlobalBounds().width * 0.5,
			save->GetPosition().y + (save->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - saveText->GetText().getGlobalBounds().height * 0.6f);

		//Back button
		auto back = std::make_shared<Button>();
		auto backSprite = back->GetSpriteComponent();
		//define sprite
		backSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		backSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		back->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.525f - backSprite->GetSprite().getGlobalBounds().width * 0.5f,
			SCREEN_HEIGHT * 0.925f - backSprite->GetSprite().getGlobalBounds().height * 0.5f));
		//text
		auto backText = back->GetTextComponent();
		backText->SetFont(m_data->assets.GetFont("Font_Pixel"));
		backText->GetText().setString("CLOSE");
		backText->GetText().setCharacterSize(26);
		backText->GetText().setStyle(sf::Text::Bold);
		//properties
		back->SetVisible(true);
		back->SetAlive(true);
		back->Init();
		//center text
		backText->GetText().setPosition(back->GetPosition().x + (back->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5) - backText->GetText().getGlobalBounds().width * 0.5,
			back->GetPosition().y + (back->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - backText->GetText().getGlobalBounds().height * 0.6f);

		// change Back button
		m_changeBackBtn = std::make_shared<Button>();
		auto changeBackBtnSprite = m_changeBackBtn->GetSpriteComponent();
		//define sprite
		changeBackBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		changeBackBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		changeBackBtnSprite->GetSprite().scale(0.5, 0.5f);
		m_changeBackBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.2625f - changeBackBtnSprite->GetSprite().getGlobalBounds().width * 0.5f,
			SCREEN_HEIGHT * 0.5f - changeBackBtnSprite->GetSprite().getGlobalBounds().height * 0.5f));
		//text
		auto changeBackBtnTxt = m_changeBackBtn->GetTextComponent();
		changeBackBtnTxt->SetFont(m_data->assets.GetFont("Font_Pixel"));
		changeBackBtnTxt->GetText().setString("Back");
		changeBackBtnTxt->GetText().setCharacterSize(15);
		changeBackBtnTxt->GetText().setStyle(sf::Text::Bold);
		//properties
		m_changeBackBtn->SetVisible(true);
		m_changeBackBtn->SetAlive(true);
		m_changeBackBtn->Init();
		//center text
		changeBackBtnTxt->GetText().setPosition(m_changeBackBtn->GetPosition().x + (m_changeBackBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5f) - changeBackBtnTxt->GetText().getGlobalBounds().width * 0.5f,
			m_changeBackBtn->GetPosition().y + (m_changeBackBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - changeBackBtnTxt->GetText().getGlobalBounds().height * 0.6f);
		m_controls.insert({ "Back", m_changeBackBtn });

		// change Pause button
		m_changePauseBtn = std::make_shared<Button>();
		auto changePauseBtnSprite = m_changePauseBtn->GetSpriteComponent();
		//define sprite
		changePauseBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		changePauseBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		changePauseBtnSprite->GetSprite().scale(0.5, 0.5f);
		m_changePauseBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.2625f - changePauseBtnSprite->GetSprite().getGlobalBounds().width * 0.5f,
			SCREEN_HEIGHT * 0.58f - changePauseBtnSprite->GetSprite().getGlobalBounds().height * 0.5f));
		//text
		auto changePauseBtnTxt = m_changePauseBtn->GetTextComponent();
		changePauseBtnTxt->SetFont(m_data->assets.GetFont("Font_Pixel"));
		changePauseBtnTxt->GetText().setString("Pause");
		changePauseBtnTxt->GetText().setCharacterSize(15);
		changePauseBtnTxt->GetText().setStyle(sf::Text::Bold);
		//properties
		m_changePauseBtn->SetVisible(true);
		m_changePauseBtn->SetAlive(true);
		m_changePauseBtn->Init();
		//center text
		changePauseBtnTxt->GetText().setPosition(m_changePauseBtn->GetPosition().x + (m_changePauseBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5f) - changePauseBtnTxt->GetText().getGlobalBounds().width * 0.5f,
			m_changePauseBtn->GetPosition().y + (m_changePauseBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.6f) - changePauseBtnTxt->GetText().getGlobalBounds().height * 0.6f);
		m_controls.insert({ "Pause", m_changePauseBtn });

		// change Skip button
		m_changeSkipBtn = std::make_shared<Button>();
		auto changeSkipBtnSprite = m_changeSkipBtn->GetSpriteComponent();
		//define sprite
		changeSkipBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
		changeSkipBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		changeSkipBtnSprite->GetSprite().scale(0.5, 0.5f);
		m_changeSkipBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.2625f - changeSkipBtnSprite->GetSprite().getGlobalBounds().width * 0.5f,
			SCREEN_HEIGHT * 0.66f - changeSkipBtnSprite->GetSprite().getGlobalBounds().height * 0.5f));
		//text
		auto changeSkipBtnTxt = m_changeSkipBtn->GetTextComponent();
		changeSkipBtnTxt->SetFont(m_data->assets.GetFont("Font_Pixel"));
		changeSkipBtnTxt->GetText().setString("Skip");
		changeSkipBtnTxt->GetText().setCharacterSize(15);
		changeSkipBtnTxt->GetText().setStyle(sf::Text::Bold);
		//properties
		m_changeSkipBtn->SetVisible(true);
		m_changeSkipBtn->SetAlive(true);
		m_changeSkipBtn->Init();
		//center text
		changeSkipBtnTxt->GetText().setPosition(m_changeSkipBtn->GetPosition().x + (m_changeSkipBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.5f) - changeSkipBtnTxt->GetText().getGlobalBounds().width * 0.5f,
			m_changeSkipBtn->GetPosition().y + (m_changeSkipBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.65) - changeSkipBtnTxt->GetText().getGlobalBounds().height * 0.5f);
		m_controls.insert({ "Skip", m_changeSkipBtn });

		// add to local ents map
		AddEntity("E_zSetBG", bg);
		AddEntity("E_Uncheck1", uncheck1);
		AddEntity("E_Uncheck2", uncheck2);
		AddEntity("E_Uncheck3", uncheck3);
		AddEntity("E_Uncheck4", uncheck4);
		AddEntity("E_Uncheck5", uncheck5);
		AddEntity("E_Save", save);
		AddEntity("E_Back", back);
		AddEntity("E_ChangeBackBtn", m_changeBackBtn);
		AddEntity("E_ChangePauseBtn", m_changePauseBtn);
		AddEntity("E_ChangeSkipBtn", m_changeSkipBtn);

		// pre-populate the settings
		UpdateSettings();
	}

	void SettingsScene::HandleInput()
	{
		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView(event.size.width, event.size.height);

			//check if back button is clicked
			auto backComp = m_data->ents.Find<Button>("E_Back")->GetSpriteComponent();
			auto backClick = m_data->ents.Find<Button>("E_Back")->GetClickableComponent();
			if ((backComp->IsClickable() && m_data->input.isClicked(backComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
				|| sf::Keyboard::isKeyPressed(Controls::GetKey("Back")))
			{
				backClick->SetClicked(true);
			}

			for (auto control : m_controls)
			{
				auto button = control.second;
				if (button->GetSpriteComponent()->IsClickable() && m_data->input.isClicked(button->GetSpriteComponent()->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
				{
					button->GetClickableComponent()->SetClicked(true);
				}
			}

			//check if save button is clicked
			auto saveComp = m_data->ents.Find<Button>("E_Save")->GetSpriteComponent();
			auto saveClick = m_data->ents.Find<Button>("E_Save")->GetClickableComponent();
			if (saveComp->IsClickable() &&  m_data->input.isClicked(saveComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				saveClick->SetClicked(true);
			}

			//check if first circle is clicked
			auto uncheck1Comp = m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<SpriteComponent>("C_UnCheck1Sprite");
			auto uncheck1Click = m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<ClickableComponent>("C_UnCheck1Btn");
			if (uncheck1Comp->IsClickable() &&  m_data->input.isClicked(uncheck1Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				uncheck1Click->SetClicked(true);
			}

			//check if second circle is clicked
			auto uncheck2Comp = m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<SpriteComponent>("C_UnCheck2Sprite");
			auto uncheck2Click = m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<ClickableComponent>("C_UnCheck2Btn");
			if (uncheck2Comp->IsClickable() &&  m_data->input.isClicked(uncheck2Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				uncheck2Click->SetClicked(true);
			}

			//check if third circle is clicked
			auto uncheck3Comp = m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<SpriteComponent>("C_UnCheck3Sprite");
			auto uncheck3Click = m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<ClickableComponent>("C_UnCheck3Btn");
			if (uncheck3Comp->IsClickable() &&  m_data->input.isClicked(uncheck3Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				uncheck3Click->SetClicked(true);
			}

			//check if forth circle is clicked
			auto uncheck4Comp = m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<SpriteComponent>("C_UnCheck4Sprite");
			auto uncheck4Click = m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<ClickableComponent>("C_UnCheck4Btn");
			if (uncheck4Comp->IsClickable() &&  m_data->input.isClicked(uncheck4Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				uncheck4Click->SetClicked(true);
			}

			//check if fifth circle is clicked
			auto uncheck5Comp = m_data->ents.Find<Entity>("E_Uncheck5")->GetComponent<SpriteComponent>("C_UnCheck5Sprite");
			auto uncheck5Click = m_data->ents.Find<Entity>("E_Uncheck5")->GetComponent<ClickableComponent>("C_UnCheck5Btn");
			if (uncheck5Comp->IsClickable() && m_data->input.isClicked(uncheck5Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				uncheck5Click->SetClicked(true);
			}
		}
	}

	void SettingsScene::Update(float t_deltaTime)
	{
		m_data->ents.Update(m_entities, t_deltaTime);

		for (auto control : m_controls)
		{
			auto button = control.second;
			auto action = control.first;

			if (button->GetClickableComponent()->CanResolve())
			{
				button->GetSpriteComponent()->GetSprite().setColor(sf::Color(150, 128, 106, 200));

				for (auto keyToMap = sf::Keyboard::Unknown; keyToMap != sf::Keyboard::Pause; keyToMap = static_cast<sf::Keyboard::Key>(keyToMap + 1))
				{
					if (sf::Keyboard::isKeyPressed(keyToMap))
					{
						Controls::SetKey(action, keyToMap);
						button->GetSpriteComponent()->GetSprite().setColor(sf::Color::White);
						button->GetClickableComponent()->SetResolve(false);
					}
				}

			}
		}

		//resolve back button click
		auto backClick = m_data->ents.Find<Button>("E_Back")->GetClickableComponent();
		if (backClick->CanResolve())
		{
			// change scene to Settings
			m_data->machine.RemoveState();
			
			backClick->SetResolve(false);
		}

		//resolve save button click
		auto saveClick = m_data->ents.Find<Button>("E_Save")->GetClickableComponent();
		if (saveClick->CanResolve())
		{
			// save data to settings file
			m_data->saveData.Save<int>(
			{ 
				static_cast<int>(m_data->settings.GetResolution().x),
				static_cast<int>(m_data->settings.GetResolution().y),
				static_cast<int>(m_data->settings.GetScreenMode())
			}, Utils::DATA_TYPE::GAME_SETTINGS);
			
			// save in-game
			m_data->settings.Save();

			// change scene to Settings
			m_data->machine.RemoveState();
			saveClick->SetResolve(false);
		}

		//resolve first circle click
		auto uncheck1Click = m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<ClickableComponent>("C_UnCheck1Btn");
		if (uncheck1Click->CanResolve())
		{
			//LOGIC FOR RESOLUTION HERE...
			m_data->settings.SetResolution(1024, 768);
			m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<SpriteComponent>("C_UnCheck1Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));

			m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<SpriteComponent>("C_UnCheck2Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<SpriteComponent>("C_UnCheck3Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<SpriteComponent>("C_UnCheck4Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			
			uncheck1Click->SetResolve(false);
		}

		//resolve second circle click
		auto uncheck2Click = m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<ClickableComponent>("C_UnCheck2Btn");
		if (uncheck2Click->CanResolve())
		{
			//LOGIC FOR RESOLUTION HERE...
			m_data->settings.SetResolution(1366, 768);

			m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<SpriteComponent>("C_UnCheck2Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));

			m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<SpriteComponent>("C_UnCheck1Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<SpriteComponent>("C_UnCheck3Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<SpriteComponent>("C_UnCheck4Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));

			uncheck2Click->SetResolve(false);
		}

		//resolve third circle click
		auto uncheck3Click = m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<ClickableComponent>("C_UnCheck3Btn");
		if (uncheck3Click->CanResolve())
		{
			//LOGIC FOR RESOLUTION HERE...
			m_data->settings.SetResolution(1600, 900);
			
			m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<SpriteComponent>("C_UnCheck3Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));

			m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<SpriteComponent>("C_UnCheck1Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<SpriteComponent>("C_UnCheck2Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<SpriteComponent>("C_UnCheck4Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));

			uncheck3Click->SetResolve(false);
		}

		//resolve forth circle click
		auto uncheck4Click = m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<ClickableComponent>("C_UnCheck4Btn");
		if (uncheck4Click->CanResolve())
		{
			//LOGIC FOR RESOLUTION HERE...
			m_data->settings.SetResolution(1920, 1080);
			
			m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<SpriteComponent>("C_UnCheck4Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<SpriteComponent>("C_UnCheck1Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<SpriteComponent>("C_UnCheck2Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<SpriteComponent>("C_UnCheck3Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		
			uncheck4Click->SetResolve(false);
		}

		//resolve fifth circle click
		auto uncheck5Click = m_data->ents.Find<Entity>("E_Uncheck5")->GetComponent<ClickableComponent>("C_UnCheck5Btn");
		if (uncheck5Click->CanResolve())
		{
			if (m_data->settings.GetScreenMode() == SCREEN_MODE::FULLSCREEN)
			{
				m_data->settings.SetScreenMode(SCREEN_MODE::WINDOWED);
				m_data->ents.Find<Entity>("E_Uncheck5")->GetComponent<SpriteComponent>("C_UnCheck5Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			}
			else
			{
				m_data->settings.SetScreenMode(SCREEN_MODE::FULLSCREEN);
				m_data->ents.Find<Entity>("E_Uncheck5")->GetComponent<SpriteComponent>("C_UnCheck5Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));
			}
			
			uncheck5Click->SetResolve(false);
		}
	}

	void SettingsScene::UpdateSettings()
	{
		if (Engine2D::GetWinSize().x == 1024 && Engine2D::GetWinSize().y == 768)
		{
			m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<SpriteComponent>("C_UnCheck1Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));

			m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<SpriteComponent>("C_UnCheck2Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<SpriteComponent>("C_UnCheck3Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<SpriteComponent>("C_UnCheck4Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		}
		if (Engine2D::GetWinSize().x == 1366 && Engine2D::GetWinSize().y == 768)
		{
			m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<SpriteComponent>("C_UnCheck2Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));

			m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<SpriteComponent>("C_UnCheck1Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<SpriteComponent>("C_UnCheck3Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<SpriteComponent>("C_UnCheck4Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		}
		
		if (Engine2D::GetWinSize().x == 1600 && Engine2D::GetWinSize().y == 900)
		{
			m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<SpriteComponent>("C_UnCheck3Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));

			m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<SpriteComponent>("C_UnCheck1Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<SpriteComponent>("C_UnCheck2Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<SpriteComponent>("C_UnCheck4Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		}
		
		if (Engine2D::GetWinSize().x == 1920 && Engine2D::GetWinSize().y == 1080)
		{
			m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<SpriteComponent>("C_UnCheck4Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));

			m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<SpriteComponent>("C_UnCheck1Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<SpriteComponent>("C_UnCheck2Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
			m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<SpriteComponent>("C_UnCheck3Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		}

		if (m_data->settings.GetScreenMode() == SCREEN_MODE::FULLSCREEN)
		{
			m_data->ents.Find<Entity>("E_Uncheck5")->GetComponent<SpriteComponent>("C_UnCheck5Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));
		}
		else
		{
			m_data->ents.Find<Entity>("E_Uncheck5")->GetComponent<SpriteComponent>("C_UnCheck5Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));

		}
	
	}

	void SettingsScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void SettingsScene::AddEntity(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		//add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}
}
