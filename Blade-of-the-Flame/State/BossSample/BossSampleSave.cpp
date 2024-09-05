#include "BossSampleSave.h"
#include "../../Utils/Utils.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Serializer/StateSerializer.h"
#include "../../Component/AnimationComp.h"
//TEST_PLAYER
#include "../SampleSave.h"
#include "../../Component/LogicComponents/Bullet.h"
#include "../../Component/LogicComponents/Boss1.h"

void BossSampleSave::Init()
{
	AEGfxSetBackgroundColor(0.3f, 0.3f, 0.3f);
	// -----------------------------------------------------------------------------------------
	//PLAYER_TEST
	GameObject* obj = GameObjectManager::GetInstance().CreateObject("player");
	obj->AddComponent<Player>();

	// -----------------------------------------------------------------------------------------
	//BOSS_TEST
	GameObject* boss1 = GameObjectManager::GetInstance().CreateObject("boss");
	boss1->AddComponent<Boss1>();

	/*for (int i = 0; i < 6; i++)
	{
		std::string anim = "Assets/boss1_Anime/Idle/Idle" + std::to_string(i) + ".png";
		boss1->GetComponent<AnimationComp>()->AddDetail(anim, "Idle");
	}
	for (int i = 5; i >= 0; i--)
	{
		std::string anim = "Assets/boss1_Anime/Idle/Idle" + std::to_string(i) + ".png";
		boss1->GetComponent<AnimationComp>()->AddDetail(anim, "Idle");
	}

	boss1->GetComponent<AnimationComp>()->SetTerm(400);
	
	boss1->GetComponent<AnimationComp>()->ChangeAnimation("Idle");
	 
	boss1->GetComponent<Transform>()->SetScale({ 400, 400 });
	boss1->GetComponent<Transform>()->SetPosition({ 400,400 });*/


	// -----------------------------------------------------------------------------------------
	//BULLET_TEST
	
}

void BossSampleSave::Update()
{

}

void BossSampleSave::Exit()
{

}
