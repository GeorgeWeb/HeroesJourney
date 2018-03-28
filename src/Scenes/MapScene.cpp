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
	{ }

	void MapScene::Init()
	{
		// SET VIEWPORT TO THE MOST RECENT SCALE OFFSETS AND RESIZE WINDOW
		if ((float)Engine2D::GetWin().getSize().x > 1366.f && (float)Engine2D::GetWin().getSize().y > 768.f)
		{
			std::cout << "AM BIGGER\n";
			m_view.setViewport(sf::FloatRect(0.0f, 0.0f, 0.88f, 1.0f));
			m_view.reset(sf::FloatRect(0.0f, 0.0f, (float)Engine2D::GetWin().getSize().x, (float)Engine2D::GetWin().getSize().y));
			Engine2D::GetWin().setSize(sf::Vector2u(m_view.getSize()));
		}
		else
		{
			std::cout << "Am not bigger\n";
			m_view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
			m_view.reset(sf::FloatRect(0.0f, 0.0f, (float)Engine2D::GetWin().getSize().x, (float)Engine2D::GetWin().getSize().y));
			Engine2D::GetWin().setSize(sf::Vector2u(m_view.getSize()));
		}

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

		m_view.reset(sf::FloatRect(0.0f, 0.0f, (float)Engine2D::GetWin().getSize().x, (float)Engine2D::GetWin().getSize().y));

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
		castle->SetPosition(sf::Vector2f((Engine2D::GetWinSize().x - castleSprite->GetSprite().getGlobalBounds().width) * 0.1f,
			(Engine2D::GetWinSize().y - castleSprite->GetSprite().getGlobalBounds().height) * 0.3f));
		castle->SetVisible(true);
		castle->SetAlive(true);

		//Forest
		auto forest = std::make_shared<ECM::Entity>();
		auto forestSprite = forest->AddComponent<SpriteComponent>("C_ForestSprite");
		//define castle sprite
		forestSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Forest"));
		forestSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		forest->SetPosition(sf::Vector2f((Engine2D::GetWinSize().x - castleSprite->GetSprite().getGlobalBounds().width) * 0.35f,
			(Engine2D::GetWinSize().y - castleSprite->GetSprite().getGlobalBounds().height) * 0.5f));
		forest->SetVisible(true);
		forest->SetAlive(true);
		
		//Mountains
		auto mountains = std::make_shared<ECM::Entity>();
		auto mountainsSprite = mountains->AddComponent<SpriteComponent>("C_MountainsSprite");
		//define castle sprite
		mountainsSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Mountains"));
		mountainsSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		mountains->SetPosition(sf::Vector2f((Engine2D::GetWinSize().x - mountainsSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(Engine2D::GetWinSize().y - mountainsSprite->GetSprite().getGlobalBounds().height) * 0.8f));
		mountains->SetVisible(true);
		mountains->SetAlive(true);

		//Sea
		auto sea = std::make_shared<ECM::Entity>();
		auto seaSprite = sea->AddComponent<SpriteComponent>("C_SeaSprite");
		//define castle sprite
		seaSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Sea"));
		seaSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		sea->SetPosition(sf::Vector2f((Engine2D::GetWinSize().x - seaSprite->GetSprite().getGlobalBounds().width) * 0.95f,
			(Engine2D::GetWinSize().y - seaSprite->GetSprite().getGlobalBounds().height) * 0.9f));
		sea->SetVisible(true);
		sea->SetAlive(true);

		//Evil Castle
		auto evilCastle = std::make_shared<ECM::Entity>();
		auto evilCastleSprite = evilCastle->AddComponent<SpriteComponent>("C_EvilCastleSprite");
		//define castle sprite
		evilCastleSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_EvilCastle"));
		evilCastleSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		evilCastle->SetPosition(sf::Vector2f((Engine2D::GetWinSize().x - evilCastleSprite->GetSprite().getGlobalBounds().width) * 0.7f,
			(Engine2D::GetWinSize().y - evilCastleSprite->GetSprite().getGlobalBounds().height) * 0.2f));
		evilCastle->SetVisible(true);
		evilCastle->SetAlive(true);

		//UI frame
		auto frame = std::make_shared<ECM::Entity>();
		auto frameSprite = frame->AddComponent<SpriteComponent>("C_FrameSprite");
		//define castle sprite
		frameSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Frame"));
		frameSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//castle properties
		frameSprite->GetSprite().scale(0.9f, 0.9f);
		frame->SetPosition(sf::Vector2f((Engine2D::GetWinSize().x - frameSprite->GetSprite().getGlobalBounds().width * 2.4f),
			(Engine2D::GetWinSize().y - frameSprite->GetSprite().getGlobalBounds().height)));
		frame->SetVisible(true);
		frame->SetAlive(true);

		// init the encounter popup
		m_encounterPopup = std::make_shared<EncounterPopup>();
		m_encounterPopup->GetComponent<SpriteComponent>("C_zPopupBGSprite")->GetSprite().scale(1.0f, 1.0f);
		// set components
		m_encounterPopup->SetBackgroundImage(m_data->assets.GetTexture("Tex_PopupBG"));
		m_encounterPopup->SetCloseButtonImage(m_data->assets.GetTexture("Tex_PopupCloseBtn"));
		m_encounterPopup->SetPlayButtonImage(m_data->assets.GetTexture("Tex_PopupPlayBtn"));
		m_encounterPopup->SetOpponentImage(m_data->assets.GetTexture("Tex_PopupOpponent"));
		m_encounterPopup->SetStoryImage(m_data->assets.GetTexture("Tex_PopupStory"));
		m_encounterPopup->SetTitleText("ENCOUNTER #?" , m_data->assets.GetFont("Font_Pixel"));
		// position
		m_encounterPopup->SetPosition(sf::Vector2f(
			(Engine2D::GetWinSize().x - m_encounterPopup->GetComponent<SpriteComponent>("C_zPopupBGSprite")->GetSprite().getGlobalBounds().width) * 0.5f,
			(Engine2D::GetWinSize().y - m_encounterPopup->GetComponent<SpriteComponent>("C_zPopupBGSprite")->GetSprite().getGlobalBounds().height) * 0.5f
		));
		m_encounterPopup->Init();
		m_encounterPopup->Assemble(m_encounterPopup->GetPosition());

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! "z" for background "x" for UI
		AddEntity("E_zMapBG", bg);
		AddEntity("E_Castle", castle);
		AddEntity("E_Forest", forest);
		AddEntity("E_Mountains", mountains);
		AddEntity("E_Sea", sea);
		AddEntity("E_EvilCastle", evilCastle);
		AddEntity("E_xFrame", frame);
		AddEntity("E_aEncounterPopup", m_encounterPopup);
		
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
		auto forestComp = m_data->ents.Find<Entity>("E_Forest")->GetComponent<SpriteComponent>("C_ForestSprite");
		auto mountainsComp = m_data->ents.Find<Entity>("E_Mountains")->GetComponent<SpriteComponent>("C_MountainsSprite");
		auto seaComp = m_data->ents.Find<Entity>("E_Sea")->GetComponent<SpriteComponent>("C_SeaSprite");
		auto evilCastleComp = m_data->ents.Find<Entity>("E_EvilCastle")->GetComponent<SpriteComponent>("C_EvilCastleSprite");

		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView();

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
				m_castleClick = true;
			}
			
			//check for forest click
			if (forestComp->IsClickable() && m_data->input.isClicked(forestComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				m_forestClick = true;
				
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
					
					// Make Entities Unclickable
					castleComp->SetClickable(false);
					frameComp->SetClickable(false);
					forestComp->SetClickable(false);
					mountainsComp->SetClickable(false);
					seaComp->SetClickable(false);
					evilCastleComp->SetClickable(false);
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

					// Make Entities Clickable
					castleComp->SetClickable(true);
					frameComp->SetClickable(true);
					forestComp->SetClickable(true);
					mountainsComp->SetClickable(true);
					seaComp->SetClickable(true);
					evilCastleComp->SetClickable(true);
				};
			}

			//check for mountains click
			if (mountainsComp->IsClickable() && m_data->input.isClicked(mountainsComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				m_mountainsClick = true;

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

					// Make Entities Unclickable
					castleComp->SetClickable(false);
					frameComp->SetClickable(false);
					forestComp->SetClickable(false);
					mountainsComp->SetClickable(false);
					seaComp->SetClickable(false);
					evilCastleComp->SetClickable(false);
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

					// Make Entities Clickable
					castleComp->SetClickable(true);
					frameComp->SetClickable(true);
					forestComp->SetClickable(true);
					mountainsComp->SetClickable(true);
					seaComp->SetClickable(true);
					evilCastleComp->SetClickable(true);
				};
			}

			//check for sea click
			if (seaComp->IsClickable() && m_data->input.isClicked(seaComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				m_seaClick = true;

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

					// Make Entities Unclickable
					castleComp->SetClickable(false);
					frameComp->SetClickable(false);
					forestComp->SetClickable(false);
					mountainsComp->SetClickable(false);
					seaComp->SetClickable(false);
					evilCastleComp->SetClickable(false);
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

					// Make Entities Clickable
					castleComp->SetClickable(true);
					frameComp->SetClickable(true);
					forestComp->SetClickable(true);
					mountainsComp->SetClickable(true);
					seaComp->SetClickable(true);
					evilCastleComp->SetClickable(true);
				};
			}

			//check for evil castle click
			if (evilCastleComp->IsClickable() && m_data->input.isClicked(evilCastleComp->GetSprite(), sf::Mouse::Left, Engine2D::GetWin()))
			{
				m_evilCastleClick = true;

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

					// Make Entities Unclickable
					castleComp->SetClickable(false);
					frameComp->SetClickable(false);
					forestComp->SetClickable(false);
					mountainsComp->SetClickable(false);
					seaComp->SetClickable(false);
					evilCastleComp->SetClickable(false);
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

					// Make Entities Clickable
					castleComp->SetClickable(true);
					frameComp->SetClickable(true);
					forestComp->SetClickable(true);
					mountainsComp->SetClickable(true);
					seaComp->SetClickable(true);
					evilCastleComp->SetClickable(true);
				};
			}
		}
	}

	void MapScene::Update(float t_delatTime)
	{
		auto castleComp = m_data->ents.Find<Entity>("E_Castle")->GetComponent<SpriteComponent>("C_CastleSprite");
		auto forestComp = m_data->ents.Find<Entity>("E_Forest")->GetComponent<SpriteComponent>("C_ForestSprite");
		auto mountainsComp = m_data->ents.Find<Entity>("E_Mountains")->GetComponent<SpriteComponent>("C_MountainsSprite");
		auto seaComp = m_data->ents.Find<Entity>("E_Sea")->GetComponent<SpriteComponent>("C_SeaSprite");
		auto evilCastleComp = m_data->ents.Find<Entity>("E_EvilCastle")->GetComponent<SpriteComponent>("C_EvilCastleSprite");

		//show if castle is clicked
		if (m_castleClick)
		{
			castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r - 100,
				castleComp->GetSprite().getColor().g - 100,
				castleComp->GetSprite().getColor().b - 100,
				castleComp->GetSprite().getColor().a));
			
			m_castleClick = false;
			m_castleUnClick = true;
		}

		//show if forest is clicked
		if (m_forestClick)
		{
			forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r - 100,
				forestComp->GetSprite().getColor().g - 100,
				forestComp->GetSprite().getColor().b - 100,
				forestComp->GetSprite().getColor().a));

			m_forestClick = false;
			m_forestUnClick = true;
		}

		//show if mountains are clicked
		if (m_mountainsClick)
		{
			mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r - 100,
				mountainsComp->GetSprite().getColor().g - 100,
				mountainsComp->GetSprite().getColor().b - 100,
				mountainsComp->GetSprite().getColor().a));

			m_mountainsClick = false;
			m_mountainsUnClick = true;
		}

		//show if sea are clicked
		if (m_seaClick)
		{
			seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r - 100,
				seaComp->GetSprite().getColor().g - 100,
				seaComp->GetSprite().getColor().b - 100,
				seaComp->GetSprite().getColor().a));

			m_seaClick = false;
			m_seaUnClick = true;
		}

		//show if sea are clicked
		if (m_evilCastleClick)
		{
			evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r - 100,
				evilCastleComp->GetSprite().getColor().g - 100,
				evilCastleComp->GetSprite().getColor().b - 100,
				evilCastleComp->GetSprite().getColor().a));

			m_evilCastleClick = false;
			m_evilCastleUnClick = true;
		}

		if (m_castleUnClick || m_forestUnClick || m_mountainsUnClick || m_seaUnClick || m_evilCastleUnClick)
		{
			m_time -= t_delatTime;
		}
		
		if (m_time < 0.0f && m_castleUnClick)
		{
			castleComp->GetSprite().setColor(sf::Color(castleComp->GetSprite().getColor().r + 100,
				castleComp->GetSprite().getColor().g + 100,
				castleComp->GetSprite().getColor().b + 100,
				castleComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_castleUnClick = false;

			auto castleState = std::make_unique<CastleScene>(CastleScene(m_data));
			m_data->machine.AddState(std::move(castleState), false);
		}

		if (m_time < 0.0f && m_forestUnClick)
		{
			forestComp->GetSprite().setColor(sf::Color(forestComp->GetSprite().getColor().r + 100,
				forestComp->GetSprite().getColor().g + 100,
				forestComp->GetSprite().getColor().b + 100,
				forestComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_forestUnClick = false;
		}

		if (m_time < 0.0f && m_mountainsUnClick)
		{
			mountainsComp->GetSprite().setColor(sf::Color(mountainsComp->GetSprite().getColor().r + 100,
				mountainsComp->GetSprite().getColor().g + 100,
				mountainsComp->GetSprite().getColor().b + 100,
				mountainsComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_mountainsUnClick = false;
		}
		
		if (m_time < 0.0f && m_seaUnClick)
		{
			seaComp->GetSprite().setColor(sf::Color(seaComp->GetSprite().getColor().r + 100,
				seaComp->GetSprite().getColor().g + 100,
				seaComp->GetSprite().getColor().b + 100,
				seaComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_seaUnClick = false;
		}
		
		if (m_time < 0.0f && m_evilCastleUnClick)
		{
			evilCastleComp->GetSprite().setColor(sf::Color(evilCastleComp->GetSprite().getColor().r + 100,
				evilCastleComp->GetSprite().getColor().g + 100,
				evilCastleComp->GetSprite().getColor().b + 100,
				evilCastleComp->GetSprite().getColor().a));

			m_time = 0.1f;
			m_evilCastleUnClick = false;
		}

		// manage screen's scene view on fixed time
		Engine2D::GetWin().setView(m_data->machine.GetActiveState()->GetSceneView());

		m_data->ents.Update(m_entities, t_delatTime);
	}

	void MapScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void MapScene::AddEntity(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}
}