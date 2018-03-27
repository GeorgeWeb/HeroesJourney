#ifndef CASTLESCENE_H
#define CASTLESCENE_H

#include <Engine/Engine.hpp>
#include "../Game.hpp"
#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/TextComponent.hpp>

#include "../Entities/Infirmary.hpp"
#include "../Entities/Blacksmith.hpp"
#include "../Entities/Library.hpp"
#include "../Entities/Inn.hpp"
#include "../Entities/GeneralStore.hpp"

namespace HJ {

	using namespace Engine;

	class CastleScene final : public SM::State
	{
		public:
			CastleScene(GameDataRef t_data);

			void Init() override final;

			void HandleInput() override final;
			void Update(float t_delatTime) override final;
			void Draw(float t_deltaTime) override final;

		protected:
			void AddEntity(const std::string& t_name, std::shared_ptr<ECM::Entity> t_entity) override final;

		private:
			GameDataRef m_data;
			bool m_click = false;
			bool m_unClick = false;

			sf::Clock m_clock;
			float m_time = 0.1f;
			// Entities
			std::shared_ptr<Entities::Infirmary> m_infirmary;
			std::shared_ptr < Entities::Blacksmith > m_blacksmith;
			std::shared_ptr<Entities::Library> m_library;
			std::shared_ptr<Entities::Inn> m_inn;
			std::shared_ptr<Entities::GeneralStore> m_generalStore;
	};
}

#endif // !CASTLESCENE_H