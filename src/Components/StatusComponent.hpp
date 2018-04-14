#ifndef STATUS_COMPONENT_H
#define STATUS_COMPONENT_H

#include "../States/State.hpp"
#include <vector>
#include <memory>
#include <Engine/Asset/AssetManager.hpp>


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
		DEFEND = 5,
		ENRAGE = 6,
		FLY = 7,
		MAGIC_IMUNITY = 8,
		MULTIPLE_TARGET = 9
	};

	class Effect
	{
		public:
			sf::Sprite* sprite;
			bool active = false;

			Effect(const sf::Texture& t_texture, sf::Color t_color = sf::Color::White)
			{
				this->SetTexutre(t_texture);
			}

			void SetTexutre(const sf::Texture& t_texture, sf::Color t_color = sf::Color::White)
			{
				sprite = new sf::Sprite();
				sprite->setTexture(t_texture);
				sprite->setColor(t_color);
				sprite->setScale(1.75f, 1.75f);
			}
		
			~Effect()
			{
				delete sprite;
			}
	};

	class StatusComponent final : public ECM::Component
	{
		// statuses' effects textures
		static sf::Texture stunTex;
		static sf::Texture defendTex;
		static sf::Texture dmgAuraTex;
		static sf::Texture armAuraTex;
		static sf::Texture frostAuraTex;
		static sf::Texture frostArmTex;
		static sf::Texture enrageTex;
		static sf::Texture flyTex;
		static sf::Texture magicImuneTex;
		static sf::Texture multiTargetTex;

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