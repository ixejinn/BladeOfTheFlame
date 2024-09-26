#include "Collider.h"

#include <iostream>
#include "../GameObject/GameObject.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/Camera.h"

Collider::Collider(GameObject* owner)
	: EngineComponent(owner), layer_(), collisionHandler_(nullptr), vertices_(), bottomLeft_(), topRight_(), mesh_(), color_()
{
	CollisionManager::GetInstance().AddCollider(this);

	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();

	trans_ = owner_->GetComponent<Transform>();
}

Collider::~Collider()
{
#ifdef _DEBUG
	AEGfxMeshFree(mesh_);
#endif
}

void Collider::RemoveFromManager()
{
	ComponentManager<EngineComponent>::GetInstance().DeleteComponent(static_cast<EngineComponent*>(this));
}

void Collider::Update()
{
	AEMtx33 transformMatrix = trans_->GetMatrix();

	if (type_ == CIRCLE_TYPE)
	{
		float sclMax = max(transformMatrix.m[0][0], transformMatrix.m[1][1]);
		transformMatrix.m[0][0] = sclMax;
		transformMatrix.m[1][1] = sclMax;
	}

	AEVec2 localScale = trans_->GetLocalScale();
	AEVec2 ColliderHalfLen = HadamardProduct(localScale / 2, scale_);

	vertices_[0] = { center_.x - ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 1.f };
	vertices_[1] = { center_.x + ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 1.f };
	vertices_[2] = { center_.x + ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 1.f };
	vertices_[3] = { center_.x - ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 1.f };
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

void Collider::SetScale(const AEVec2& scale)
{
	scale_ = scale;
	SetMesh();
}

void Collider::SetCenter(const AEVec2& center)
{
	center_ = center;
	SetMesh();
}

void Collider::CallHandler(CollisionEvent* event)
{
	collisionHandler_->OnCollision(event);
}

void BoxCollider::SetMesh()
{
	if (mesh_ != nullptr)
		AEGfxMeshFree(mesh_);

	// Set mesh
	AEGfxMeshStart();

	AEVec2 localScale = trans_->GetLocalScale();
	AEVec2 ColliderHalfLen = HadamardProduct(localScale * 0.5f, scale_);

	AEGfxTriAdd(
		center_.x - ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 0xFFFFFFFF, 0.0f, 1.0f,
		center_.x + ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 0xFFFFFFFF, 1.0f, 1.0f,
		center_.x - ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 0xFFFFFFFF, 0.0f, 0.0f
	);
	AEGfxTriAdd(
		center_.x + ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 0xFFFFFFFF, 1.0f, 1.0f,
		center_.x + ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 0xFFFFFFFF, 1.0f, 0.0f,
		center_.x - ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 0xFFFFFFFF, 0.0f, 0.0f
	);

	mesh_ = AEGfxMeshEnd();
}

BoxCollider::BoxCollider(GameObject* owner) : Collider(owner)
{
	color_ = { 255, 0, 0 };
	SetMesh();
}

void BoxCollider::Update()
{
	Collider::Update();

#ifdef _DEBUG
	// Set render mode
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// Set color to multiply
	AEGfxSetColorToMultiply(1, 1, 1, 1);

	// Set color to add
	AEGfxSetColorToAdd(color_.red / 255.f, color_.green / 255.f, color_.blue / 255.f, 0);

	// Set blend mode
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// Set transparency
	AEGfxSetTransparency(1);

	// Set texture
	AEGfxTextureSet(nullptr, 0, 0);

	// Set transform
	AEMtx33 transf = trans_->GetMatrix();
	AEMtx33Concat(&transf, &Camera::GetInstance().GetMatrix(), &transf);
	AEGfxSetTransform(transf.m);

	// Draw mesh
	AEGfxMeshDraw(mesh_, AE_GFX_MDM_TRIANGLES);
#endif
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

void CircleCollider::SetMesh()
{
	if (mesh_ != nullptr)
		AEGfxMeshFree(mesh_);

	// Set mesh
	AEGfxMeshStart();

	AEVec2 localScale = trans_->GetLocalScale();
	AEVec2 ColliderHalfLen = HadamardProduct(localScale * 0.5f, scale_);

	AEGfxTriAdd(
		center_.x - ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 0xFFFFFFFF, 0.0f, 1.0f,
		center_.x + ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 0xFFFFFFFF, 1.0f, 1.0f,
		center_.x - ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 0xFFFFFFFF, 0.0f, 0.0f
	);
	AEGfxTriAdd(
		center_.x + ColliderHalfLen.x, center_.y - ColliderHalfLen.y, 0xFFFFFFFF, 1.0f, 1.0f,
		center_.x + ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 0xFFFFFFFF, 1.0f, 0.0f,
		center_.x - ColliderHalfLen.x, center_.y + ColliderHalfLen.y, 0xFFFFFFFF, 0.0f, 0.0f
	);

	mesh_ = AEGfxMeshEnd();
}

CircleCollider::CircleCollider(GameObject* owner) : Collider(owner), radius_()
{
	type_ = CIRCLE_TYPE;

	ResetRadius();

	color_ = { 0, 0, 255 };
	SetMesh();
}

void CircleCollider::Update()
{
	Collider::Update();

#ifdef _DEBUG
	// Set render mode
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// Set color to multiply
	AEGfxSetColorToMultiply(1, 1, 1, 1);

	// Set color to add
	AEGfxSetColorToAdd(color_.red / 255.f, color_.green / 255.f, color_.blue / 255.f, 0);

	// Set blend mode
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// Set transparency
	AEGfxSetTransparency(1);

	// Set texture
	AEGfxTextureSet(nullptr, 0, 0);

	// Set transform
	AEMtx33 transf = trans_->GetMatrix();
	float scl = max(transf.m[0][0], transf.m[1][1]);
	transf.m[0][0] = scl;
	transf.m[1][1] = scl;
	AEMtx33Concat(&transf, &Camera::GetInstance().GetMatrix(), &transf);
	AEGfxSetTransform(transf.m);

	// Draw mesh
	AEGfxMeshDraw(mesh_, AE_GFX_MDM_TRIANGLES);
#endif
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

void CircleCollider::SetRadius(float r)
{
	AEVec2 localScale = trans_->GetLocalScale();
	AEVec2 scale = trans_->GetScale();
	float scl = max(scale.x, scale.y);

	radius_ = r;
	scale_ = { radius_ * 2.f / localScale.x / scl, radius_ * 2.f / localScale.x / scl };	// localScale.x == localScale.y 가정
	SetMesh();
}

void CircleCollider::MultiplyRadius(float m)
{
	radius_ *= m;
	SetRadius(radius_);
}

void CircleCollider::ResetRadius()
{
	AEVec2 localScale = trans_->GetLocalScale();
	AEVec2 scale = trans_->GetScale();

	// localScale (오브젝트 로컬 스케일) * scale (스케일 변환) * scale_ (콜라이더 스케일)
	radius_ = max(localScale.x * scale.x * scale_.x, localScale.y * scale.y * scale_.y);
	radius_ /= 2.f;
}

ComponentSerializer* CircleCollider::CreateComponent(GameObject* owner)
{
	if (owner->GetComponent<Transform>() == nullptr)
		std::cerr << "[ERROR] BoxCollider::CreateComponent() Transform not found" << std::endl;

	if (!owner->AddComponent<CircleCollider>())
		std::cout << "CircleCollider::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<CircleCollider>();
}
