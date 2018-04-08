#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <Engine/Engine.hpp>
#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/ClickableComponent.hpp>
#include <Engine\ECM\Components\TextComponent.hpp>

#include "CastleInterior.hpp"

#include "../Game.hpp"
#include "../Entities/EncounterPopup.hpp"


namespace HJ {

	using namespace Engine;

	class MapScene final : public SM::State
	{
		public:
			MapScene(GameDataRef t_data);

			void Init() override final;

			void HandleInput() override final;
			void Update(float t_delatTime) override final;
			void Draw(float t_deltaTime) override final;

		protected:
			void AddEntity(const std::string& t_name, std::shared_ptr<ECM::Entity> t_entity) override final;

		private:
			void UpdateText();
			void UpdateResources();
			void HideEntsOnDisplay(std::vector<ECM::Entity*> t_entsToHide, std::vector<Engine::Components::SpriteComponent*> t_compsToFade, std::vector<Engine::Components::SpriteComponent*> t_compsToBlock);
			void ShowEntsOnClose(std::vector<ECM::Entity*> t_entsToShow, std::vector<Engine::Components::SpriteComponent*> t_compsToUnfade, std::vector<Engine::Components::SpriteComponent*> t_compsToUnblock);


		private:
			GameDataRef m_data;
			
			//using idea from the castle interior for text
			std::string lastClicked = "";
			/* ENTITIES */
			// Encounters popups
			std::shared_ptr<Entities::EncounterPopup> m_encounterPopup;
	};
}

#endif // !MAPSCENE_H