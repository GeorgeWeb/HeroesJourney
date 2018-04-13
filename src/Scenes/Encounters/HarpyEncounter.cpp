#include "HarpyEncounter.hpp"
#include "../PauseMenu.hpp"
#include "../MapScene.hpp"

#include <Engine/ECM/Components/ClickableComponent.hpp>

namespace HJ {
	namespace Encounters {

		using namespace Engine;
		using namespace System;
		// engine/game component namespaces
		using namespace Engine::ECM;
		using namespace Engine::Components;
		using namespace Entities;

		HarpyEncounter::HarpyEncounter(GameDataRef t_data)
			: BaseEncounterScene(t_data)
		{ }

		void HarpyEncounter::Init()
		{
			m_data->assets.LoadTexture("Tex_HarpyBattleBG", ENCOUNTER_HARPY_BACKGROUND);

			// ......... //
			// populate the active heroes list with the currently unlocked ones before the battle starts
			m_activeHeroes.push_back(m_data->gm.hRogue);
			m_activeHeroes.push_back(m_data->gm.hBard);
			m_activeHeroes.push_back(m_data->gm.hKnight);
			// set the turn count to the size of all active heroes
			m_hTurnCount = m_activeHeroes.size();

			// Background
			auto bg = std::make_shared<Entity>();
			auto bgSprite = bg->AddComponent<SpriteComponent>("C_HarpyBattleBGSprite");
			// define bg sprite
			bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_HarpyBattleBG"));
			bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
			// properties
			bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
			bg->SetVisible(true);
			bg->SetAlive(true);
			bg->Init();

			// no unlocked heroes apart from the main character - the Knight
			m_data->gm.hKnight->SetSprite(m_data->assets.GetTexture("Tex_HeroKnight"), sf::IntRect(0, 0, 32, 32));
			m_data->gm.hKnight->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_data->gm.hKnight->GetSpriteComponent()->GetSprite().getGlobalBounds().width) * 0.2f,
				(SCREEN_HEIGHT - m_data->gm.hKnight->GetSpriteComponent()->GetSprite().getGlobalBounds().height) * 0.4f));
			m_data->gm.hKnight->Init();

			m_data->gm.hBard->SetSprite(m_data->assets.GetTexture("Tex_HeroKnight"), sf::IntRect(0, 0, 32, 32));
			m_data->gm.hBard->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_data->gm.hBard->GetSpriteComponent()->GetSprite().getGlobalBounds().width) * 0.1f,
				(SCREEN_HEIGHT - m_data->gm.hBard->GetSpriteComponent()->GetSprite().getGlobalBounds().height) * 0.25f));
			m_data->gm.hBard->Init();

			m_data->gm.hRogue->SetSprite(m_data->assets.GetTexture("Tex_HeroKnight"), sf::IntRect(0, 0, 32, 32));
			m_data->gm.hRogue->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_data->gm.hRogue->GetSpriteComponent()->GetSprite().getGlobalBounds().width) * 0.2f,
				(SCREEN_HEIGHT - m_data->gm.hRogue->GetSpriteComponent()->GetSprite().getGlobalBounds().height) * 0.1f));
			m_data->gm.hRogue->Init();

			// encounters's evil ai - forest troll
			m_activeBoss = std::make_shared<Hero>();
			int health = m_data->gm.hRogue->GetHealth() * 3;
			m_activeBoss->SetStats("Harpy", HERO_TYPE::EVIL, health, 15, 1, 15);
			m_activeBoss->SetSprite(m_data->assets.GetTexture("Tex_EvilFrostGolem"), sf::IntRect(0, 0, 32, 32));
			m_activeBoss->SetPosition(sf::Vector2f((SCREEN_WIDTH - m_activeBoss->GetSpriteComponent()->GetSprite().getGlobalBounds().width) * 0.7f,
				(SCREEN_HEIGHT - m_activeBoss->GetSpriteComponent()->GetSprite().getGlobalBounds().height) * 0.2f));
			m_activeBoss->Init();
			m_activeBoss->GetSpriteComponent()->GetSprite().setScale(7.5f, 7.5f);
			// Add perma status effects
			m_activeBoss->GetStatusComponent()->SetEffect(EFFECT_TYPE::FLY, true);
			// Add skills
			m_activeBoss->GetSkillComponent()->AddSkill(SKILL_NAME::SPECIAL_SKILL_1, std::make_shared<IcyClaw>());
			m_activeBoss->GetSkillComponent()->AddSkill(SKILL_NAME::SPECIAL_SKILL_2, std::make_shared<IcyClaw>());
			m_activeBoss->GetSkillComponent()->AddSkill(SKILL_NAME::RAGE, std::make_shared<Devour>()); ///> rage skill!

			// Baseline positions
			// good
			goodBaseLine = m_data->gm.hKnight->GetPosition();
			goodBaseLine.x += m_data->gm.hKnight->GetSpriteComponent()->GetSprite().getGlobalBounds().width + 10.0f;
			// evil
			evilBaseLine = m_activeBoss->GetPosition();
			evilBaseLine.x -= m_data->gm.hKnight->GetSpriteComponent()->GetSprite().getGlobalBounds().width + 10.0f;

			// create an event-like action resolver for hero/ai - [actions/events]
			m_actionResolver = std::make_shared<ActionResolver>();
			m_actionResolver->Init();
			// CREATE UI ELEMENTS

			// ui frame
			auto uiFrame = std::make_shared<Entity>();
			auto uiFrameSprite = uiFrame->AddComponent<SpriteComponent>("C_EncounterUIFrameSprite");
			uiFrameSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
			uiFrameSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_EncounterUIFrame"));
			//properties
			uiFrame->SetPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT * 0.63f));
			uiFrame->SetVisible(true);
			uiFrame->SetAlive(true);
			uiFrame->Init();
			m_allUIcomps.push_back(uiFrameSprite.get());

			// Attack button
			auto atkBtn = std::make_shared<Button>();
			auto atkBtnSprite = atkBtn->GetSpriteComponent();
			atkBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
			atkBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_BasicAttackBtn"));
			//properties
			atkBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.67f));
			atkBtn->Init();
			//clickable component
			m_allUIcomps.push_back(atkBtnSprite.get());

			// Defend button
			auto defBtn = std::make_shared<Button>();
			auto defBtnSprite = defBtn->GetSpriteComponent();
			defBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
			defBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_DefendBtn"));
			//properties
			defBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.525f, SCREEN_HEIGHT * 0.67f));
			defBtn->SetVisible(true);
			defBtn->SetAlive(true);
			defBtn->Init();
			m_allUIcomps.push_back(defBtnSprite.get());

			// HP button
			auto hpBtn = std::make_shared<Button>();
			// sprite
			auto hpBtnSprite = hpBtn->GetSpriteComponent();
			hpBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
			hpBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UseHPBtn"));
			hpBtnSprite->GetSprite().scale(3.0f, 3.0f);
			// text
			auto hpBtnText = hpBtn->GetTextComponent();
			hpBtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
			hpBtnText->GetText().setStyle(sf::Text::Bold);
			hpBtnText->GetText().setString("x" + std::to_string(m_data->gm.healthPot));
			hpBtnText->GetText().setCharacterSize(16);
			//properties
			hpBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.67f));
			hpBtn->Init();
			hpBtnText->GetText().setPosition(
				hpBtn->GetPosition().x + (hpBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.00001f) - hpBtnText->GetText().getGlobalBounds().width * 0.00001f,
				hpBtn->GetPosition().y + (hpBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.85f) - hpBtnText->GetText().getGlobalBounds().height * 0.85f
			);
			m_allUIcomps.push_back(hpBtnSprite.get());

			// MP button
			auto mpBtn = std::make_shared<Button>();
			// sprite
			auto mpBtnSprite = mpBtn->GetSpriteComponent();
			mpBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
			mpBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_UseMPBtn"));
			mpBtnSprite->GetSprite().scale(3.0f, 3.0f);
			// text
			auto mpBtnText = mpBtn->GetTextComponent();
			mpBtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
			mpBtnText->GetText().setStyle(sf::Text::Bold);
			mpBtnText->GetText().setString("x" + std::to_string(m_data->gm.manaPot));
			mpBtnText->GetText().setCharacterSize(16);
			//properties
			mpBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.81f));
			mpBtn->Init();
			mpBtnText->GetText().setPosition(
				mpBtn->GetPosition().x + (hpBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().width * 0.0001f) - mpBtnText->GetText().getGlobalBounds().width * 0.0001f,
				mpBtn->GetPosition().y + (hpBtn->GetSpriteComponent()->GetSprite().getGlobalBounds().height * 0.85f) - mpBtnText->GetText().getGlobalBounds().height * 0.85f
			);
			m_allUIcomps.push_back(mpBtnSprite.get());

			// Skill1 button
			auto skill1Btn = std::make_shared<Button>();
			// sprite
			auto skill1BtnSprite = skill1Btn->GetSpriteComponent();
			skill1BtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
			skill1BtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_TestSkillBtn"));
			// text
			auto skill1BtnText = skill1Btn->GetTextComponent();
			skill1BtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
			skill1BtnText->GetText().setStyle(sf::Text::Bold);
			skill1BtnText->GetText().setString("Skill 1");
			skill1BtnText->GetText().setCharacterSize(16);
			//properties
			skill1Btn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.81f));
			skill1Btn->Init();
			skill1BtnText->GetText().setPosition(skill1Btn->GetPosition().x, skill1Btn->GetPosition().y + 115.0f);
			m_allUIcomps.push_back(skill1BtnSprite.get());

			// Skill2 button
			auto skill2Btn = std::make_shared<Button>();
			// sprite
			auto skill2BtnSprite = skill2Btn->GetSpriteComponent();
			skill2BtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
			skill2BtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_TestSkillBtn"));
			// text
			auto skill2BtnText = skill2Btn->GetTextComponent();
			skill2BtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
			skill2BtnText->GetText().setStyle(sf::Text::Bold);
			skill2BtnText->GetText().setString("Skill 2");
			skill2BtnText->GetText().setCharacterSize(16);
			// general properties
			skill2Btn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.525f, SCREEN_HEIGHT * 0.81f));
			skill2Btn->Init();
			skill2BtnText->GetText().setPosition(skill2Btn->GetPosition().x, skill2Btn->GetPosition().y + 115.0f);
			m_allUIcomps.push_back(skill2BtnSprite.get());

			// Pause button
			auto pauseBtn = std::make_shared<Button>();
			// sprite
			auto pauseBtnSprite = pauseBtn->GetSpriteComponent();
			pauseBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
			pauseBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
			pauseBtnSprite->GetSprite().scale(0.75f, 0.75f);
			// text
			auto pauseBtnText = pauseBtn->GetTextComponent();
			pauseBtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
			pauseBtnText->GetText().setString("Pause");
			pauseBtnText->GetText().scale(0.75f, 0.75f);
			pauseBtnText->GetText().setCharacterSize(24);
			// general properties
			pauseBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.67f));
			pauseBtn->Init();
			// center text
			pauseBtnText->GetText().setPosition(pauseBtn->GetPosition().x + pauseBtnText->GetText().getGlobalBounds().width * 0.7f,
				pauseBtn->GetPosition().y + pauseBtnText->GetText().getGlobalBounds().height * 1.2f);
			m_allUIcomps.push_back(pauseBtnSprite.get());

			// Concede button
			auto concedeBtn = std::make_shared<Button>();
			// sprite
			auto concedeBtnSprite = concedeBtn->GetSpriteComponent();
			concedeBtnSprite->GetSprite().setColor(sf::Color(169, 169, 169, 169));
			concedeBtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StandardBtn"));
			concedeBtnSprite->GetSprite().scale(0.75f, 0.75f);
			// text
			auto concedeBtnText = concedeBtn->GetTextComponent();
			concedeBtnText->SetFont(m_data->assets.GetFont("Font_Pixel"));
			concedeBtnText->GetText().setColor(sf::Color(169, 169, 169, 169));
			concedeBtnText->GetText().setString("Concede");
			concedeBtnText->GetText().scale(0.75f, 0.75f);
			concedeBtnText->GetText().setCharacterSize(24);
			// general properties
			concedeBtn->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.845f));
			concedeBtn->Init();
			// center text
			concedeBtnText->GetText().setPosition(concedeBtn->GetPosition().x + concedeBtnText->GetText().getGlobalBounds().width * 0.375f,
				concedeBtn->GetPosition().y + concedeBtnText->GetText().getGlobalBounds().height * 1.125f);
			m_allUIcomps.push_back(concedeBtnSprite.get());

			std::string& heroHP = std::string("");
			std::string& heroMP = std::string("");
			// Text indicating knight stats
			auto knightStatsTxt = std::make_shared<Entity>();
			auto knightStatsTxtComp = knightStatsTxt->AddComponent<TextComponent>("C_HeroStatsText");
			knightStatsTxtComp->GetText().setFont(m_data->assets.GetFont("Font_Pixel"));
			knightStatsTxtComp->GetText().setCharacterSize(14);
			heroHP = std::to_string(m_data->gm.hKnight->GetHealth()) + "/" + std::to_string(m_data->gm.hKnight->GetMaxHealth()) + "HP";
			heroMP = std::to_string(m_data->gm.hKnight->GetMana()) + "/" + std::to_string(m_data->gm.hKnight->GetMaxMana()) + "MP";
			knightStatsTxtComp->GetText().setString(m_data->gm.hKnight->className() + ": " + heroHP + " | " + heroMP);
			knightStatsTxtComp->GetText().setColor(sf::Color::White);
			knightStatsTxtComp->GetText().setStyle(sf::Text::Bold);
			knightStatsTxt->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.035f, SCREEN_HEIGHT * 0.7f));
			knightStatsTxt->SetAlive(true);
			knightStatsTxt->SetVisible(true);
			knightStatsTxt->Init();

			// Text indicating bard stats
			auto bardStatsTxt = std::make_shared<Entity>();
			auto bardStatsTxtComp = bardStatsTxt->AddComponent<TextComponent>("C_HeroStatsText");
			bardStatsTxtComp->GetText().setFont(m_data->assets.GetFont("Font_Pixel"));
			bardStatsTxtComp->GetText().setCharacterSize(14);
			heroHP = std::to_string(m_data->gm.hBard->GetHealth()) + "/" + std::to_string(m_data->gm.hBard->GetMaxHealth()) + "HP";
			heroMP = std::to_string(m_data->gm.hBard->GetMana()) + "/" + std::to_string(m_data->gm.hBard->GetMaxMana()) + "MP";
			bardStatsTxtComp->GetText().setString(m_data->gm.hBard->className() + ": " + heroHP + " | " + heroMP);
			bardStatsTxtComp->GetText().setColor(sf::Color::White);
			bardStatsTxt->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.035f, SCREEN_HEIGHT * 0.75f));
			bardStatsTxt->SetAlive(true);
			bardStatsTxt->SetVisible(true);
			bardStatsTxt->Init();

			// Text indicating rogue stats
			auto rogueStatsTxt = std::make_shared<Entity>();
			auto rogueStatsTxtComp = rogueStatsTxt->AddComponent<TextComponent>("C_HeroStatsText");
			rogueStatsTxtComp->GetText().setFont(m_data->assets.GetFont("Font_Pixel"));
			rogueStatsTxtComp->GetText().setCharacterSize(14);
			heroHP = std::to_string(m_data->gm.hRogue->GetHealth()) + "/" + std::to_string(m_data->gm.hRogue->GetMaxHealth()) + "HP";
			heroMP = std::to_string(m_data->gm.hRogue->GetMana()) + "/" + std::to_string(m_data->gm.hRogue->GetMaxMana()) + "MP";
			rogueStatsTxtComp->GetText().setString(m_data->gm.hRogue->className() + ": " + heroHP + " | " + heroMP);
			rogueStatsTxtComp->GetText().setColor(sf::Color::White);
			rogueStatsTxt->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.035f, SCREEN_HEIGHT * 0.8f));
			rogueStatsTxt->SetAlive(true);
			rogueStatsTxt->SetVisible(true);
			rogueStatsTxt->Init();

			// Text indicating BOSS stats
			auto bossStatsTxt = std::make_shared<Entity>();
			auto bossStatsTxtComp = bossStatsTxt->AddComponent<TextComponent>("C_HeroStatsText");
			bossStatsTxtComp->GetText().setFont(m_data->assets.GetFont("Font_Pixel"));
			bossStatsTxtComp->GetText().setCharacterSize(18);
			heroHP = std::to_string(m_activeBoss->GetHealth()) + "/" + std::to_string(m_activeBoss->GetMaxHealth()) + "HP";
			bossStatsTxtComp->GetText().setString(m_activeBoss->className() + ": " + heroHP);
			bossStatsTxtComp->GetText().setColor(sf::Color::Yellow);
			bossStatsTxt->SetPosition(sf::Vector2f(SCREEN_WIDTH * 0.035f, SCREEN_HEIGHT * 0.95f));
			bossStatsTxt->SetAlive(true);
			bossStatsTxt->SetVisible(true);
			bossStatsTxt->Init();

			m_statistics.push_back(bossStatsTxt);
			m_statistics.push_back(rogueStatsTxt);
			m_statistics.push_back(bardStatsTxt);
			m_statistics.push_back(knightStatsTxt);

			AddEntity("E_zTutorialBG", bg);
			AddEntity("E_HeroKnight", m_data->gm.hKnight);
			AddEntity("E_HeroBard", m_data->gm.hBard);
			AddEntity("E_HeroRogue", m_data->gm.hRogue);
			AddEntity("E_SceneBoss", m_activeBoss);
			AddEntity("E_ActionResolver", m_actionResolver);
			AddEntity("E_xTutorialUiFrame", uiFrame);
			AddEntity("E_aAtkBtn", atkBtn);
			AddEntity("E_aDefBtn", defBtn);
			AddEntity("E_aHPBtn", hpBtn);
			AddEntity("E_aMPBtn", mpBtn);
			AddEntity("E_aSkill1Btn", skill1Btn);
			AddEntity("E_aSkill2Btn", skill2Btn);
			AddEntity("E_aPauseBtn", pauseBtn);
			AddEntity("E_aConcedeBtn", concedeBtn);
			AddEntity("E_aKnightStatsTxt", knightStatsTxt);
			AddEntity("E_aBardStatsTxt", bardStatsTxt);
			AddEntity("E_aRogueStatsTxt", rogueStatsTxt);
			AddEntity("E_aBossStatsTxt", bossStatsTxt);

			// list of the UI button sprites to be disabled/enabled on turn change
			std::vector<SpriteComponent*> battleBtnSprites{ atkBtnSprite.get(), defBtnSprite.get(), hpBtnSprite.get(), mpBtnSprite.get(), skill1BtnSprite.get(), skill2BtnSprite.get() };
			m_battleUIButtons.insert(m_battleUIButtons.end(), battleBtnSprites.begin(), battleBtnSprites.end());

			// unify all hero types / GOOD and EVIL
			m_heroesUnion.push_back(m_activeBoss);
			m_heroesUnion.insert(m_heroesUnion.end(), m_activeHeroes.begin(), m_activeHeroes.end());

			// begin the battle
			m_status = BATTLE_STATUS::PLAYING;
			// the main hero - Knight, always starts first
			NextTurn();

			// set win/loose helpers
			m_data->gm.loot = 80;
			m_data->gm.nextEncounter = 3;
		}

	}
}