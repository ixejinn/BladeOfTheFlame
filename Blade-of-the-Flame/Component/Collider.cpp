#include "Collider.h"

#include "Transform.h"
#include "../GameObject/GameObject.h"
#include "../Manager/CollisionManager.h"

Collider::Collider(GameObject* owner, ColliderType type)
	: EngineComponent(owner),
	type_(type), center_({ 0.0f, 0.0f }), scale_({ 1.f, 1.f }),
	collisionPoint_()
{
	CollisionManager::GetInstance().AddCollider(this);
}

void Collider::RemoveFromManager()
{
	ComponentManager<EngineComponent>::GetInstance().DeleteComponent(static_cast<EngineComponent*>(this));
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

void BoxCollider::SetBounds()
{
	Transform* trans = owner_->GetComponent<Transform>();
	if (trans == nullptr)
	{
		std::cerr << "[ERROR] BoxCollider::SetBounds() Transform not found" << std::endl;
		return;
	}
	const AEMtx33 transformMatrix = trans->GetMatrix();

	AEVec2 localScale = trans->GetLocalScale();
	AEVec2 ColliderHalfLen = HadamardProduct(localScale / 2, scale_);

	Vec3 vertices[4] = {
		{ center_.x - ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 1.f },
		{ center_.x + ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 1.f },
		{ center_.x - ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 1.f },
		{ center_.x + ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 1.f }
	};
	for (int i = 0; i < 4; i++)
		vertices[i] = transformMatrix * vertices[i];

	float minX, maxX, minY, maxY;
	minX = maxX = vertices[0].x;
	minY = maxY = vertices[0].y;
	for (int i = 1; i < 4; i++)
	{
		if (vertices[i].x < minX)
			minX = vertices[i].x;
		if (vertices[i].x > maxX)
			maxX = vertices[i].x;

		if (vertices[i].y < minY)
			minY = vertices[i].y;
		if (vertices[i].y > maxY)
			maxY = vertices[i].y;
	}

	bottomLeft_.x = minX;
	bottomLeft_.y = minY;
	bottomLeft_.z = 1.f;

	topRight_.x = maxX;
	topRight_.y = maxY;
	topRight_.z = 1.f;
}

BoxCollider::BoxCollider(GameObject* owner) : Collider(owner, AABB)
{
	if (owner->GetComponent<Transform>() == nullptr)
		std::cerr << "[ERROR] BoxCollider::BoxCollider() Transform not found" << std::endl;

	SetBounds();
}

void BoxCollider::Update()
{
	Transform* trans = owner_->GetComponent<Transform>();

	if (trans->IsRotationChanged())
	{
		SetBounds();
		return;
	}

	const AEMtx33 transformMatrix = trans->GetMatrix();
	AEVec2 localScale = trans->GetLocalScale();
	AEVec2 ColliderHalfLen = HadamardProduct(localScale / 2, scale_);

	bottomLeft_ = transformMatrix * Vec3{ center_.x - ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 1.f };
	topRight_	= transformMatrix * Vec3{ center_.x + ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 1.f };
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

CircleCollider::CircleCollider(GameObject* owner) : Collider(owner, CIRCLE), radius_()
{
	if (owner->GetComponent<Transform>() == nullptr)
		std::cerr << "[ERROR] BoxCollider::BoxCollider() Transform not found" << std::endl;
}

void CircleCollider::Update()
{
	Transform* trans = owner_->GetComponent<Transform>();

	AEVec2 localScale = trans->GetLocalScale();
	AEVec2 scale = trans->GetScale();

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
