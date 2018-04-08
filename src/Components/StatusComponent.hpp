#ifndef STATUS_COMPONENT_H
#define STATUS_COMPONENT_H

#include "../States/State.hpp"
#include <vector>
#include <memory>

namespace HJ { namespace Components {

	using namespace Engine;

	constexpr unsigned int effectTypeCount = 5;

	enum class EFFECT_TYPE : int
	{
		STUN = 0,
		FROST_ARMOR = 1,
		ARMOUR_AURA = 2,
		DAMAGE_AURA = 3,
		FROST_AURA = 4,
		DODGE = 5,
		ENRAGE = 6,
		FLY = 7,
		MULTIPLE_TARGET = 8
	};

	struct Effect
	{
		sf::Sprite sprite;
		bool active = true;

		void SetSprite(const sf::Texture& t_texture, sf::Color t_color = sf::Color::Black)
		{ 
			sprite.setTexture(t_texture); 
			sprite.setColor(t_color);
		}
	};

	class StatusComponent final : public ECM::Component
	{
		protected:
			std::map<EFFECT_TYPE, std::shared_ptr<Effect>> m_effects;

		public:
			StatusComponent() = delete;
			explicit StatusComponent(ECM::Entity* t_parent);
			
			StatusComponent* GetType() override;

			void Update(float t_deltaTime) override;
			void Render() override;

			void SetEffect(EFFECT_TYPE t_type, bool t_active);			
			std::shared_ptr<Effect> GetEffect(EFFECT_TYPE t_type);

			std::map<EFFECT_TYPE, std::shared_ptr<Effect>> GetEffects() { return m_effects; }
		
		private:
			sf::Vector2f offset = sf::Vector2f(0.0f, 0.0f);
	};

} }

#endif // !STATUS_COMPONENT_H