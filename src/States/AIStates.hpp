#pragma once

#include "../Components/StateMachineComponent.hpp"
#include "../Entities/Hero.hpp"

#include <vector>

namespace HJ { namespace States {

	using namespace Engine;
	
	class GolemMoveState final : public State
	{
		private:
			sf::Vector2f m_position;

		public:
			GolemMoveState(sf::Vector2f t_position)
				: m_position(t_position) {}
			void EnterState(ECM::Entity* t_owner) override {}
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;
	};

	class GolemReturnState final : public State
	{
		private:
			sf::Vector2f m_position;

		public:
			GolemReturnState(sf::Vector2f t_position)
				: m_position(t_position) {}
			void EnterState(ECM::Entity* t_owner) override {}
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;
	};

	class GolemAttackState final : public State
	{
		private:
			std::vector<std::shared_ptr<Entities::Hero>> m_heroes;
			unsigned int m_damage;

		public:
			GolemAttackState(std::vector<std::shared_ptr<Entities::Hero>> t_heroes, unsigned int t_damage)
				: m_heroes(t_heroes), m_damage(t_damage) {}

			void EnterState(ECM::Entity* t_owner) override {}
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;
	};

	class GolemRageState final : public State
	{
		private:
			std::vector<std::shared_ptr<Entities::Hero>> m_heroes;
			unsigned int m_damage;

		public:
			GolemRageState(std::vector<std::shared_ptr<Entities::Hero>> t_heroes, unsigned int t_damage)
				: m_heroes(t_heroes), m_damage(t_damage) {}

			void EnterState(ECM::Entity* t_owner) override {}
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;
	};

} }