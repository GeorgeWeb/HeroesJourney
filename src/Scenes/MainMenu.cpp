#include "../DEFINITIONS.hpp"

#include "MainMenu.hpp"
#include "StoryIntro.hpp"
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
		/* < GLOBAL PRE-LOAD */
		#pragma region GLOBAL PRE-LOAD
		// music
		m_data->assets.LoadMusic("EpicTheme", EPIC_FANTASY_THEME);
		m_data->assets.LoadMusic("AdventureTheme", ADVENTURE_FANTASY_THEME);
		m_data->assets.LoadMusic("CastleTheme", CASTLE_BAKGROUND_THEME);
		// General assets
		m_data->assets.LoadTexture("Tex_StandardBtn", STANDARD_BTN);
		m_data->assets.LoadTexture("Tex_BloodSplashSheet", BLOOD_SPLASH_SPRITESHEET);
		m_data->assets.LoadTexture("Tex_TestSkillBtn", TEST_SKILL_BTN);
		m_data->assets.LoadTexture("Tex_Coin", COIN_ICON);
		// Building assets
		m_data->assets.LoadTexture("Tex_Infirmary", CASTLE_SCENE_INFIRMARY);
		m_data->assets.LoadTexture("Tex_Blacksmith", CASTLE_SCENE_BLACKSMITH);
		m_data->assets.LoadTexture("Tex_Library", CASTLE_SCENE_LIBRARY);
		m_data->assets.LoadTexture("Tex_Inn", CASTLE_SCENE_INN);
		m_data->assets.LoadTexture("Tex_GeneralStore", CASTLE_SCENE_GENERAL_STORE);
		// Hero assets
		m_data->assets.LoadTexture("Tex_HeroKnight", HERO_KNIGHT_SPRITE);
		m_data->assets.LoadTexture("Tex_HeroBard", HERO_BARD_SPRITE);
		m_data->assets.LoadTexture("Tex_HeroSorc", HERO_SORC_SPRITE);
		m_data->assets.LoadTexture("Tex_HeroRogue", HERO_ROGUE_SPRITE);
		// Evil assets
		m_data->assets.LoadTexture("Tex_EvilFrostGolem", EVIL_FROST_GOLEM_SPRITE);
		m_data->assets.LoadTexture("Tex_EvilTroll", EVIL_TROLL_SPRITE);
		m_data->assets.LoadTexture("Tex_EvilCyclops", EVIL_CYCLOPS_SPRITE);
		m_data->assets.LoadTexture("Tex_EvilHarpy", EVIL_HARPY_SPRITE);
		m_data->assets.LoadTexture("Tex_EvilFrostMage", EVIL_FROST_MAGE_SPRITE);
		// Encounter assets
		// basics
		m_data->assets.LoadTexture("Tex_EncounterUIFrame", ENCOUNTER_UI_FRAME);
		m_data->assets.LoadTexture("Tex_BasicAttackBtn", BASIC_ATTACK_BTN);
		m_data->assets.LoadTexture("Tex_DefendBtn", DEFFEND_BTN);
		m_data->assets.LoadTexture("Tex_UseHPBtn", USE_HP_BTN);
		m_data->assets.LoadTexture("Tex_UseMPBtn", USE_MP_BTN);
		// special skills
		m_data->assets.LoadTexture("Tex_ArcherySkill", ARCHERY_SKILL);
		m_data->assets.LoadTexture("Tex_RoASkill", RAIN_OF_ARROWS_SKILL);
		m_data->assets.LoadTexture("Tex_HeroicStrikeSkill", HEROIC_STRIKE_SKILL);
		m_data->assets.LoadTexture("Tex_ShieldBashSkill", SHIELD_BASH_SKILL);
		m_data->assets.LoadTexture("Tex_FireBoltSkill", FIRE_BOLT_SKILL);
		m_data->assets.LoadTexture("Tex_FireAuraSkill", FIRE_AURA_SKILL);
		m_data->assets.LoadTexture("Tex_OffAuraSkill", OFF_AURA_SKILL);
		m_data->assets.LoadTexture("Tex_DefAuraSkill", DEF_AURA_SKILL);
		#pragma endregion
		/* /> GLOBAL PRE-LOAD */

		// Load resources
		m_data->assets.LoadTexture("Tex_MainBG", SPLASH_SCENE_BACKGROUND);

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
		titleComp->GetText().setColor(sf::Color(255, 255, 255, 200));
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
		mbtnText->GetText().setString("NEW STORY");
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

		// Pause splash theme
		m_data->assets.GetMusic("EpicTheme").stop();

		// play theme
		m_data->assets.GetMusic("AdventureTheme").setLoop(true);
		m_data->assets.GetMusic("AdventureTheme").setVolume(35);
		m_data->assets.GetMusic("AdventureTheme").play();

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
			if (startBtn->IsClickable() && m_data->input.isClicked(startComp->GetSprite(), Controls::GetButton("Select"), Engine2D::GetWin()))
			{
				startBtn->SetClicked(true);
			}

			auto loadComp = m_data->ents.Find<Button>("E_xLoadBtn")->GetSpriteComponent();
			auto loadBtn = m_data->ents.Find<Button>("E_xLoadBtn")->GetClickableComponent();
			if (loadBtn->IsClickable() &&  m_data->input.isClicked(loadComp->GetSprite(), Controls::GetButton("Select"), Engine2D::GetWin()))
			{
				loadBtn->SetClicked(true);
			}

			auto setComp = m_data->ents.Find<Button>("E_xSetBtn")->GetSpriteComponent();
			auto setBtn = m_data->ents.Find<Button>("E_xSetBtn")->GetClickableComponent();
			if (m_data->input.isClicked(setComp->GetSprite(), Controls::GetButton("Select"), Engine2D::GetWin()))
			{
				setBtn->SetClicked(true);
			}

			auto quitComp = m_data->ents.Find<Button>("E_xQBtn")->GetSpriteComponent();
			auto quitBtn = m_data->ents.Find<Button>("E_xQBtn")->GetClickableComponent();
			if (quitBtn->IsClickable() && m_data->input.isClicked(quitComp->GetSprite(), Controls::GetButton("Select"), Engine2D::GetWin()))
			{
				quitBtn->SetClicked(true);
			}
		}
	}

	void MainMenuScene::Update(float t_delatTime)
	{
		auto load = m_data->ents.Find<Button>("E_xLoadBtn");
		if (m_data->saveData.IsEmpty(Utils::DATA_TYPE::GAME_DATA))
		{
			load->GetClickableComponent()->SetClickable(false);
			load->GetSpriteComponent()->GetSprite().setColor(sf::Color(128, 128, 128, 228));
		}
		else
		{
			load->GetClickableComponent()->SetClickable(true);
			load->GetSpriteComponent()->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		}

		auto startBtn = m_data->ents.Find<Button>("E_xStartBtn")->GetClickableComponent();
		if (startBtn->CanResolve())
		{
			startBtn->SetResolve(false);

			m_data->gm.healthPot = 1;
			m_data->gm.manaPot = 1;
			m_data->gm.gold = 10;

			// serializable game entities
			// buildings
			m_data->gm.infirmary = std::make_shared<Infirmary>();
			m_data->gm.blacksmith = std::make_shared<Blacksmith>();
			m_data->gm.library = std::make_shared<Library>();
			m_data->gm.inn = std::make_shared<Inn>();
			m_data->gm.store = std::make_shared<GeneralStore>();
			// heroes
			m_data->gm.hKnight = std::make_shared<Knight>();
			m_data->gm.hBard = std::make_shared<Bard>();
			m_data->gm.hSorceress = std::make_shared<Sorceress>();
			m_data->gm.hRogue = std::make_shared<Rogue>();

			// change scene to Story intro
			auto storyIntro = std::make_unique<StoryIntroScene>(StoryIntroScene(m_data));
			m_data->machine.AddState(std::move(storyIntro));
		
		}

		auto loadBtn = load->GetClickableComponent();
		if (loadBtn->CanResolve())
		{
			loadBtn->SetResolve(false);
			
			// Load saved data
			// serializable game entities
			// heroes
			m_data->gm.hKnight = std::make_shared<Knight>(false);
			m_data->gm.hBard = std::make_shared<Bard>(false);
			m_data->gm.hSorceress = std::make_shared<Sorceress>(false);
			m_data->gm.hRogue = std::make_shared<Rogue>(false);
			// buildings
			m_data->gm.infirmary = std::make_shared<Infirmary>(false);
			m_data->gm.blacksmith = std::make_shared<Blacksmith>(false);
			m_data->gm.library = std::make_shared<Library>(false);
			m_data->gm.inn = std::make_shared<Inn>(false);
			m_data->gm.store = std::make_shared<GeneralStore>(false);

			// heroes
			// knight
			int knightHP = 0, knightMaxHP = 0, knightMP = 0, knightMaxMP = 0, knightArmour = 0, knightDodge = 0, knightCrit = 0, knightDMG = 0;
			// bard
			int bardHP = 0, bardMaxHP = 0, bardMP = 0, bardMaxMP = 0, bardArmour = 0, bardDodge = 0, bardCrit = 0, bardDMG = 0;
			// rogue
			int rogueHP = 0, rogueMaxHP = 0, rogueMP = 0, rogueMaxMP = 0, rogueArmour = 0, rogueDodge = 0, rogueCrit = 0, rogueDMG = 0;
			// sorceress
			int sorcHP = 0, sorcMaxHP = 0, sorcMP = 0, sorcMaxMP = 0, sorcArmour = 0, sorcDodge = 0, sorcCrit = 0, sorcDMG = 0;
			// buidlings
			int blacksmithLvl = 0, infirmaryLvl = 0, libraryLvl = 0, innLvl = 0, storeLvl = 0;
			// resources
			// potions
			int healthPots = 0, manaPots = 0;
			// money
			int gold = 0;
			// encounters/campaign progression
			int trollPassed = 0, cyclopsPassed = 0, harpyPassed = 0, magePassed = 0, progress = 0;
			
			m_data->saveData.Load<int>({
				&knightHP, &knightMaxHP, &knightMP, &knightMaxMP, &knightArmour, &knightDodge, &knightCrit, &knightDMG,
				&bardHP, &bardMaxHP, &bardMP, &bardMaxMP, &bardArmour, &bardDodge, &bardCrit, &bardDMG, 
				&rogueHP, &rogueMaxHP, &rogueMP, &rogueMaxMP, &rogueArmour, &rogueDodge, &rogueCrit, &rogueDMG,
				&sorcHP, &sorcMaxHP, &sorcMP, &sorcMaxMP, &sorcArmour, &sorcDodge, &sorcCrit, &sorcDMG,
				&blacksmithLvl, &infirmaryLvl, &libraryLvl, &innLvl, &storeLvl, 
				&healthPots, &manaPots, &gold, 
				&trollPassed, &cyclopsPassed, &harpyPassed, &magePassed, &progress
			}, Utils::DATA_TYPE::GAME_DATA);			

			// set the loaded values
			#pragma region Setting up last gameplay save
			// heroes
			// knight
			m_data->gm.hKnight->SetHealth(knightHP);
			m_data->gm.hKnight->SetMaxHealth(knightMaxHP);
			m_data->gm.hKnight->SetMana(knightMP);
			m_data->gm.hKnight->SetMaxMana(knightMaxMP);
			m_data->gm.hKnight->SetArmour(knightArmour);
			m_data->gm.hKnight->SetDodge(knightDodge);
			m_data->gm.hKnight->SetCrit(knightCrit);
			m_data->gm.hKnight->SetDmg(knightDMG);
			// bard
			m_data->gm.hBard->SetHealth(bardHP);
			m_data->gm.hBard->SetMaxHealth(bardMaxHP);
			m_data->gm.hBard->SetMana(bardMP);
			m_data->gm.hBard->SetMaxMana(bardMaxMP);
			m_data->gm.hBard->SetArmour(bardArmour);
			m_data->gm.hBard->SetDodge(bardDodge);
			m_data->gm.hBard->SetCrit(bardCrit);
			m_data->gm.hBard->SetDmg(bardDMG);
			// rogue
			m_data->gm.hRogue->SetHealth(rogueHP);
			m_data->gm.hRogue->SetMaxHealth(rogueMaxHP);
			m_data->gm.hRogue->SetMana(rogueMP);
			m_data->gm.hRogue->SetMaxMana(rogueMaxMP);
			m_data->gm.hRogue->SetArmour(rogueArmour);
			m_data->gm.hRogue->SetDodge(rogueDodge);
			m_data->gm.hRogue->SetCrit(rogueCrit);
			m_data->gm.hRogue->SetDmg(rogueDMG);
			// sorceress
			m_data->gm.hSorceress->SetHealth(sorcHP);
			m_data->gm.hSorceress->SetMaxHealth(sorcMaxHP);
			m_data->gm.hSorceress->SetMana(sorcMP);
			m_data->gm.hSorceress->SetMaxMana(sorcMaxMP);
			m_data->gm.hSorceress->SetArmour(sorcArmour);
			m_data->gm.hSorceress->SetDodge(sorcDodge);
			m_data->gm.hSorceress->SetCrit(sorcCrit);
			m_data->gm.hSorceress->SetDmg(sorcDMG);
			//buidlings
			m_data->gm.blacksmith->SetLevel(blacksmithLvl);
			m_data->gm.infirmary->SetLevel(infirmaryLvl);
			m_data->gm.library->SetLevel(libraryLvl);
			m_data->gm.inn->SetLevel(innLvl);
			m_data->gm.store->SetLevel(storeLvl);
			// resources
			m_data->gm.healthPot = healthPots;
			m_data->gm.manaPot = manaPots;
			m_data->gm.gold = gold;
			// encounters/campaign progression
			m_data->gm.trollPassed = trollPassed;
			m_data->gm.cyclopsPassed = cyclopsPassed;
			m_data->gm.harpyPassed = harpyPassed;
			m_data->gm.magePassed = magePassed;
			m_data->gm.nextEncounter = progress;
			#pragma endregion

			// change scene to Story intro
			auto storyIntro = std::make_shared<MapScene>(MapScene(m_data));
			m_data->machine.AddState(storyIntro);
		}

		auto setBtn = m_data->ents.Find<Button>("E_xSetBtn")->GetClickableComponent();
		if (setBtn->CanResolve())
		{
			setBtn->SetResolve(false);
			// change scene to Settings
			auto SettingsScreen = std::make_shared<SettingsScene>(SettingsScene(m_data));
			m_data->machine.AddState(SettingsScreen, false);
		}

		auto quitBtn = m_data->ents.Find<Button>("E_xQBtn")->GetClickableComponent();
		if (quitBtn->CanResolve())
		{
			quitBtn->SetResolve(false);
			// exit game (window)
			Engine2D::GetWin().close();
		}

		m_data->ents.Update(m_entities, t_delatTime);
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