#ifndef SKILL_SET_H
#define SKILL_SET_H

#include "Components/StatusComponent.hpp"

namespace HJ
{
	using namespace Components;

	enum class SKILL_TYPE : int
	{
		MELEE = 0,
		RANGED = 1
	};

	enum class SKILL_TARGET : int
	{
		ALLY = 0,
		ENEMY = 1
	};

	class Skill
	{
		public:
			Skill() = default;
			
			unsigned int manaNeed;
			
			SKILL_TYPE type;
			SKILL_TARGET target;

			unsigned int damageMod;

			std::string textureRefName;
			std::string effectDesc;

			std::vector<EFFECT_TYPE> applicableEffects;
	};

	// [BASIC/GENERAL SKILL SET]
	class BasicAttack final : public Skill
	{
		public:
			BasicAttack() : Skill()
			{
				textureRefName = "Tex_BasicAttackBtn";
				effectDesc = "";
				type = SKILL_TYPE::MELEE;
				manaNeed = 0;
				damageMod = 100;
				applicableEffects = {};
			}
	};

	/*** SPECIALIZED SKILL SETS ***/

	class BasicDefence final : public Skill
	{
		public:
			BasicDefence() : Skill()
			{
				textureRefName = "Tex_DefendBtn";
				effectDesc = "";
				type = SKILL_TYPE::MELEE;
				manaNeed = 0;
				damageMod = 0;
				applicableEffects = {};
			}
	};

	// [KNIGHT SKILL SET]
	class HeroicStrike final : public Skill
	{
		public:
			HeroicStrike() : Skill()
			{
				textureRefName = "Tex_TestSkillBtn";
				effectDesc = "";
				type = SKILL_TYPE::MELEE;
				manaNeed = 50;
				damageMod = 200;
				applicableEffects = {};
			}
	};

	class ShieldThrow final : public Skill
	{
		public:
			ShieldThrow() : Skill()
			{
				textureRefName = "Tex_TestSkillBtn";
				effectDesc = "Stun";
				type = SKILL_TYPE::RANGED;
				manaNeed = 50;
				damageMod = 0;
				applicableEffects = { EFFECT_TYPE::STUN };
			}
	};

	// [BARD SKILL SET]
	class OffenseAura final : public Skill
	{
		public:
			OffenseAura() : Skill()
			{
				textureRefName = "Tex_TestSkillBtn";
				effectDesc = "Party DMG boost";
				type = SKILL_TYPE::RANGED;
				manaNeed = 25;
				damageMod = 0;
				applicableEffects = { EFFECT_TYPE::DAMAGE_AURA };
			}
	};

	class DeffenseAura final : public Skill
	{
		public:
			DeffenseAura() : Skill()
			{
				textureRefName = "Tex_TestSkillBtn";
				effectDesc = "Party ARM boost";
				type = SKILL_TYPE::RANGED;
				manaNeed = 25;
				damageMod = 0;
				applicableEffects = { EFFECT_TYPE::ARMOUR_AURA };
			}
	};
	
	// [ROGUE SKILL SET]
	class RavenBow final : public Skill
	{
		public:
			RavenBow() : Skill()
			{
				textureRefName = "Tex_TestSkillBtn";
				effectDesc = "";
				type = SKILL_TYPE::RANGED;
				manaNeed = 0;
				damageMod = 75;
				applicableEffects = {};
			}
	};

	class RainOfArrows final : public Skill
	{
		public:
			RainOfArrows() : Skill()
			{
				textureRefName = "Tex_TestSkillBtn";
				effectDesc = "";
				type = SKILL_TYPE::RANGED;
				manaNeed = 50;
				damageMod = 3 * 75;
				applicableEffects = {};
			}
	};

	// [SORCERESS SKILL SET]
	class FireBolt final : public Skill
	{
		public:
			FireBolt() : Skill()
			{
				textureRefName = "Tex_TestSkillBtn";
				effectDesc = "";
				type = SKILL_TYPE::RANGED;
				manaNeed = 50;
				damageMod = 200;
				applicableEffects = {};
			}
	};

	class FrostAura final : public Skill
	{
		public:
			FrostAura() : Skill()
			{
				textureRefName = "Tex_TestSkillBtn";
				effectDesc = "Party frost resistance";
				type = SKILL_TYPE::RANGED;
				manaNeed = 50;
				damageMod = 0;
				applicableEffects = { EFFECT_TYPE::FROST_AURA };
			}
	};

}

#endif // !SKILL_SET_H
