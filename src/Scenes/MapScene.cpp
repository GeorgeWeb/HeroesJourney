#include "MapScene.hpp"
#include "PauseMenu.hpp"

#include "../Entities/AnimatedLogo.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	MapScene::MapScene(GameDataRef t_data) :
		m_data(t_data)
	{
		InitSceneView();
	}

	void MapScene::Init()
	{
		m_data->assets.LoadTexture("Tex_MapBG", MAP_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_Castle", MAP_SCENE_CASTLE);
		m_data->assets.LoadTexture("Tex_Forest", MAP_SCENE_FOREST);
		m_data->assets.LoadTexture("Tex_Mountains", MAP_SCENE_MOUNTAINS);
		m_data->assets.LoadTexture("Tex_Sea", MAP_SCENE_SEA);
		m_data->assets.LoadTexture("Tex_EvilCastle", MAP_SCENE_EVIL_CASTLE);
		m_data->assets.LoadTexture("Tex_Frame", MAP_SCENE_UI_FRAME);
		m_data->assets.LoadTexture("Tex_PopupBG", ENCOUNTER_POPUP_BACKGROUND);
		m_data->assets.LoadTexture("Tex_PopupCloseBtn", ENCOUNTER_POPUP_CLOSE_BTN);
		m_data->assets.LoadTexture("Tex_PopupPlayBtn", ENCOUNTER_POPUP_PLAY_BTN);
		m_data->assets.LoadTexture("Tex_PopupOpponent", ENCOUNTER_POPUP_OPPONENT);
		m_data->assets.LoadTexture("Tex_PopupStory", ENCOUNTER_POPUP_STORY);
		m_data->assets.LoadTexture("Tex_KnightIcon", MAP_SCENE_KNIGHT_ICON);
		m_data->assets.LoadTexture("Tex_SorcIcon", MAP_SCENE_SORC_ICON);
		m_data->assets.LoadTexture("Tex_BardIcon", MAP_SCENE_BARD_ICON);
		m_data->assets.LoadTexture("Tex_RougeIcon", MAP_SCENE_ROUGE_ICON);

		//Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_MapBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_MapBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		bgSprite->GetSprite().scale(0.9f, 0.85f);
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		//Castle
		auto castle = std::make_shared<ECM::Entity>();
		auto castleSprite = castle->AddComponent<SpriteComponent>("C_CastleSprite");
		//define castle sprite
		castleSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Castle"));
		castleSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		castle->SetPosition(sf::Vector2f((SCREEN_WIDTH - castleSprite->GetSprite().getGlobalBounds().width) * 0.1f,
			(SCREEN_HEIGHT - castleSprite->GetSprite().getGlobalBounds().height) * 0.3f));
		castle->SetVisible(true);
		castle->SetAlive(true);
		//clickable component
		auto castleBtn = castle->AddComponent<ClickableComponent>("C_CastleBtn");
		castleBtn->SetSpriteTarget(castleSprite.get());

		//Forest
		auto forest = std::make_shared<ECM::Entity>();
		auto forestSprite = forest->AddComponent<SpriteComponent>("C_ForestSprite");
		//define castle sprite
		forestSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Forest"));
		forestSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		forest->SetPosition(sf::Vector2f((SCREEN_WIDTH - castleSprite->GetSprite().getGlobalBounds().width) * 0.35f,
			(SCREEN_HEIGHT - castleSprite->GetSprite().getGlobalBounds().height) * 0.5f));
		forest->SetVisible(true);
		forest->SetAlive(true);
		//clickable component
		auto forestBtn = forest->AddComponent<ClickableComponent>("C_ForestBtn");
		forestBtn->SetSpriteTarget(forestSprite.get());
		
		//Mountains
		auto mountains = std::make_shared<ECM::Entity>();
		auto mountainsSprite = mountains->AddComponent<SpriteComponent>("C_MountainsSprite");
		//define castle sprite
		mountainsSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Mountains"));
		mountainsSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		mountains->SetPosition(sf::Vector2f((SCREEN_WIDTH - mountainsSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(SCREEN_HEIGHT - mountainsSprite->GetSprite().getGlobalBounds().height) * 0.8f));
		mountains->SetVisible(true);
		mountains->SetAlive(true);
		auto mountainsBtn = mountains->AddComponent<ClickableComponent>("C_MountainsBtn");
		mountainsBtn->SetSpriteTarget(mountainsSprite.get());

		//Sea
		auto sea = std::make_shared<ECM::Entity>();
		auto seaSprite = sea->AddComponent<SpriteComponent>("C_SeaSprite");
		//define castle sprite
		seaSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Sea"));
		seaSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		sea->SetPosition(sf::Vector2f((SCREEN_WIDTH - seaSprite->GetSprite().getGlobalBounds().width) * 0.95f,
			(SCREEN_HEIGHT - seaSprite->GetSprite().getGlobalBounds().height) * 0.9f));
		sea->SetVisible(true);
		sea->SetAlive(true);
		auto seaBtn = sea->AddComponent<ClickableComponent>("C_SeaBtn");
		seaBtn->SetSpriteTarget(seaSprite.get());

		//Evil Castle
		auto evilCastle = std::make_shared<ECM::Entity>();
		auto evilCastleSprite = evilCastle->AddComponent<SpriteComponent>("C_EvilCastleSprite");
		//define castle sprite
		evilCastleSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_EvilCastle"));
		evilCastleSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		evilCastle->SetPosition(sf::Vector2f((SCREEN_WIDTH - evilCastleSprite->GetSprite().getGlobalBounds().width) * 0.7f,
			(SCREEN_HEIGHT - evilCastleSprite->GetSprite().getGlobalBounds().height) * 0.2f));
		evilCastle->SetVisible(true);
		evilCastle->SetAlive(true);
		auto evilCastleBtn = evilCastle->AddComponent<ClickableComponent>("C_EvilCastleBtn");
		evilCastleBtn->SetSpriteTarget(evilCastleSprite.get());

		//UI frame
		auto frame = std::make_shared<ECM::Entity>();
		auto frameSprite = frame->AddComponent<SpriteComponent>("C_FrameSprite");
		//define castle sprite
		frameSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Frame"));
		frameSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		frameSprite->GetSprite().scale(0.9f, 0.9f);
		frame->SetPosition(sf::Vector2f((SCREEN_WIDTH - frameSprite->GetSprite().getGlobalBounds().width * 2.4f),
			(SCREEN_HEIGHT - frameSprite->GetSprite().getGlobalBounds().height)));
		frame->SetVisible(true);
		frame->SetAlive(true);

		//knight icon
		auto knightIcon = std::make_shared<ECM::Entity>();
		auto knightIconSprite = knightIcon->AddComponent<SpriteComponent>("C_KnightIconSprite");
		//sprite properties
		knightIconSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_KnightIcon"));
		knightIconSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//more properties
		knightIcon->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.04, SCREEN_HEIGHT * 0.73));
		knightIcon->SetVisible(true);
		knightIcon->SetAlive(true);
		knightIconSprite->GetSprite().scale(2.5, 2.5);
		auto knightIconBtn = knightIcon->AddComponent<ClickableComponent>("C_KnightIconBtn");
		knightIconBtn->SetSpriteTarget(knightIconSprite.get());

		//sorcerres icon
		auto sorcIcon = std::make_shared<ECM::Entity>();
		auto sorcIconSprite = sorcIcon->AddComponent<SpriteComponent>("C_SorcIconSprite");
		//sprite properties
		sorcIconSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SorcIcon"));
		sorcIconSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//more properties
		sorcIcon->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.16, SCREEN_HEIGHT * 0.73));
		sorcIcon->SetVisible(true);
		sorcIcon->SetAlive(true);
		sorcIconSprite->GetSprite().scale(2.5, 2.5);
		auto sorcIconBtn = sorcIcon->AddComponent<ClickableComponent>("C_SorcIconBtn");
		sorcIconBtn->SetSpriteTarget(sorcIconSprite.get());

		//bard icon
		auto bardIcon = std::make_shared<ECM::Entity>();
		auto bardIconSprite = bardIcon->AddComponent<SpriteComponent>("C_BardIconSprite");
		//sprite properties
		bardIconSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_BardIcon"));
		bardIconSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//more properties
		bardIcon->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.04, SCREEN_HEIGHT * 0.85));
		bardIcon->SetVisible(true);
		bardIcon->SetAlive(true);
		bardIconSprite->GetSprite().scale(2.5, 2.5);
		auto bardIconBtn = bardIcon->AddComponent<ClickableComponent>("C_BardIconBtn");
		bardIconBtn->SetSpriteTarget(bardIconSprite.get());

		//rouge icon
		auto rougeIcon = std::make_shared<ECM::Entity>();
		auto rougeIconSprite = rougeIcon->AddComponent<SpriteComponent>("C_RougeIconSprite");
		//sprite properties
		rougeIconSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_RougeIcon"));
		rougeIconSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//more properties
		rougeIcon->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.16, SCREEN_HEIGHT * 0.85));
		rougeIcon->SetVisible(true);
		rougeIcon->SetAlive(true);
		rougeIconSprite->GetSprite().scale(2.5, 2.5);
		auto rougeIconBtn = rougeIcon->AddComponent<ClickableComponent>("C_RougeIconBtn");
		rougeIconBtn->SetSpriteTarget(rougeIconSprite.get());

		// init the encounter popup
		m_encounterPopup = std::make_shared<EncounterPopup>();
		m_encounterPopup->GetComponent<SpriteComponent>("C_zPopupBGSprite")->GetSprite().scale(1.0f, 1.0f);
		// set components
		m_encounterPopup->SetBackgroundImage(m_data->assets.GetTexture("Tex_PopupBG"));
		m_encounterPopup->SetCloseButtonImage(m_data->assets.GetTexture("Tex_PopupCloseBtn"));
		m_encounterPopup->SetPlayButtonImage(m_data->assets.GetTexture("Tex_PopupPlayBtn"));
		m_encounterPopup->SetOpponentImage(m_data->assets.GetTexture("Tex_PopupOpponent"));
		m_encounterPopup->SetStoryImage(m_data->assets.GetTexture("Tex_PopupStory"));
		m_encounterPopup->SetTitleText("ENCOUNTER #?", m_data->assets.GetFont("Font_Pixel"));
		// position
		m_encounterPopup->SetPosition(sf::Vector2f(
			(SCREEN_WIDTH - m_encounterPopup->GetComponent<SpriteComponent>("C_zPopupBGSprite")->GetSprite().getGlobalBounds().width) * 0.5f,
			(SCREEN_HEIGHT - m_encounterPopup->GetComponent<SpriteComponent>("C_zPopupBGSprite")->GetSprite().getGlobalBounds().height) * 0.5f
		));
		m_encounterPopup->Init();
		m_encounterPopup->Assemble(m_encounterPopup->GetPosition());

		//Texts for the charachter UI
		// Text
		auto text = std::make_shared<Entity>();
		auto infTextFont = text->AddComponent<TextComponent>("C_Text");
		// define
		infTextFont->SetFont(m_data->assets.GetFont("Font_Pixel"));
		infTextFont->GetText().setCharacterSize(12);
		text->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.26, SCREEN_HEIGHT * 0.75));
		// properties
		text->showOnCreate = false;
		text->SetVisible(false);
		text->SetAlive(true);
		text->Init();
		infTextFont->GetText().setString("1111111111111");

		// Text 2
		auto text2 = std::make_shared<Entity>();
		auto infTextFont2 = text2->AddComponent<TextComponent>("C_Text2");
		// define
		infTextFont2->SetFont(m_data->assets.GetFont("Font_Pixel"));
		infTextFont2->GetText().setCharacterSize(12);
		text2->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.26, SCREEN_HEIGHT * 0.80));
		// properties
		text2->showOnCreate = false;
		text2->SetVisible(false);
		text2->SetAlive(true);
		text2->Init();
		infTextFont2->GetText().setString("22222222222222222");

		// Text 3
		auto text3 = std::make_shared<Entity>();
		auto infTextFont3 = text3->AddComponent<TextComponent>("C_Text3");
		// define
		infTextFont3->SetFont(m_data->assets.GetFont("Font_Pixel"));
		infTextFont3->GetText().setCharacterSize(12);
		text3->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.26, SCREEN_HEIGHT * 0.87));
		// properties
		text3->showOnCreate = false;
		text3->SetVisible(false);
		text3->SetAlive(true);
		text3->Init();
		infTextFont3->GetText().setString("3333333333333333");

		// Text 4
		auto text4 = std::make_shared<Entity>();
		auto infTextFont4 = text4->AddComponent<TextComponent>("C_Text4");
		// define
		infTextFont4->SetFont(m_data->assets.GetFont("Font_Pixel"));
		infTextFont4->GetText().setCharacterSize(12);
		text4->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.26, SCREEN_HEIGHT * 0.92));
		// properties
		text4->showOnCreate = false;
		text4->SetVisible(false);
		text4->SetAlive(true);
		text4->Init();
		infTextFont4->GetText().setString("4444444444444444");

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! "z" for background "x" for UI
		AddEntity("E_zMapBG", bg);
		AddEntity("E_Castle", castle);
		AddEntity("E_Forest", forest);
		AddEntity("E_Mountains", mountains);
		AddEntity("E_Sea", sea);
		AddEntity("E_EvilCastle", evilCastle);
		AddEntity("E_xFrame", frame);
		AddEntity("E_aEncounterPopup", m_encounterPopup);
		AddEntity("E_0KnightIcon", knightIcon);
		AddEntity("E_0SorcIcon", sorcIcon);
		AddEntity("E_0RogueIcon", rougeIcon);
		AddEntity("E_0BardIcon", bardIcon);
		AddEntity("E_0Text", text);
		AddEntity("E_0Text2", text2);
		AddEntity("E_0Text3", text3);
		AddEntity("E_0Text4", text4);


		
		// WOW ... 3 hrs to get to that one right here :) Kinda easy to use now.
		//m_data->ents.Find<AnimatedLogo>("E_GameLogo")->Init();
		//AddEntity("E_GameLogo", m_data->ents.GetSharedEntity("E_GameLogo"));
	}

	void MapScene::HandleInput()
	{
		auto bg = m_data->ents.Find<Entity>("E_zMapBG");
		auto bgComp = m_data->ents.Find<Entity>("E_zMapBG")->GetComponent<SpriteComponent>("C_MapBGSprite");
		auto frame = m_data->ents.Find<Entity>("E_xFrame");
		auto frameComp = m_data->ents.Find<Entity>("E_xFrame")->GetComponent<SpriteComponent>("C_FrameSprite");
		auto castleComp = m_data->ents.Find<Entity>("E_Castle")->GetComponent<SpriteComponent>("C_CastleSprite");
		auto castleBtn = m_data->ents.Find<Entity>("E_Castle")->GetComponent<ClickableComponent>("C_CastleBtn");
		auto forestComp = m_data->ents.Find<Entity>("E_Forest")->GetComponent<SpriteComponent>("C_ForestSprite");
		auto forestBtn = m_data->ents.Find<Entity>("E_Forest")->GetComponent<ClickableComponent>("C_ForestBtn");
		auto mountainsComp = m_data->ents.Find<Entity>("E_Mountains")->GetComponent<SpriteComponent>("C_MountainsSprite");
		auto mountainsBtn = m_data->ents.Find<Entity>("E_Mountains")->GetComponent<ClickableComponent>("C_MountainsBtn");
		auto seaComp = m_data->ents.Find<Entity>("E_Sea")->GetComponent<SpriteComponent>("C_SeaSprite");
		auto seaBtn = m_data->ents.Find<Entity>("E_Sea")->GetComponent<ClickableComponent>("C_SeaBtn");
		auto evilCastleComp = m_data->ents.Find<Entity>("E_EvilCastle")->GetComponent<SpriteComponent>("C_EvilCastleSprite");
		auto evilCastleBtn = m_data->ents.Find<Entity>("E_EvilCastle")->GetComponent<ClickableComponent>("C_EvilCastleBtn");
		auto knightComp = m_data->ents.Find<Entity>("E_0KnightIcon")->GetComponent<SpriteComponent>("C_KnightIconSprite");
		auto sorcComp = m_data->ents.Find<Entity>("E_0SorcIcon")->GetComponent<SpriteComponent>("C_SorcIconSprite");
		auto rogueComp = m_data->ents.Find<Entity>("E_0RogueIcon")->GetComponent<SpriteComponent>("C_RougeIconSprite");
		auto bardComp = m_data->ents.Find<Entity>("E_0BardIcon")->GetComponent<SpriteComponent>("C_BardIconSprite");
		auto knightBtn = m_data->ents.Find<Entity>("E_0KnightIcon")->GetComponent<ClickableComponent>("C_KnightIconBtn");
		auto sorcBtn = m_data->ents.Find<Entity>("E_0SorcIcon")->GetComponent<ClickableComponent>("C_SorcIconBtn");
		auto rogueBtn = m_data->ents.Find<Entity>("E_0RogueIcon")->GetComponent<ClickableComponent>("C_RougeIconBtn");
		auto bardBtn = m_data->ents.Find<Entity>("E_0BardIcon")->GetComponent<ClickableComponent>("C_BardIconBtn");

		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView(event.size.width, event.size.height);

			// Pause menu
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				// Switch scenes (to Pause Menu)
				auto pauseMenuState = std::make_unique<PauseMenuScene>(PauseMenuScene(m_data));
				m_data->machine.AddState(std::move(pauseMenuState), false);
			}

			//check for castle click
			if (castleComp->IsClickable() && m_data->input.isClicked(castleComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				castleBtn->SetClicked(true);
				auto CastleInterior = std::make_unique<CastleScene>(CastleScene(m_data));
				m_data->machine.AddState(std::move(CastleInterior), false);
			}
			
			//check for forest click
			if (forestComp->IsClickable() && m_data->input.isClicked(forestComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				forestBtn->SetClicked(true);
				
				// SET CREATION BEHAVIOUR
				m_encounterPopup->OnDisplay([=]()
				{
					// Show the encounter popup
					m_encounterPopup->SetVisible(true);
					m_encounterPopup->SetAlive(true);
					
					// turn closing check on
					m_encounterPopup->ToggleCloseBtnBehaviour();

					// Change the textures of the popup
					// TODO: ...

					// Fade Entities
					bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 100.0f));
					frameComp->GetSprite().setColor(sf::Color(frameComp->GetSprite().getColor().r, frameComp->GetSprite().getColor().g, frameComp->GetSprite().getColor().b, 10.0f));
					castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r, castleComp->GetSprite().getColor().g, castleComp->GetSprite().getColor().b, 10.0f));
					forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r, forestComp->GetSprite().getColor().g, forestComp->GetSprite().getColor().b, 10.0f));
					mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r, mountainsComp->GetSprite().getColor().g, mountainsComp->GetSprite().getColor().b, 10.0f));
					seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 10.0f));
					evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					knightComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					sorcComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					rogueComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					bardComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					
					// Make Entities Unclickable
					castleComp->SetClickable(false);
					frameComp->SetClickable(false);
					forestComp->SetClickable(false);
					mountainsComp->SetClickable(false);
					seaComp->SetClickable(false);
					evilCastleComp->SetClickable(false);
					knightComp->SetClickable(false);
					sorcComp->SetClickable(false);
					rogueComp->SetClickable(false);
					bardComp->SetClickable(false);
				});

				// SET CLOSING BEHAVIOUR
				m_encounterPopup->OnClose = [=]()
				{
					// Hide the encounter popup
					m_encounterPopup->SetVisible(false);
					m_encounterPopup->SetAlive(false);

					// turn closing check off
					m_encounterPopup->ToggleCloseBtnBehaviour();

					// Unfade Entities
					bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 255.0f));
					frameComp->GetSprite().setColor(sf::Color(frameComp->GetSprite().getColor().r, frameComp->GetSprite().getColor().g, frameComp->GetSprite().getColor().b, 255.0f));
					castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r, castleComp->GetSprite().getColor().g, castleComp->GetSprite().getColor().b, 255.0f));
					forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r, forestComp->GetSprite().getColor().g, forestComp->GetSprite().getColor().b, 255.0f));
					mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r, mountainsComp->GetSprite().getColor().g, mountainsComp->GetSprite().getColor().b, 255.0f));
					seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 255.0f));
					knightComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					sorcComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					rogueComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					bardComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));

					// Make Entities Clickable
					castleComp->SetClickable(true);
					frameComp->SetClickable(true);
					forestComp->SetClickable(true);
					mountainsComp->SetClickable(true);
					seaComp->SetClickable(true);
					evilCastleComp->SetClickable(true);
					knightComp->SetClickable(true);
					sorcComp->SetClickable(true);
					rogueComp->SetClickable(true);
					bardComp->SetClickable(true);
				};
			}

			//check for mountains click
			if (mountainsComp->IsClickable() && m_data->input.isClicked(mountainsComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				mountainsBtn->SetClicked(true);

				// SET CREATION BEHAVIOUR
				m_encounterPopup->OnDisplay([=]()
				{
					// Show the encounter popup
					m_encounterPopup->SetVisible(true);
					m_encounterPopup->SetAlive(true);

					// turn closing check on
					m_encounterPopup->ToggleCloseBtnBehaviour();

					// Change the textures of the popup
					// TODO: ...

					// Fade Entities
					bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 100.0f));
					frameComp->GetSprite().setColor(sf::Color(frameComp->GetSprite().getColor().r, frameComp->GetSprite().getColor().g, frameComp->GetSprite().getColor().b, 10.0f));
					castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r, castleComp->GetSprite().getColor().g, castleComp->GetSprite().getColor().b, 10.0f));
					forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r, forestComp->GetSprite().getColor().g, forestComp->GetSprite().getColor().b, 10.0f));
					mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r, mountainsComp->GetSprite().getColor().g, mountainsComp->GetSprite().getColor().b, 10.0f));
					seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 10.0f));
					evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					knightComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					sorcComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					rogueComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					bardComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));

					// Make Entities Unclickable
					castleComp->SetClickable(false);
					frameComp->SetClickable(false);
					forestComp->SetClickable(false);
					mountainsComp->SetClickable(false);
					seaComp->SetClickable(false);
					evilCastleComp->SetClickable(false);
					knightComp->SetClickable(false);
					sorcComp->SetClickable(false);
					rogueComp->SetClickable(false);
					bardComp->SetClickable(false);
				});

				// SET CLOSING BEHAVIOUR
				m_encounterPopup->OnClose = [=]()
				{
					// Hide the encounter popup
					m_encounterPopup->SetVisible(false);
					m_encounterPopup->SetAlive(false);

					// turn closing check off
					m_encounterPopup->ToggleCloseBtnBehaviour();

					// Unfade Entities
					bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 255.0f));
					frameComp->GetSprite().setColor(sf::Color(frameComp->GetSprite().getColor().r, frameComp->GetSprite().getColor().g, frameComp->GetSprite().getColor().b, 255.0f));
					castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r, castleComp->GetSprite().getColor().g, castleComp->GetSprite().getColor().b, 255.0f));
					forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r, forestComp->GetSprite().getColor().g, forestComp->GetSprite().getColor().b, 255.0f));
					mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r, mountainsComp->GetSprite().getColor().g, mountainsComp->GetSprite().getColor().b, 255.0f));
					seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 255.0f));
					knightComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					sorcComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					rogueComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					bardComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));


					// Make Entities Clickable
					castleComp->SetClickable(true);
					frameComp->SetClickable(true);
					forestComp->SetClickable(true);
					mountainsComp->SetClickable(true);
					seaComp->SetClickable(true);
					evilCastleComp->SetClickable(true);
					knightComp->SetClickable(true);
					sorcComp->SetClickable(true);
					rogueComp->SetClickable(true);
					bardComp->SetClickable(true);
				};
			}

			//check for sea click
			if (seaComp->IsClickable() && m_data->input.isClicked(seaComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				seaBtn->SetClicked(true);

				// SET CREATION BEHAVIOUR
				m_encounterPopup->OnDisplay([=]()
				{
					// Show the encounter popup
					m_encounterPopup->SetVisible(true);
					m_encounterPopup->SetAlive(true);

					// turn closing check on
					m_encounterPopup->ToggleCloseBtnBehaviour();

					// Change the textures of the popup
					// TODO: ...

					// Fade Entities
					bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 100.0f));
					frameComp->GetSprite().setColor(sf::Color(frameComp->GetSprite().getColor().r, frameComp->GetSprite().getColor().g, frameComp->GetSprite().getColor().b, 10.0f));
					castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r, castleComp->GetSprite().getColor().g, castleComp->GetSprite().getColor().b, 10.0f));
					forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r, forestComp->GetSprite().getColor().g, forestComp->GetSprite().getColor().b, 10.0f));
					mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r, mountainsComp->GetSprite().getColor().g, mountainsComp->GetSprite().getColor().b, 10.0f));
					seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 10.0f));
					evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					knightComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					sorcComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					rogueComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					bardComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));

					// Make Entities Unclickable
					castleComp->SetClickable(false);
					frameComp->SetClickable(false);
					forestComp->SetClickable(false);
					mountainsComp->SetClickable(false);
					seaComp->SetClickable(false);
					evilCastleComp->SetClickable(false);
					knightComp->SetClickable(false);
					sorcComp->SetClickable(false);
					rogueComp->SetClickable(false);
					bardComp->SetClickable(false);
				});

				// SET CLOSING BEHAVIOUR
				m_encounterPopup->OnClose = [=]()
				{
					// Hide the encounter popup
					m_encounterPopup->SetVisible(false);
					m_encounterPopup->SetAlive(false);

					// turn closing check off
					m_encounterPopup->ToggleCloseBtnBehaviour();

					// Unfade Entities
					bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 255.0f));
					frameComp->GetSprite().setColor(sf::Color(frameComp->GetSprite().getColor().r, frameComp->GetSprite().getColor().g, frameComp->GetSprite().getColor().b, 255.0f));
					castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r, castleComp->GetSprite().getColor().g, castleComp->GetSprite().getColor().b, 255.0f));
					forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r, forestComp->GetSprite().getColor().g, forestComp->GetSprite().getColor().b, 255.0f));
					mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r, mountainsComp->GetSprite().getColor().g, mountainsComp->GetSprite().getColor().b, 255.0f));
					seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 255.0f));
					knightComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					sorcComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					rogueComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					bardComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));

					// Make Entities Clickable
					castleComp->SetClickable(true);
					frameComp->SetClickable(true);
					forestComp->SetClickable(true);
					mountainsComp->SetClickable(true);
					seaComp->SetClickable(true);
					evilCastleComp->SetClickable(true);
					knightComp->SetClickable(true);
					sorcComp->SetClickable(true);
					rogueComp->SetClickable(true);
					bardComp->SetClickable(true);
				};
			}

			//check for evil castle click
			if (evilCastleComp->IsClickable() && m_data->input.isClicked(evilCastleComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				evilCastleBtn->SetClicked(true);

				// SET CREATION BEHAVIOUR
				m_encounterPopup->OnDisplay([=]()
				{
					// Show the encounter popup
					m_encounterPopup->SetVisible(true);
					m_encounterPopup->SetAlive(true);

					// turn closing check on
					m_encounterPopup->ToggleCloseBtnBehaviour();

					// Change the textures of the popup
					// TODO: ...

					// Fade Entities
					bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 100.0f));
					frameComp->GetSprite().setColor(sf::Color(frameComp->GetSprite().getColor().r, frameComp->GetSprite().getColor().g, frameComp->GetSprite().getColor().b, 10.0f));
					castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r, castleComp->GetSprite().getColor().g, castleComp->GetSprite().getColor().b, 10.0f));
					forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r, forestComp->GetSprite().getColor().g, forestComp->GetSprite().getColor().b, 10.0f));
					mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r, mountainsComp->GetSprite().getColor().g, mountainsComp->GetSprite().getColor().b, 10.0f));
					seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 10.0f));
					evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					knightComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					sorcComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					rogueComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));
					bardComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 10.0f));

					// Make Entities Unclickable
					castleComp->SetClickable(false);
					frameComp->SetClickable(false);
					forestComp->SetClickable(false);
					mountainsComp->SetClickable(false);
					seaComp->SetClickable(false);
					evilCastleComp->SetClickable(false);
					knightComp->SetClickable(false);
					sorcComp->SetClickable(false);
					rogueComp->SetClickable(false);
					bardComp->SetClickable(false);
				});

				// SET CLOSING BEHAVIOUR
				m_encounterPopup->OnClose = [=]()
				{
					// Hide the encounter popup
					m_encounterPopup->SetVisible(false);
					m_encounterPopup->SetAlive(false);

					// turn closing check off
					m_encounterPopup->ToggleCloseBtnBehaviour();

					// Unfade Entities
					bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 255.0f));
					frameComp->GetSprite().setColor(sf::Color(frameComp->GetSprite().getColor().r, frameComp->GetSprite().getColor().g, frameComp->GetSprite().getColor().b, 255.0f));
					castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r, castleComp->GetSprite().getColor().g, castleComp->GetSprite().getColor().b, 255.0f));
					forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r, forestComp->GetSprite().getColor().g, forestComp->GetSprite().getColor().b, 255.0f));
					mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r, mountainsComp->GetSprite().getColor().g, mountainsComp->GetSprite().getColor().b, 255.0f));
					seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r, evilCastleComp->GetSprite().getColor().g, evilCastleComp->GetSprite().getColor().b, 255.0f));
					knightComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					sorcComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					rogueComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));
					bardComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r, seaComp->GetSprite().getColor().g, seaComp->GetSprite().getColor().b, 255.0f));

					// Make Entities Clickable
					castleComp->SetClickable(true);
					frameComp->SetClickable(true);
					forestComp->SetClickable(true);
					mountainsComp->SetClickable(true);
					seaComp->SetClickable(true);
					evilCastleComp->SetClickable(true);
					knightComp->SetClickable(true);
					sorcComp->SetClickable(true);
					rogueComp->SetClickable(true);
					bardComp->SetClickable(true);
				};
			}

			if (knightComp->IsClickable() && m_data->input.isClicked(knightComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				knightBtn->SetClicked(true);

				lastClicked = "knight";
			}

			if (rogueComp->IsClickable() && m_data->input.isClicked(rogueComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				rogueBtn->SetClicked(true);

				lastClicked = "rouge";
			}

			if (bardComp->IsClickable() && m_data->input.isClicked(bardComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				bardBtn->SetClicked(true);

				lastClicked = "bard";
			}

			if (sorcComp->IsClickable() && m_data->input.isClicked(sorcComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				sorcBtn->SetClicked(true);

				lastClicked = "sorc";
			}

		}
	}

	void MapScene::Update(float t_delatTime)
	{
		//update hero stat
		UpdateText();

		auto castleBtn = m_data->ents.Find<Entity>("E_Castle")->GetComponent<ClickableComponent>("C_CastleBtn");
		auto forestBtn = m_data->ents.Find<Entity>("E_Forest")->GetComponent<ClickableComponent>("C_ForestBtn");
		auto mountainsBtn = m_data->ents.Find<Entity>("E_Mountains")->GetComponent<ClickableComponent>("C_MountainsBtn");
		auto seaBtn = m_data->ents.Find<Entity>("E_Sea")->GetComponent<ClickableComponent>("C_SeaBtn");
		auto evilCastleBtn = m_data->ents.Find<Entity>("E_EvilCastle")->GetComponent<ClickableComponent>("C_EvilCastleBtn");
		auto knightBtn = m_data->ents.Find<Entity>("E_0KnightIcon")->GetComponent<ClickableComponent>("C_KnightIconBtn");
		auto sorcBtn = m_data->ents.Find<Entity>("E_0SorcIcon")->GetComponent<ClickableComponent>("C_SorcIconBtn");
		auto rogueBtn = m_data->ents.Find<Entity>("E_0RogueIcon")->GetComponent<ClickableComponent>("C_RougeIconBtn");
		auto bardBtn = m_data->ents.Find<Entity>("E_0BardIcon")->GetComponent<ClickableComponent>("C_BardIconBtn");
		
		//show if castle is clicked
		if (castleBtn->CanResolve())
		{
			castleBtn->SetResolve(false);
		}

		//show if forest is clicked
		if (forestBtn->CanResolve())
		{
			forestBtn->SetResolve(false);
		}

		//show if mountains are clicked
		if (mountainsBtn->CanResolve())
		{
			mountainsBtn->SetResolve(false);
		}

		//show if sea are clicked
		if (seaBtn->CanResolve())
		{
			seaBtn->SetResolve(false);
		}

		//show if evilCastle are clicked
		if (evilCastleBtn->CanResolve())
		{
			evilCastleBtn->SetResolve(false);
		}
		//show if bard is clicked
		if (bardBtn->CanResolve())
		{
			bardBtn->SetResolve(false);
		}
		//show if rogue is clicked
		if (rogueBtn->CanResolve())
		{
			rogueBtn->SetResolve(false);
		}

		//show if sorceress is clicked
		if (sorcBtn->CanResolve())
		{
			sorcBtn->SetResolve(false);
		}

		//show if knight is clicked
		if (knightBtn->CanResolve())
		{
			knightBtn->SetResolve(false);
		}

	
		m_data->ents.Update(m_entities, t_delatTime);
	}

	void MapScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void MapScene::UpdateText()
	{
		if (lastClicked == "knight")
		{
			m_data->ents.Find<Entity>("E_0Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("HP: "+ std::to_string(m_data->gm.hKnight->GetHealth()) + "/" + std::to_string(m_data->gm.hKnight->GetMaxHealth()));
			m_data->ents.Find<Entity>("E_0Text")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text2")->GetComponent<TextComponent>("C_Text2")->GetText().setString(" MN: " + std::to_string(m_data->gm.hKnight->GetMana()) + "/" + std::to_string(m_data->gm.hKnight->GetMaxMana()));
			m_data->ents.Find<Entity>("E_0Text2")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text3")->GetComponent<TextComponent>("C_Text3")->GetText().setString("DMG: " + std::to_string(m_data->gm.hKnight->GetDmg())+" ("+ std::to_string(m_data->gm.hKnight->GetCrit()) +" % crit)");
			m_data->ents.Find<Entity>("E_0Text3")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text4")->GetComponent<TextComponent>("C_Text4")->GetText().setString("ARM: " + std::to_string(m_data->gm.hKnight->GetArmour())+"  Dodge: " + std::to_string(m_data->gm.hKnight->GetDodge()));
			m_data->ents.Find<Entity>("E_0Text4")->SetVisible(true);

			
		}

		if (lastClicked == "rouge")
		{
			m_data->ents.Find<Entity>("E_0Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("HP: " + std::to_string(m_data->gm.hRogue->GetHealth()) + "/" + std::to_string(m_data->gm.hRogue->GetMaxHealth()));
			m_data->ents.Find<Entity>("E_0Text")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text2")->GetComponent<TextComponent>("C_Text2")->GetText().setString(" MN: " + std::to_string(m_data->gm.hRogue->GetMana()) + "/" + std::to_string(m_data->gm.hRogue->GetMaxMana()));
			m_data->ents.Find<Entity>("E_0Text2")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text3")->GetComponent<TextComponent>("C_Text3")->GetText().setString("DMG: " + std::to_string(m_data->gm.hRogue->GetDmg()) + " (" + std::to_string(m_data->gm.hRogue->GetCrit()) + " % crit)");
			m_data->ents.Find<Entity>("E_0Text3")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text4")->GetComponent<TextComponent>("C_Text4")->GetText().setString("ARM: " + std::to_string(m_data->gm.hRogue->GetArmour()) + "  Dodge: " + std::to_string(m_data->gm.hRogue->GetDodge()));
			m_data->ents.Find<Entity>("E_0Text4")->SetVisible(true);
		}

		if (lastClicked == "bard")
		{
			m_data->ents.Find<Entity>("E_0Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("HP: " + std::to_string(m_data->gm.hBard->GetHealth()) + "/" + std::to_string(m_data->gm.hBard->GetMaxHealth()));
			m_data->ents.Find<Entity>("E_0Text")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text2")->GetComponent<TextComponent>("C_Text2")->GetText().setString(" MN: " + std::to_string(m_data->gm.hBard->GetMana()) + "/" + std::to_string(m_data->gm.hBard->GetMaxMana()));
			m_data->ents.Find<Entity>("E_0Text2")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text3")->GetComponent<TextComponent>("C_Text3")->GetText().setString("DMG: " + std::to_string(m_data->gm.hBard->GetDmg()) + " (" + std::to_string(m_data->gm.hBard->GetCrit()) + " % crit)");
			m_data->ents.Find<Entity>("E_0Text3")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text4")->GetComponent<TextComponent>("C_Text4")->GetText().setString("ARM: " + std::to_string(m_data->gm.hBard->GetArmour()) + "  Dodge: " + std::to_string(m_data->gm.hBard->GetDodge()));
			m_data->ents.Find<Entity>("E_0Text4")->SetVisible(true);
		}

		if (lastClicked == "sorc")
		{
			m_data->ents.Find<Entity>("E_0Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("HP: " + std::to_string(m_data->gm.hSorceress->GetHealth()) + "/" + std::to_string(m_data->gm.hSorceress->GetMaxHealth()));
			m_data->ents.Find<Entity>("E_0Text")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text2")->GetComponent<TextComponent>("C_Text2")->GetText().setString(" MN: " + std::to_string(m_data->gm.hSorceress->GetMana()) + "/" + std::to_string(m_data->gm.hSorceress->GetMaxMana()));
			m_data->ents.Find<Entity>("E_0Text2")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text3")->GetComponent<TextComponent>("C_Text3")->GetText().setString("DMG: " + std::to_string(m_data->gm.hSorceress->GetDmg()) + " (" + std::to_string(m_data->gm.hSorceress->GetCrit()) + " % crit)");
			m_data->ents.Find<Entity>("E_0Text3")->SetVisible(true);

			m_data->ents.Find<Entity>("E_0Text4")->GetComponent<TextComponent>("C_Text4")->GetText().setString("ARM: " + std::to_string(m_data->gm.hSorceress->GetArmour()) + "  Dodge: " + std::to_string(m_data->gm.hSorceress->GetDodge()));
			m_data->ents.Find<Entity>("E_0Text4")->SetVisible(true);
		}

		
	}

	void MapScene::AddEntity(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}
}