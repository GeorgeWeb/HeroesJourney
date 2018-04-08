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
		FROST_RESISTANCE = 1,
		DODGE_AURA = 2,
		DAMAGE_AURA = 3,
		DODGE_SKILL = 4
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

	using EffectRef = std::shared_ptr<Effect>;

	class StatusComponent final : public ECM::Component
	{
		protected:
			std::map<EFFECT_TYPE, EffectRef> m_effects;

		public:
			StatusComponent() = delete;
			explicit StatusComponent(ECM::Entity* t_parent);
			
			StatusComponent* GetType() override;

			void Update(float t_deltaTime) override;
			void Render() override;

			void SetEffect(EFFECT_TYPE t_type, bool t_active);
			std::map<EFFECT_TYPE, EffectRef> GetEffects() { return m_effects; }
		
		private:
			sf::Vector2f offset = sf::Vector2f(0.0f, 0.0f);
	};

} }

#endif // !STATUS_COMPONENT_H