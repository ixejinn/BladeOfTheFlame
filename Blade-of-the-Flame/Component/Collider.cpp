#include "Collider.h"

#include "../GameObject/GameObject.h"
#include "../Manager/CollisionManager.h"

Collider::Collider(GameObject* owner) : EngineComponent(owner), collisionPoint_(), bottomLeft_(), topRight_()
{
	CollisionManager::GetInstance().AddCollider(this);

	owner_->AddComponent<Transform>();
	trans_ = owner_->GetComponent<Transform>();
	
	owner_->AddComponent<RigidBody>();
}

void Collider::RemoveFromManager()
{
	ComponentManager<EngineComponent>::GetInstance().DeleteComponent(static_cast<EngineComponent*>(this));
}

void Collider::Update()
{
	const AEMtx33 transformMatrix = trans_->GetMatrix();

	AEVec2 localScale = trans_->GetLocalScale();
	AEVec2 ColliderHalfLen = HadamardProduct(localScale / 2, scale_);

	vertices_[0] = { center_.x - ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 1.f };
	vertices_[1] = { center_.x + ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 1.f };
	vertices_[2] = { center_.x - ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 1.f };
	vertices_[3] = { center_.x + ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 1.f };
	for (int i = 0; i < 4; i++)
		vertices_[i] = transformMatrix * vertices_[i];

	float minX, maxX, minY, maxY;
	minX = maxX = vertices_[0].x;
	minY = maxY = vertices_[0].y;
	for (int i = 1; i < 4; i++)
	{
		if (vertices_[i].x < minX)
			minX = vertices_[i].x;
		if (vertices_[i].x > maxX)
			maxX = vertices_[i].x;

		if (vertices_[i].y < minY)
			minY = vertices_[i].y;
		if (vertices_[i].y > maxY)
			maxY = vertices_[i].y;
	}

	bottomLeft_.x = minX;
	bottomLeft_.y = minY;
	bottomLeft_.z = 1.f;

	topRight_.x = maxX;
	topRight_.y = maxY;
	topRight_.z = 1.f;
}

void Collider::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");
	if (compData != data.end())
	{
		auto p = compData->find("center");
		center_.x = p->begin().value();
		center_.y = (p->begin() + 1).value();

		p = compData->find("scale");
		scale_.x = p->begin().value();
		scale_.y = (p->begin() + 1).value();
	}
}

BoxCollider::BoxCollider(GameObject* owner) : Collider(owner) {}

void BoxCollider::Update()
{
	Collider::Update();
}

json BoxCollider::SaveToJson()
{
	json data, compData;
	data["type"] = TypeName;

	compData["center"] = { center_.x, center_.y };
	compData["scale"] = { scale_.x, scale_.y };

	data["compData"] = compData;
	return data;
}

ComponentSerializer* BoxCollider::CreateComponent(GameObject* owner)
{
	if (owner->GetComponent<Transform>() == nullptr)
		std::cerr << "[ERROR] BoxCollider::CreateComponent() Transform not found" << std::endl;

	if (!owner->AddComponent<BoxCollider>())
		std::cout << "BoxCollider::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<BoxCollider>();
}

CircleCollider::CircleCollider(GameObject* owner) : Collider(owner), radius_()
{
	type_ = CIRCLE_TYPE;
}

void CircleCollider::Update()
{
	Collider::Update();

	AEVec2 localScale = trans_->GetLocalScale();
	AEVec2 scale = trans_->GetScale();

	// localScale (오브젝트 로컬 스케일) * scale (스케일 변환) * scale_ (콜라이더 스케일)
	radius_ = max(localScale.x * scale.x * scale_.x, localScale.y * scale.y * scale_.y);
	radius_ /= 2.f;
}

json CircleCollider::SaveToJson()
{
	json data, compData;
	data["type"] = TypeName;

	compData["center"] = { center_.x, center_.y };
	compData["scale"] = { scale_.x, scale_.y };

	data["compData"] = compData;
	return data;
}

ComponentSerializer* CircleCollider::CreateComponent(GameObject* owner)
{
	if (owner->GetComponent<Transform>() == nullptr)
		std::cerr << "[ERROR] BoxCollider::CreateComponent() Transform not found" << std::endl;

	if (!owner->AddComponent<CircleCollider>())
		std::cout << "CircleCollider::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<CircleCollider>();
}
