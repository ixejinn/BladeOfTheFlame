#include "SampleSave.h"

#include <string>
#include "../Utils/Utils.h"
#include "../Utils/RandomEngine.h"
#include "../Manager/GameObjectManager.h"
#include "../Serializer/StateSerializer.h"
#include "../Manager/ParticleSystem.h"

void SampleSave::Init()
{
	GameObject* obj = GameObjectManager::GetInstance().CreateObject("player");
	obj->AddComponent<Player>();

	auto& engine = RandomEngine::GetInstance().GetEngine();
	std::uniform_int_distribution<int> coord{ -300, 300 };

	for (int i = 0; i < 5; i++)
	{
		monster[i] = GameObjectManager::GetInstance().CreateObject("monster" + std::to_string(i));
		monster[i]->AddComponent<Monster>();
		
		int x = coord(engine), y = coord(engine);
		monster[i]->GetComponent<Transform>()->SetPosition(x, y);
	}

	ParticleSystem::getPtr()->SetParticleCount(3);
	// boss ¸¸µé°í inactive
}

void SampleSave::Update()
{
	bool allKill = true;
	for (int i = 0; i < 5; i++)
	{
		ParticleSystem::getPtr()->Update(monster[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		if (monster[i]->active_ == true)
		{
			allKill = false;
			break;
		}
	}
	if (allKill)
	{
		std::cout << "BOSS!!!!!" << std::endl;

		// boss active
	}
}

void SampleSave::Exit()
{
}
