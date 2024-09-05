#include "FlameAltar.h"

#include "../../Manager/GameObjectManager.h"
#include "../../Manager/EventManager.h"
#include "../../Event/Event.h"
#include "../../Utils/RandomEngine.h"

FlameAltar::FlameAltar(GameObject* owner) : LogicComponent(owner)
{
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<Sprite>();

	trans_ = owner_->GetComponent<Transform>();
	trans_->SetScale({ 100, 100 });
	trans_->SetPosition(windowWidth, windowWidth);
	
	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetLayer(Collider::ITEM);
	col->SetHandler(static_cast<EventEntity*>(this));
	owner_->GetComponent<Sprite>()->SetColor({ 255, 255, 0 });

	playerTrans_ = GameObjectManager::GetInstance().GetObjectA("player")->GetComponent<Transform>();

	timeStart_ = std::chrono::system_clock::now();
}

void FlameAltar::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void FlameAltar::Update()
{
	static bool first = true;
	static auto& engine = RandomEngine::GetInstance().GetEngine();

	std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
	if (first || dt.count() >= spawnPeriod_)
	{
		first = false;
		int x = 0, y = 0;

		bool valid = false;
		while (!valid)
		{
			x = spawnX_(engine);
			y = spawnY_(engine);

			AEVec2 playerPos = playerTrans_->GetPosition();
			playerPos.x -= x;
			playerPos.y -= y;

			f32 distance = AEVec2Length(&playerPos);
			if (distance >= windowWidth * 3)
				valid = true;
		}
		
		//std::cout << "FlameAltar : " << x << ", " << y << std::endl;
		trans_->SetPosition(float(x), float(y));
		timeStart_ = std::chrono::system_clock::now();
	}
}

void FlameAltar::LoadFromJson(const json&)
{
}

json FlameAltar::SaveToJson()
{
	return json();
}

void FlameAltar::OnEvent(BaseEvent* event)
{
}

void FlameAltar::OnCollision(CollisionEvent* event)
{
	Player* player = event->from_->GetComponent<Player>();
	if (player)
	{
		if (player->getCompass_)
		{
			NextStageEvent* event = new NextStageEvent();
			event->from_ = owner_;
			EventManager::GetInstance().AddEvent(event);	// to compass

			owner_->active_ = false;
			std::cout << "Boss!!" << std::endl;
			// 보스에게 이벤트 전송
			// 선 없애기
			// 효과 넣기
			// 이미지를 바꾸든 애니메이션을 넣든
		}
	}
}

ComponentSerializer* FlameAltar::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<FlameAltar>())
		std::cout << "FlameAltar::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<FlameAltar>();
}
