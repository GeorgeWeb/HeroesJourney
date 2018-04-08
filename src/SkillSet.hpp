#ifndef SKILL_SET_H
#define SKILL_SET_H

#include "Components/StatusComponent.hpp"

namespace HJ
{
	using namespace HJ::Components;

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

	class BasicAttack : public Skill
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

	class BasicDefence : public Skill
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
	class HeroicStrike : public Skill
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

	class ShieldThrow : public Skill
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
	class OffenseAura : public Skill
	{
	public:
		OffenseAura() : Skill()
		{
			textureRefName = "Tex_TestSkillBtn";
			effectDesc = "Stun";
			type = SKILL_TYPE::RANGED;
			manaNeed = 50;
			damageMod = 0;
			applicableEffects = { EFFECT_TYPE::STUN };
		}
	};

	// [ROGUE SKILL SET]


	// [SORCERESS SKILL SET]


}

#endif // !SKILL_SET_H
