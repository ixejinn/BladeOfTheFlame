#pragma once
//#include "../../../Manager/ComponentManager.h"
#include "../Manager/ComponentManager.h"
//#include "../../../Manager/GameObjectManager.h"
#include "../Manager/GameObjectManager.h"

#include <map>

enum SkillType
{
	Default,
	cScorching,
	cFlame,
	cHaste,
	cFireball,
	cEating_Oxyzen,
	cMeteor,
	cInferno
};

class SkillManager
{
	bool Qactive = false;
	bool Eactive = false;
	bool Ractive = false;

	SkillManager();
	~SkillManager();
public:
	void resetKeys() { Qactive = false, Eactive = false, Ractive = false; }
	//double CooldownCountMelee = 0;
	double CooldownCountMeteor = 0;
	double CooldownCountFlame = 0;
	//static double CooldownCount;
	//static double CooldownCount;
	//static double CooldownCount;
	//static double CooldownCount;

	static SkillManager& GetInstance()
	{
		static SkillManager instance;
		return instance;
	}
	void KeyCheck();
	void SetSkillType(int level);

	int type = Default;
};