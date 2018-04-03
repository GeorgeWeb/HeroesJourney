#include "Tutorial.hpp"
#include "../PauseMenu.hpp"

namespace HJ { namespace Encounters {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;

	TutorialScene::TutorialScene(GameDataRef t_data)
		: m_data(t_data)
	{
		InitSceneView();
	}

	void TutorialScene::Init()
	{
		m_data->assets.LoadTexture("Tex_TutorialBG", TUTORIAL_ENCOUNTER);

		// Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_TutorialBGSprite");
		// define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_TutorialBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 128));
		// properties
		bgSprite->GetSprite().scale(0.9f, 0.85f);
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);
		bg->Init();

		m_data->gm.hKnight->SetSprite(m_data->assets.GetTexture("Tex_HeroKnight"), sf::IntRect(0, 0, 32, 32));
		m_data->gm.hKnight->Init();
		
		AddEntity("E_zTutorialBG", bg);
		AddEntity("E_HeroKnight", m_data->gm.hKnight);
	}

	void TutorialScene::HandleInput()
	{
		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView(event.size.width, event.size.height);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				// Switch scenes (to Pause Menu)
				auto pauseMenuState = std::make_unique<PauseMenuScene>(PauseMenuScene(m_data));
				m_data->machine.AddState(std::move(pauseMenuState), false);
			}
		}
	}

	void TutorialScene::Update(float t_delatTime)
	{
		m_data->ents.Update(m_entities, t_delatTime);
	}

	void TutorialScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void TutorialScene::AddEntity(const std::string & t_name, std::shared_ptr<ECM::Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}

} }