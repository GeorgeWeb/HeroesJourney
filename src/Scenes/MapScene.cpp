#include "MapScene.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	using namespace Engine::Components;


	HJ::MapScene::MapScene(GameDataRef t_data)
		:m_data(t_data)
	{
		//not used
	}

	void HJ::MapScene::Init()
	{
		m_data->assets.LoadTexture("Tex_MapBG", MAIN_GAME_SCENE_BACKGROUND);

		//Entity manager to non-visible ents
		for (auto ent : m_data->ents.GetEntsDictionary()) ent.second->SetVisible(false);

		//Local entities map container
		std::map<std::string, std::shared_ptr<ECM::Entity>> ents;

		//Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_MapBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_MapBG"));
		bgSprite->GetSprite().setColor(sf::Color(128, 128, 128, 200));
		//properties
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		//add to local ents map
		ents.insert_or_assign("E_MapBG", bg);

		//:if entity is not in the entity manager, then add
		m_data->ents.PopulateEntsDictionary(ents);

	}

	void HJ::MapScene::HandleInput()
	{
	}

	void HJ::MapScene::Update(float t_delatTime)
	{
		m_data->ents.Update(t_delatTime);

	}

	void HJ::MapScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render();
	}
}