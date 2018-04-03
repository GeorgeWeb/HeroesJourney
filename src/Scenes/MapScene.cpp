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
		m_data->assets.LoadTexture("Tex_Health", HP_POT_ICON);
		m_data->assets.LoadTexture("Tex_Mana", MANA_POT_ICON);
		m_data->assets.LoadTexture("Tex_Coin", COIN_ICON);

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
		knightIcon->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.04f, SCREEN_HEIGHT * 0.73f));
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
		sorcIcon->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.16f, SCREEN_HEIGHT * 0.73f));
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
		// clickable comp
		auto m_encounterPopupFight = m_encounterPopup->AddComponent<ClickableComponent>("C_xPopupFightBtn");
		m_encounterPopupFight->SetSpriteTarget(m_encounterPopup->GetComponent<SpriteComponent>("C_xPopupPlayBtnSprite"));
		auto m_encounterPopupClose = m_encounterPopup->AddComponent<ClickableComponent>("C_xPopupCloseBtnBtn");
		m_encounterPopupClose->SetSpriteTarget(m_encounterPopup->GetComponent<SpriteComponent>("C_xPopupCloseBtnSprite"));
		
		//Texts for the charachter UI
		// Text
		auto text = std::make_shared<Entity>();
		auto infTextFont = text->AddComponent<TextComponent>("C_Text");
		// define
		infTextFont->SetFont(m_data->assets.GetFont("Font_Pixel"));
		infTextFont->GetText().setCharacterSize(12);
		text->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.26f, SCREEN_HEIGHT * 0.75f));
		// properties
		text->showOnCreate = false;
		text->SetVisible(false);
		text->SetAlive(true);
		text->Init();

		// Text 2
		auto text2 = std::make_shared<Entity>();
		auto infTextFont2 = text2->AddComponent<TextComponent>("C_Text2");
		// define
		infTextFont2->SetFont(m_data->assets.GetFont("Font_Pixel"));
		infTextFont2->GetText().setCharacterSize(12);
		text2->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.26f, SCREEN_HEIGHT * 0.80f));
		// properties
		text2->showOnCreate = false;
		text2->SetVisible(false);
		text2->SetAlive(true);
		text2->Init();

		// Text 3
		auto text3 = std::make_shared<Entity>();
		auto infTextFont3 = text3->AddComponent<TextComponent>("C_Text3");
		// define
		infTextFont3->SetFont(m_data->assets.GetFont("Font_Pixel"));
		infTextFont3->GetText().setCharacterSize(12);
		text3->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.26f, SCREEN_HEIGHT * 0.87f));
		// properties
		text3->showOnCreate = false;
		text3->SetVisible(false);
		text3->SetAlive(true);
		text3->Init();

		// Text 4
		auto text4 = std::make_shared<Entity>();
		auto infTextFont4 = text4->AddComponent<TextComponent>("C_Text4");
		// define
		infTextFont4->SetFont(m_data->assets.GetFont("Font_Pixel"));
		infTextFont4->GetText().setCharacterSize(12);
		text4->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.26f, SCREEN_HEIGHT * 0.92f));
		// properties
		text4->showOnCreate = false;
		text4->SetVisible(false);
		text4->SetAlive(true);
		text4->Init();
		
		//Resource visualization
		//Health potion sprite
		auto health = std::make_shared<Entity>();
		auto healthSprite = health->AddComponent<SpriteComponent>("C_Health");
		//sprite define
		healthSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Health"));
		healthSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		health->SetPosition(sf::Vector2f(SCREEN_WIDTH *0.02f,  SCREEN_HEIGHT * 0.65f));
		//properties
		health->SetVisible(true);
		health->SetAlive(true);

		// Text for health
		auto textHp = std::make_shared<Entity>();
		auto hpTextFont = textHp->AddComponent<TextComponent>("C_HpText");
		// define
		hpTextFont->SetFont(m_data->assets.GetFont("Font_Pixel"));
		hpTextFont->GetText().setCharacterSize(14);
		textHp->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.04f, SCREEN_HEIGHT * 0.67f));
		// properties
		textHp->showOnCreate = true;
		textHp->SetVisible(true);
		textHp->SetAlive(true);
		textHp->Init();
		hpTextFont->GetText().setCharacterSize(10);

		//Mana potion sprite
		auto mana = std::make_shared<Entity>();
		auto manaSprite = mana->AddComponent<SpriteComponent>("C_Mana");
		//sprite define
		manaSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Mana"));
		manaSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		mana->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.07f, SCREEN_HEIGHT * 0.65f));
		//properties
		mana->SetVisible(true);
		mana->SetAlive(true);

		// Text for mana
		auto textMn = std::make_shared<Entity>();
		auto mnTextFont = textMn->AddComponent<TextComponent>("C_MnText");
		// define
		mnTextFont->SetFont(m_data->assets.GetFont("Font_Pixel"));
		mnTextFont->GetText().setCharacterSize(14);
		textMn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.09f, SCREEN_HEIGHT * 0.67f));
		// properties
		textMn->showOnCreate = true;
		textMn->SetVisible(true);
		textMn->SetAlive(true);
		textMn->Init();
		mnTextFont->GetText().setCharacterSize(10);

		//Coin sprite
		auto coin = std::make_shared<Entity>();
		auto coinSprite = coin->AddComponent<SpriteComponent>("C_Coin");
		//sprite define
		coinSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Coin"));
		coinSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		coin->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.12f, SCREEN_HEIGHT * 0.66f));
		//properties
		coin->SetVisible(true);
		coin->SetAlive(true);

		// Text for coin
		auto textCoin = std::make_shared<Entity>();
		auto coinTextFont = textCoin->AddComponent<TextComponent>("C_CoinText");
		// define
		coinTextFont->SetFont(m_data->assets.GetFont("Font_Pixel"));
		coinTextFont->GetText().setCharacterSize(14);
		textCoin->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.67f));
		// properties
		textCoin->showOnCreate = true;
		textCoin->SetVisible(true);
		textCoin->SetAlive(true);
		textCoin->Init();
		coinTextFont->GetText().setCharacterSize(10);

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
		AddEntity("E_0Health", health);
		AddEntity("E_0Mana", mana);
		AddEntity("E_0Coin", coin);
		AddEntity("E_0HpText", textHp);
		AddEntity("E_0MnText", textMn);
		AddEntity("E_0CoinText", textCoin);

		// If you wanna re-use an entity from another scene that already exists in the global ents. mngr.
		//m_data->ents.Find<AnimatedLogo>("E_GameLogo")->Init();
		//AddEntity("E_GameLogo", m_data->ents.GetSharedEntity("E_GameLogo"));
	}

	void MapScene::HandleInput()
	{
		#pragma region Ents & Comps to for checks
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
		auto text = m_data->ents.Find<Entity>("E_0Text");
		auto text2 = m_data->ents.Find<Entity>("E_0Text2");
		auto text3 = m_data->ents.Find<Entity>("E_0Text3");
		auto text4 = m_data->ents.Find<Entity>("E_0Text4");
		auto fightBtn = m_data->ents.Find<Entity>("E_aEncounterPopup")->GetComponent<ClickableComponent>("C_xPopupFightBtn");
		auto closeBtn = m_data->ents.Find<Entity>("E_aEncounterPopup")->GetComponent<ClickableComponent>("C_xPopupCloseBtnBtn");
		auto fightComp = m_data->ents.Find<Entity>("E_aEncounterPopup")->GetComponent<SpriteComponent>("C_xPopupPlayBtnSprite");
		auto closeComp = m_data->ents.Find<Entity>("E_aEncounterPopup")->GetComponent<SpriteComponent>("C_xPopupCloseBtnSprite");
		auto healthComp = m_data->ents.Find<Entity>("E_0Health")->GetComponent<SpriteComponent>("C_Health");
		auto manaComp = m_data->ents.Find<Entity>("E_0Mana")->GetComponent<SpriteComponent>("C_Mana");
		auto coinComp = m_data->ents.Find<Entity>("E_0Coin")->GetComponent<SpriteComponent>("C_Coin");
		auto hpTextComp = m_data->ents.Find<Entity>("E_0HpText");
		auto mnTextComp = m_data->ents.Find<Entity>("E_0MnText");
		auto coinTextComp = m_data->ents.Find<Entity>("E_0CoinText");
		#pragma endregion

		std::vector<Entity*> entsVisibile({ text, text2, text3, text4, hpTextComp, mnTextComp, coinTextComp });
		std::vector<SpriteComponent*> compsVisibile({ frameComp, castleComp, forestComp, mountainsComp, seaComp,
			evilCastleComp, knightComp, sorcComp, rogueComp, bardComp, healthComp, healthComp, manaComp, coinComp });
		std::vector<SpriteComponent*> compsClickable({ castleComp, frameComp, forestComp, mountainsComp, seaComp,
			evilCastleComp, knightComp, sorcComp, rogueComp, bardComp });

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
					// Change the textures of the popup based on the actual Encounter we're in.
					// TODO: ...

					// Show the encounter popup
					m_encounterPopup->SetVisible(true);
					m_encounterPopup->SetAlive(true);

					// turn closing check on
					m_encounterPopup->ToggleButtonsBehaviour();

					// Fade Entities/Components
					HideEntsOnDisplay(entsVisibile, compsVisibile, compsClickable);
				});

				// SET CLOSING BEHAVIOUR
				m_encounterPopup->OnClose = [=]()
				{
					// Hide the encounter popup
					m_encounterPopup->SetVisible(false);
					m_encounterPopup->SetAlive(false);

					// turn closing check off
					m_encounterPopup->ToggleButtonsBehaviour();

					// Unfade Entities/Components
					ShowEntsOnClose(entsVisibile, compsVisibile, compsClickable);
				};

				// SET PLAY CLICKED BEHAVIOUR
				m_encounterPopup->OnPlay = [=]()
				{
					// TODO: Play logic.
					std::cout << "Clicked Play!!!\n";
				};
			}

			//check for mountains click
			if (mountainsComp->IsClickable() && m_data->input.isClicked(mountainsComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				mountainsBtn->SetClicked(true);

				// SET CREATION BEHAVIOUR
				m_encounterPopup->OnDisplay([=]()
				{
					// Change the textures of the popup based on the actual Encounter we're in.
					// TODO: ...

					// Show the encounter popup
					m_encounterPopup->SetVisible(true);
					m_encounterPopup->SetAlive(true);

					// turn closing check on
					m_encounterPopup->ToggleButtonsBehaviour();
					
					// Fade Entities/Components
					HideEntsOnDisplay(entsVisibile, compsVisibile, compsClickable);
				});

				// SET CLOSING BEHAVIOUR
				m_encounterPopup->OnClose = [=]()
				{
					// Hide the encounter popup
					m_encounterPopup->SetVisible(false);
					m_encounterPopup->SetAlive(false);

					// turn closing check off
					m_encounterPopup->ToggleButtonsBehaviour();

					// Unfade Entities/Components
					ShowEntsOnClose(entsVisibile, compsVisibile, compsClickable);
				};

				// SET PLAY CLICKED BEHAVIOUR
				m_encounterPopup->OnPlay = [=]()
				{
					// TODO: Play logic.
					std::cout << "Clicked Play!!!\n";
				};
			}

			//check for sea click
			if (seaComp->IsClickable() && m_data->input.isClicked(seaComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				seaBtn->SetClicked(true);
				// SET CREATION BEHAVIOUR
				m_encounterPopup->OnDisplay([=]()
				{
					// Change the textures of the popup based on the actual Encounter we're in.
					// TODO: ...

					// Show the encounter popup
					m_encounterPopup->SetVisible(true);
					m_encounterPopup->SetAlive(true);

					// turn closing check on
					m_encounterPopup->ToggleButtonsBehaviour();

					// Fade Entities/Components
					HideEntsOnDisplay(entsVisibile, compsVisibile, compsClickable);
				});

				// SET CLOSING BEHAVIOUR
				m_encounterPopup->OnClose = [=]()
				{
					// Hide the encounter popup
					m_encounterPopup->SetVisible(false);
					m_encounterPopup->SetAlive(false);

					// turn closing check off
					m_encounterPopup->ToggleButtonsBehaviour();

					// Unfade Entities/Components
					ShowEntsOnClose(entsVisibile, compsVisibile, compsClickable);
				};

				// SET PLAY CLICKED BEHAVIOUR
				m_encounterPopup->OnPlay = [=]()
				{
					// TODO: Play logic.
					std::cout << "Clicked Play!!!\n";
				};
			}

			//check for evil castle click
			if (evilCastleComp->IsClickable() && m_data->input.isClicked(evilCastleComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				evilCastleBtn->SetClicked(true);
				// SET CREATION BEHAVIOUR
				m_encounterPopup->OnDisplay([=]()
				{
					// Change the textures of the popup based on the actual Encounter we're in.
					// TODO: ...

					// Show the encounter popup
					m_encounterPopup->SetVisible(true);
					m_encounterPopup->SetAlive(true);

					// turn closing check on
					m_encounterPopup->ToggleButtonsBehaviour();

					// Fade Entities/Components
					HideEntsOnDisplay(entsVisibile, compsVisibile, compsClickable);
				});

				// SET CLOSING BEHAVIOUR
				m_encounterPopup->OnClose = [=]()
				{
					// Hide the encounter popup
					m_encounterPopup->SetVisible(false);
					m_encounterPopup->SetAlive(false);

					// turn closing check off
					m_encounterPopup->ToggleButtonsBehaviour();

					// Unfade Entities/Components
					ShowEntsOnClose(entsVisibile, compsVisibile, compsClickable);
				};

				// SET PLAY CLICKED BEHAVIOUR
				m_encounterPopup->OnPlay = [=]()
				{
					// TODO: Play logic.
					std::cout << "Clicked Play!!!\n";
				};
			}

			if (knightComp->IsClickable() && m_data->input.isClicked(knightComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				knightBtn->SetClicked(true);

				lastClicked = "knight";
				m_data->ents.Find<Entity>("E_0Text4")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text3")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text2")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text")->SetVisible(true);
			}

			if (rogueComp->IsClickable() && m_data->input.isClicked(rogueComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				rogueBtn->SetClicked(true);

				lastClicked = "rogue";
				m_data->ents.Find<Entity>("E_0Text4")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text3")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text2")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text")->SetVisible(true);
			}

			if (bardComp->IsClickable() && m_data->input.isClicked(bardComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				bardBtn->SetClicked(true);

				lastClicked = "bard";
				m_data->ents.Find<Entity>("E_0Text4")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text3")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text2")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text")->SetVisible(true);
			}

			if (sorcComp->IsClickable() && m_data->input.isClicked(sorcComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				sorcBtn->SetClicked(true);

				lastClicked = "sorc";
				m_data->ents.Find<Entity>("E_0Text4")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text3")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text2")->SetVisible(true);
				m_data->ents.Find<Entity>("E_0Text")->SetVisible(true);
			}
		}
	}

	void MapScene::Update(float t_delatTime)
	{
		//update hero stat
		UpdateText();
		
		//update resources
		UpdateResources();

		auto castleBtn = m_data->ents.Find<Entity>("E_Castle")->GetComponent<ClickableComponent>("C_CastleBtn");
		auto forestBtn = m_data->ents.Find<Entity>("E_Forest")->GetComponent<ClickableComponent>("C_ForestBtn");
		auto mountainsBtn = m_data->ents.Find<Entity>("E_Mountains")->GetComponent<ClickableComponent>("C_MountainsBtn");
		auto seaBtn = m_data->ents.Find<Entity>("E_Sea")->GetComponent<ClickableComponent>("C_SeaBtn");
		auto evilCastleBtn = m_data->ents.Find<Entity>("E_EvilCastle")->GetComponent<ClickableComponent>("C_EvilCastleBtn");
		auto knightBtn = m_data->ents.Find<Entity>("E_0KnightIcon")->GetComponent<ClickableComponent>("C_KnightIconBtn");
		auto sorcBtn = m_data->ents.Find<Entity>("E_0SorcIcon")->GetComponent<ClickableComponent>("C_SorcIconBtn");
		auto rogueBtn = m_data->ents.Find<Entity>("E_0RogueIcon")->GetComponent<ClickableComponent>("C_RougeIconBtn");
		auto bardBtn = m_data->ents.Find<Entity>("E_0BardIcon")->GetComponent<ClickableComponent>("C_BardIconBtn");
		auto fightBtn = m_data->ents.Find<Entity>("E_aEncounterPopup")->GetComponent<ClickableComponent>("C_xPopupFightBtn");
		auto closeBtn = m_data->ents.Find<Entity>("E_aEncounterPopup")->GetComponent<ClickableComponent>("C_xPopupCloseBtnBtn");

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
			m_data->ents.Find<Entity>("E_0Text2")->GetComponent<TextComponent>("C_Text2")->GetText().setString(" MN: " + std::to_string(m_data->gm.hKnight->GetMana()) + "/" + std::to_string(m_data->gm.hKnight->GetMaxMana()));
			m_data->ents.Find<Entity>("E_0Text3")->GetComponent<TextComponent>("C_Text3")->GetText().setString("DMG: " + std::to_string(m_data->gm.hKnight->GetDmg())+" ("+ std::to_string(m_data->gm.hKnight->GetCrit()) +" % crit)");
			m_data->ents.Find<Entity>("E_0Text4")->GetComponent<TextComponent>("C_Text4")->GetText().setString("ARM: " + std::to_string(m_data->gm.hKnight->GetArmour())+"  Dodge: " + std::to_string(m_data->gm.hKnight->GetDodge()));
		}

		if (lastClicked == "rogue")
		{
			m_data->ents.Find<Entity>("E_0Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("HP: " + std::to_string(m_data->gm.hRogue->GetHealth()) + "/" + std::to_string(m_data->gm.hRogue->GetMaxHealth()));
			m_data->ents.Find<Entity>("E_0Text2")->GetComponent<TextComponent>("C_Text2")->GetText().setString(" MN: " + std::to_string(m_data->gm.hRogue->GetMana()) + "/" + std::to_string(m_data->gm.hRogue->GetMaxMana()));
			m_data->ents.Find<Entity>("E_0Text3")->GetComponent<TextComponent>("C_Text3")->GetText().setString("DMG: " + std::to_string(m_data->gm.hRogue->GetDmg()) + " (" + std::to_string(m_data->gm.hRogue->GetCrit()) + " % crit)");
			m_data->ents.Find<Entity>("E_0Text4")->GetComponent<TextComponent>("C_Text4")->GetText().setString("ARM: " + std::to_string(m_data->gm.hRogue->GetArmour()) + "  Dodge: " + std::to_string(m_data->gm.hRogue->GetDodge()));
		}

		if (lastClicked == "bard")
		{
			m_data->ents.Find<Entity>("E_0Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("HP: " + std::to_string(m_data->gm.hBard->GetHealth()) + "/" + std::to_string(m_data->gm.hBard->GetMaxHealth()));
			m_data->ents.Find<Entity>("E_0Text2")->GetComponent<TextComponent>("C_Text2")->GetText().setString(" MN: " + std::to_string(m_data->gm.hBard->GetMana()) + "/" + std::to_string(m_data->gm.hBard->GetMaxMana()));
			m_data->ents.Find<Entity>("E_0Text3")->GetComponent<TextComponent>("C_Text3")->GetText().setString("DMG: " + std::to_string(m_data->gm.hBard->GetDmg()) + " (" + std::to_string(m_data->gm.hBard->GetCrit()) + " % crit)");
			m_data->ents.Find<Entity>("E_0Text4")->GetComponent<TextComponent>("C_Text4")->GetText().setString("ARM: " + std::to_string(m_data->gm.hBard->GetArmour()) + "  Dodge: " + std::to_string(m_data->gm.hBard->GetDodge()));
		}

		if (lastClicked == "sorc")
		{
			m_data->ents.Find<Entity>("E_0Text")->GetComponent<TextComponent>("C_Text")->GetText().setString("HP: " + std::to_string(m_data->gm.hSorceress->GetHealth()) + "/" + std::to_string(m_data->gm.hSorceress->GetMaxHealth()));
			m_data->ents.Find<Entity>("E_0Text2")->GetComponent<TextComponent>("C_Text2")->GetText().setString(" MN: " + std::to_string(m_data->gm.hSorceress->GetMana()) + "/" + std::to_string(m_data->gm.hSorceress->GetMaxMana()));
			m_data->ents.Find<Entity>("E_0Text3")->GetComponent<TextComponent>("C_Text3")->GetText().setString("DMG: " + std::to_string(m_data->gm.hSorceress->GetDmg()) + " (" + std::to_string(m_data->gm.hSorceress->GetCrit()) + " % crit)");
			m_data->ents.Find<Entity>("E_0Text4")->GetComponent<TextComponent>("C_Text4")->GetText().setString("ARM: " + std::to_string(m_data->gm.hSorceress->GetArmour()) + "  Dodge: " + std::to_string(m_data->gm.hSorceress->GetDodge()));
		}
	}

	void MapScene::UpdateResources()
	{
		m_data->ents.Find<Entity>("E_0HpText")->GetComponent<TextComponent>("C_HpText")->GetText().setString("X " + std::to_string(m_data->gm.healthPot));
		m_data->ents.Find<Entity>("E_0MnText")->GetComponent<TextComponent>("C_MnText")->GetText().setString("X " + std::to_string(m_data->gm.manaPot));
		m_data->ents.Find<Entity>("E_0CoinText")->GetComponent<TextComponent>("C_CoinText")->GetText().setString("X " + std::to_string(m_data->gm.gold));	
	}

	void MapScene::HideEntsOnDisplay(std::vector<Entity*> t_entsToHide, std::vector<SpriteComponent*> t_compsToFade, std::vector<SpriteComponent*> t_compsToBlock)
	{
		auto bgComp = m_data->ents.Find<Entity>("E_zMapBG")->GetComponent<SpriteComponent>("C_MapBGSprite");
		bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 100.0f));
	
		for (auto& ent : t_entsToHide)
			ent->SetVisible(false);

		for (auto& cmpToFade : t_compsToFade)
			cmpToFade->GetSprite().setColor(sf::Color(cmpToFade->GetSprite().getColor().r, cmpToFade->GetSprite().getColor().g, cmpToFade->GetSprite().getColor().b, 10.0f));

		for (auto& cmpToBlock : t_compsToBlock)
			cmpToBlock->SetClickable(false);
	}

	void MapScene::ShowEntsOnClose(std::vector<Entity*> t_entsToShow, std::vector<SpriteComponent*> t_compsToUnfade, std::vector<SpriteComponent*> t_compsToUnblock)
	{
		auto bgComp = m_data->ents.Find<Entity>("E_zMapBG")->GetComponent<SpriteComponent>("C_MapBGSprite");
		bgComp->GetSprite().setColor(sf::Color(bgComp->GetSprite().getColor().r, bgComp->GetSprite().getColor().g, bgComp->GetSprite().getColor().b, 255.0f));

		for (auto& ent : t_entsToShow)
			ent->SetVisible(true);

		for (auto& cmpToFade : t_compsToUnfade)
			cmpToFade->GetSprite().setColor(sf::Color(cmpToFade->GetSprite().getColor().r, cmpToFade->GetSprite().getColor().g, cmpToFade->GetSprite().getColor().b, 255.0f));

		for (auto& cmpToBlock : t_compsToUnblock)
			cmpToBlock->SetClickable(true);
	}

	void MapScene::AddEntity(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}
}