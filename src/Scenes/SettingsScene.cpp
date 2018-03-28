#include "SettingsScene.hpp"
#include "../DEFINITIONS.hpp"
#include <Engine/ECM/Components/ClickableComponent.hpp>


namespace HJ {

	using namespace Engine;
	using namespace System;
	//engine/game compoment namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	SettingsScene::SettingsScene(GameDataRef t_data)
		:m_data(t_data)
	{
		//will not be used for more initialization
	}

	void SettingsScene::Init()
	{
		//load resources
		m_data->assets.LoadTexture("Tex_SettingsBG", SETTING_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_BackBtn", SETTING_SCENE_BACKBTN);
		m_data->assets.LoadTexture("Tex_SaveBtn", SETTING_SCENE_SAVEBTN);
		m_data->assets.LoadTexture("Tex_UpBtn", SETTING_SCENE_UPBTN);
		m_data->assets.LoadTexture("Tex_DownBtn", SETTING_SCENE_DOWNBTN);
		m_data->assets.LoadTexture("Tex_SelectBtn", SETTING_SCENE_SELECTEDBTN);
		m_data->assets.LoadTexture("Tex_UnSelectBtn", SETTING_SCENE_UNSELECTEDBTN);
		m_data->assets.LoadTexture("Tex_TextBox", SETTING_SCENE_TEXTBOX);

		//background
		auto bg = std::make_shared<Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_SettingsBGSprite");
		//define bg sprite
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SettingsBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		bg->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 - bgSprite->GetSprite().getGlobalBounds().width * 0.5 , 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		//Unchecked buttons1
		auto uncheck1 = std::make_shared<Entity>();
		auto uncheck1Sprite = uncheck1->AddComponent<SpriteComponent>("C_UnCheck1Sprite");
		//define sprite
		uncheck1Sprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		uncheck1Sprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		uncheck1->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 - bgSprite->GetSprite().getGlobalBounds().width * 0.45, bgSprite->GetSprite().getGlobalBounds().height * 0.1));
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
		uncheck2->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 - bgSprite->GetSprite().getGlobalBounds().width * 0.25, bgSprite->GetSprite().getGlobalBounds().height * 0.1));
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
		uncheck3->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 - bgSprite->GetSprite().getGlobalBounds().width * 0.005, bgSprite->GetSprite().getGlobalBounds().height * 0.1));
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
		uncheck4->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 + bgSprite->GetSprite().getGlobalBounds().width * 0.25, bgSprite->GetSprite().getGlobalBounds().height * 0.1));
		uncheck4->SetVisible(true);
		uncheck4->SetAlive(true);
		//clickabe component
		auto uncheck4Btn = uncheck4->AddComponent<ClickableComponent>("C_UnCheck4Btn");
		uncheck4Btn->SetSpriteTarget(uncheck4Sprite.get());

		//Unchecked buttons 5- VSYNC
		auto uncheck5 = std::make_shared<Entity>();
		auto uncheck5Sprite = uncheck5->AddComponent<SpriteComponent>("C_UnCheck5Sprite");
		//define sprite
		uncheck5Sprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UnSelectBtn"));
		uncheck5Sprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		uncheck5->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 - bgSprite->GetSprite().getGlobalBounds().width * 0.25, bgSprite->GetSprite().getGlobalBounds().height * 0.23));
		uncheck5->SetVisible(true);
		uncheck5->SetAlive(true);
		//clickabe component
		auto uncheck5Btn = uncheck5->AddComponent<ClickableComponent>("C_UnCheck5Btn");
		uncheck5Btn->SetSpriteTarget(uncheck5Sprite.get());

		//Checked button
		auto check = std::make_shared<Entity>();
		auto checkSprite = check->AddComponent<SpriteComponent>("C_Check1Sprite");
		//define sprite
		checkSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));
		checkSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		check->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 - bgSprite->GetSprite().getGlobalBounds().width * 0.5, 0.0f));
		check->SetVisible(false);
		check->SetAlive(true);

		//TextBox1
		auto textBox1 = std::make_shared<Entity>();
		auto textBoxSprite1 = textBox1->AddComponent<SpriteComponent>("C_TextBoxSprite1");
		//define sprite
		textBoxSprite1->GetSprite().setTexture(m_data->assets.GetTexture("Tex_TextBox"));
		textBoxSprite1->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		textBox1->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 + bgSprite->GetSprite().getGlobalBounds().width * 0.05, bgSprite->GetSprite().getGlobalBounds().height * 0.36));
		textBox1->SetVisible(true);
		textBox1->SetAlive(true);

		//Up Button Master
		auto upBtn1 = std::make_shared<Entity>();
		auto upBtnSprite1 = upBtn1->AddComponent<SpriteComponent>("C_upBtnSprite1");
		//define sprite
		upBtnSprite1->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UpBtn"));
		upBtnSprite1->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		upBtn1->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 + bgSprite->GetSprite().getGlobalBounds().width * 0.05 - upBtnSprite1->GetSprite().getGlobalBounds().width, bgSprite->GetSprite().getGlobalBounds().height * 0.36));
		upBtn1->SetVisible(true);
		upBtn1->SetAlive(true);
		auto upBtn1Click = upBtn1->AddComponent<ClickableComponent>("C_upBtnBtn1");
		upBtn1Click->SetSpriteTarget(upBtnSprite1.get());

		//Down Button Master
		auto downBtn1 = std::make_shared<Entity>();
		auto downBtnSprite1 = downBtn1->AddComponent<SpriteComponent>("C_downBtnSprite1");
		//define sprite
		downBtnSprite1->GetSprite().setTexture(m_data->assets.GetTexture("Tex_DownBtn"));
		downBtnSprite1->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		downBtn1->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 + bgSprite->GetSprite().getGlobalBounds().width * 0.05 + textBoxSprite1->GetSprite().getGlobalBounds().width, bgSprite->GetSprite().getGlobalBounds().height * 0.36));
		downBtn1->SetVisible(true);
		downBtn1->SetAlive(true);
		auto downBtn1Click = downBtn1->AddComponent<ClickableComponent>("C_downBtnBtn1");
		downBtn1Click->SetSpriteTarget(downBtnSprite1.get());

		//TextBox2
		auto textBox2 = std::make_shared<Entity>();
		auto textBoxSprite2 = textBox2->AddComponent<SpriteComponent>("C_TextBoxSprite2");
		//define sprite
		textBoxSprite2->GetSprite().setTexture(m_data->assets.GetTexture("Tex_TextBox"));
		textBoxSprite2->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		textBox2->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 + bgSprite->GetSprite().getGlobalBounds().width * 0.05, bgSprite->GetSprite().getGlobalBounds().height * 0.44));
		textBox2->SetVisible(true);
		textBox2->SetAlive(true);

		//Up Button 
		auto upBtn2 = std::make_shared<Entity>();
		auto upBtnSprite2 = upBtn2->AddComponent<SpriteComponent>("C_upBtnSprite2");
		//define sprite
		upBtnSprite2->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UpBtn"));
		upBtnSprite2->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		upBtn2->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 + bgSprite->GetSprite().getGlobalBounds().width * 0.05 - upBtnSprite2->GetSprite().getGlobalBounds().width, bgSprite->GetSprite().getGlobalBounds().height * 0.44));
		upBtn2->SetVisible(true);
		upBtn2->SetAlive(true);
		auto upBtn2Click = upBtn2->AddComponent<ClickableComponent>("C_upBtnBtn2");
		upBtn2Click->SetSpriteTarget(upBtnSprite2.get());

		//Down Button Master
		auto downBtn2 = std::make_shared<Entity>();
		auto downBtnSprite2 = downBtn2->AddComponent<SpriteComponent>("C_downBtnSprite2");
		//define sprite
		downBtnSprite2->GetSprite().setTexture(m_data->assets.GetTexture("Tex_DownBtn"));
		downBtnSprite2->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		downBtn2->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 + bgSprite->GetSprite().getGlobalBounds().width * 0.05 + textBoxSprite2->GetSprite().getGlobalBounds().width, bgSprite->GetSprite().getGlobalBounds().height * 0.44));
		downBtn2->SetVisible(true);
		downBtn2->SetAlive(true);
		auto downBtn2Click = downBtn2->AddComponent<ClickableComponent>("C_downBtnBtn2");
		downBtn2Click->SetSpriteTarget(downBtnSprite2.get());

		//TextBox3
		auto textBox3 = std::make_shared<Entity>();
		auto textBoxSprite3 = textBox3->AddComponent<SpriteComponent>("C_TextBoxSprite1");
		//define sprite
		textBoxSprite3->GetSprite().setTexture(m_data->assets.GetTexture("Tex_TextBox"));
		textBoxSprite3->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		textBox3->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 + bgSprite->GetSprite().getGlobalBounds().width * 0.05, bgSprite->GetSprite().getGlobalBounds().height * 0.52));
		textBox3->SetVisible(true);
		textBox3->SetAlive(true);

		//Up Button Master
		auto upBtn3 = std::make_shared<Entity>();
		auto upBtnSprite3 = upBtn3->AddComponent<SpriteComponent>("C_upBtnSprite3");
		//define sprite
		upBtnSprite3->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UpBtn"));
		upBtnSprite3->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		upBtn3->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 + bgSprite->GetSprite().getGlobalBounds().width * 0.05 - upBtnSprite3->GetSprite().getGlobalBounds().width, bgSprite->GetSprite().getGlobalBounds().height * 0.52));
		upBtn3->SetVisible(true);
		upBtn3->SetAlive(true);
		auto upBtn3Click = upBtn3->AddComponent<ClickableComponent>("C_upBtnBtn3");
		upBtn3Click->SetSpriteTarget(upBtnSprite3.get());

		//Down Button Master
		auto downBtn3 = std::make_shared<Entity>();
		auto downBtnSprite3 = downBtn3->AddComponent<SpriteComponent>("C_downBtnSprite3");
		//define sprite
		downBtnSprite3->GetSprite().setTexture(m_data->assets.GetTexture("Tex_DownBtn"));
		downBtnSprite3->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		downBtn3->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 + bgSprite->GetSprite().getGlobalBounds().width * 0.05 + textBoxSprite3->GetSprite().getGlobalBounds().width, bgSprite->GetSprite().getGlobalBounds().height * 0.52));
		downBtn3->SetVisible(true);
		downBtn3->SetAlive(true);
		auto downBtn3Click = downBtn3->AddComponent<ClickableComponent>("C_downBtnBtn3");
		downBtn3Click->SetSpriteTarget(downBtnSprite3.get());

		//Save button
		auto save = std::make_shared<Entity>();
		auto saveSprite = save->AddComponent<SpriteComponent>("C_SaveSprite");
		//define sprite
		saveSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SaveBtn"));
		saveSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		save->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 + bgSprite->GetSprite().getGlobalBounds().width * 0.2 , bgSprite->GetSprite().getGlobalBounds().height * 0.8));
		save->SetVisible(true);
		save->SetAlive(true);
		auto saveBtn = save->AddComponent<ClickableComponent>("C_SaveBtn");
		saveBtn->SetSpriteTarget(saveSprite.get());

		//Back button
		auto back = std::make_shared<Entity>();
		auto backSprite = back->AddComponent<SpriteComponent>("C_BackSprite");
		//define sprite
		backSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_BackBtn"));
		backSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		back->SetPosition(sf::Vector2f(SCREEN_WIDTH*0.5 - bgSprite->GetSprite().getGlobalBounds().width * 0.2, bgSprite->GetSprite().getGlobalBounds().height * 0.8));
		back->SetVisible(true);
		back->SetAlive(true);
		//add button component
		auto backBtn = back->AddComponent<ClickableComponent>("C_BackBtnBtn");
		backBtn->SetSpriteTarget(backSprite.get());

		//add to local ents map
		AddEntity("E_zSetBG", bg);
		AddEntity("E_Uncheck1", uncheck1);
		AddEntity("E_Uncheck2", uncheck2);
		AddEntity("E_Uncheck3", uncheck3);
		AddEntity("E_Uncheck4", uncheck4);
		AddEntity("E_Uncheck5", uncheck5);
		AddEntity("E_TextBox1", textBox1);
		AddEntity("E_UpBtn1", upBtn1);
		AddEntity("E_DownBtn1", downBtn1);
		AddEntity("E_TextBox2", textBox2);
		AddEntity("E_UpBtn2", upBtn2);
		AddEntity("E_DownBtn2", downBtn2);
		AddEntity("E_TextBox3", textBox3);
		AddEntity("E_UpBtn3", upBtn3);
		AddEntity("E_DownBtn3", downBtn3);
		AddEntity("E_Save", save);
		AddEntity("E_Back", back);

	}

	void SettingsScene::HandleInput()
	{
		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Engine2D::GetWin().close();
			
		}
		//check if back button is clicked
		auto backComp = m_data->ents.Find<Entity>("E_Back")->GetComponent<SpriteComponent>("C_BackSprite");
		auto backClick = m_data->ents.Find<Entity>("E_Back")->GetComponent<ClickableComponent>("C_BackBtnBtn");
		if (m_data->input.isClicked(backComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			backClick->SetClicked(true);
		}

		//check if save button is clicked
		auto saveComp = m_data->ents.Find<Entity>("E_Save")->GetComponent<SpriteComponent>("C_SaveSprite");
		auto saveClick = m_data->ents.Find<Entity>("E_Save")->GetComponent<ClickableComponent>("C_SaveBtn");
		if (m_data->input.isClicked(saveComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			saveClick->SetClicked(true);
		}

		//check if first circle is clicked
		auto uncheck1Comp = m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<SpriteComponent>("C_UnCheck1Sprite");
		auto uncheck1Click = m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<ClickableComponent>("C_UnCheck1Btn");
		if (m_data->input.isClicked(uncheck1Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			uncheck1Click->SetClicked(true);
		}

		//check if second circle is clicked
		auto uncheck2Comp = m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<SpriteComponent>("C_UnCheck2Sprite");
		auto uncheck2Click = m_data->ents.Find<Entity>("E_Uncheck2")->GetComponent<ClickableComponent>("C_UnCheck2Btn");
		if (m_data->input.isClicked(uncheck2Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			uncheck2Click->SetClicked(true);
		}

		//check if third circle is clicked
		auto uncheck3Comp = m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<SpriteComponent>("C_UnCheck3Sprite");
		auto uncheck3Click = m_data->ents.Find<Entity>("E_Uncheck3")->GetComponent<ClickableComponent>("C_UnCheck3Btn");
		if (m_data->input.isClicked(uncheck3Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			uncheck3Click->SetClicked(true);
		}

		//check if forth circle is clicked
		auto uncheck4Comp = m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<SpriteComponent>("C_UnCheck4Sprite");
		auto uncheck4Click = m_data->ents.Find<Entity>("E_Uncheck4")->GetComponent<ClickableComponent>("C_UnCheck4Btn");
		if (m_data->input.isClicked(uncheck4Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			uncheck4Click->SetClicked(true);
		}

		//check if fifth circle is clicked
		auto uncheck5Comp = m_data->ents.Find<Entity>("E_Uncheck5")->GetComponent<SpriteComponent>("C_UnCheck5Sprite");
		auto uncheck5Click = m_data->ents.Find<Entity>("E_Uncheck5")->GetComponent<ClickableComponent>("C_UnCheck5Btn");
		if (m_data->input.isClicked(uncheck5Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			uncheck5Click->SetClicked(true);
		}

		//check if the first up button is clicked
		auto up1Comp = m_data->ents.Find<Entity>("E_UpBtn1")->GetComponent<SpriteComponent>("C_upBtnSprite1");
		auto up1Click = m_data->ents.Find<Entity>("E_UpBtn1")->GetComponent <ClickableComponent>("C_upBtnBtn1");
		if (m_data->input.isClicked(up1Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			up1Click->SetClicked(true);
		}

		//check if the first down button is clicked
		auto down1Comp = m_data->ents.Find<Entity>("E_DownBtn1")->GetComponent<SpriteComponent>("C_downBtnSprite1");
		auto down1Click = m_data->ents.Find<Entity>("E_DownBtn1")->GetComponent <ClickableComponent>("C_downBtnBtn1");
		if (m_data->input.isClicked(down1Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			down1Click->SetClicked(true);
		}

		//check if the second up button is clicked
		auto up2Comp = m_data->ents.Find<Entity>("E_UpBtn2")->GetComponent<SpriteComponent>("C_upBtnSprite2");
		auto up2Click = m_data->ents.Find<Entity>("E_UpBtn2")->GetComponent <ClickableComponent>("C_upBtnBtn2");
		if (m_data->input.isClicked(up2Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			up2Click->SetClicked(true);
		}

		//check if the second down button is clicked
		auto down2Comp = m_data->ents.Find<Entity>("E_DownBtn2")->GetComponent<SpriteComponent>("C_downBtnSprite2");
		auto down2Click = m_data->ents.Find<Entity>("E_DownBtn2")->GetComponent <ClickableComponent>("C_downBtnBtn2");
		if (m_data->input.isClicked(down2Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			down2Click->SetClicked(true);
		
		}

		//check if the thrid up button is clicked
		auto up3Comp = m_data->ents.Find<Entity>("E_UpBtn3")->GetComponent<SpriteComponent>("C_upBtnSprite3");
		auto up3Click = m_data->ents.Find<Entity>("E_UpBtn3")->GetComponent <ClickableComponent>("C_upBtnBtn3");
		if (m_data->input.isClicked(up3Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			up3Click->SetClicked(true);
		}

		//check if the thrid down button is clicked
		auto down3Comp = m_data->ents.Find<Entity>("E_DownBtn3")->GetComponent<SpriteComponent>("C_downBtnSprite3");
		auto down3Click = m_data->ents.Find<Entity>("E_DownBtn3")->GetComponent <ClickableComponent>("C_downBtnBtn3");
		if (m_data->input.isClicked(down3Comp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
		{
			down3Click->SetClicked(true);
			
		}
	}

	void SettingsScene::Update(float t_deltaTime)
	{
		m_data->ents.Update(m_entities, t_deltaTime);

		//resolve back button click
		auto backClick = m_data->ents.Find<Entity>("E_Back")->GetComponent<ClickableComponent>("C_BackBtnBtn");
		if (backClick->CanResolve())
		{
			m_data->machine.RemoveState();
			backClick->SetResolve(false);
		}

		//resolve save button click
		auto saveClick = m_data->ents.Find<Entity>("E_Save")->GetComponent<ClickableComponent>("C_SaveBtn");
		if (saveClick->CanResolve())
		{
			//ADD LOGIC FOR SAVING THE CHANGES HERE...

			m_data->machine.RemoveState();
			saveClick->SetResolve(false);
		}

		//resolve first circle click
		auto uncheck1Click = m_data->ents.Find<Entity>("E_Uncheck1")->GetComponent<ClickableComponent>("C_UnCheck1Btn");
		if (uncheck1Click->CanResolve())
		{
			//LOGIC FOR RESOLUTION HERE...
			
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
			//LOGIC FOR Vsync HERE...
			m_data->ents.Find<Entity>("E_Uncheck5")->GetComponent<SpriteComponent>("C_UnCheck5Sprite")->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SelectBtn"));
			
			uncheck5Click->SetResolve(false);
		}

		//resolve first up button click
		auto up1Click = m_data->ents.Find<Entity>("E_UpBtn1")->GetComponent <ClickableComponent>("C_upBtnBtn1");
		if (up1Click->CanResolve())
		{	
			//VOLUME UP LOGIC HERE

			up1Click->SetResolve(false);
		}
		//resolve first down button click
		auto down1Click = m_data->ents.Find<Entity>("E_DownBtn1")->GetComponent <ClickableComponent>("C_downBtnBtn1");
		if (down1Click->CanResolve())
		{
			//VOLUME DOWN LOGIC HERE

			down1Click->SetResolve(false);
		}

		//resolve second up button click
		auto up2Click = m_data->ents.Find<Entity>("E_UpBtn2")->GetComponent <ClickableComponent>("C_upBtnBtn2");
		if (up2Click->CanResolve())
		{
			//VOLUME UP LOGIC HERE

			up2Click->SetResolve(false);
		}
		//resolve second down button click
		auto down2Click = m_data->ents.Find<Entity>("E_DownBtn2")->GetComponent <ClickableComponent>("C_downBtnBtn2");
		if (down2Click->CanResolve())
		{
			//VOLUME DOWN LOGIC HERE

			down2Click->SetResolve(false);
		}

		//resolve third up button click
		auto up3Click = m_data->ents.Find<Entity>("E_UpBtn3")->GetComponent <ClickableComponent>("C_upBtnBtn3");
		if (up3Click->CanResolve())
		{
			//VOLUME UP LOGIC HERE

			up3Click->SetResolve(false);
		}
		//resolve third down button click
		auto down3Click = m_data->ents.Find<Entity>("E_DownBtn3")->GetComponent <ClickableComponent>("C_downBtnBtn3");
		if (down3Click->CanResolve())
		{
			//VOLUME DOWN LOGIC HERE

			down3Click->SetResolve(false);
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
