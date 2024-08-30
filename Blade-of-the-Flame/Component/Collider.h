#pragma once
#include "AEMath.h"
#include "EngineComponent.h"
#include "../Manager/ComponentManager.h"
#include "../Utils/MathUtils.h"
#include "../Event/EventEntity.h"

class Transform;

class Collider : public EngineComponent
{
public:
	enum ColliderType
	{
		CIRCLE_TYPE,	// circle
		AABB_TYPE,		// box
		OBB_TYPE
	};

protected:
	ColliderType type_ = AABB_TYPE;

	Transform* trans_ = nullptr;
	AEVec2 center_ = { 0.0f, 0.0f };	// Transform의 position으로부터 얼마나 이동했는지를 나타냄
	AEVec2 scale_ = { 1.f, 1.f };		// Collider의 local scale

	AEVec2 collisionPoint_;	// 충돌 지점

	Vec3 vertices_[4];
	Vec3 bottomLeft_;
	Vec3 topRight_;

	Collider(GameObject* owner);

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;

	void SetType(const ColliderType& type) { type_ = type; }
	void SetScale(const AEVec2& scale) { scale_ = scale; }
	void SetCenter(const AEVec2& center) { center_ = center; }

	const AEVec2& GetBottomLeft() const { return AEVec2{ bottomLeft_.x, bottomLeft_.y }; }
	const AEVec2& GetTopRight() const { return AEVec2{ topRight_.x, topRight_.y }; }

	friend class CollisionManager;
};

/**
* @brief	GameObject에 Transform 부착 후 사용 가능
*/
class BoxCollider : public Collider
{
private:
	BoxCollider(GameObject* owner);

public:
	void Update() override;

	json SaveToJson() override;
	
	// for StateSerializer
	static constexpr const char* TypeName = "BoxCollider";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<EngineComponent>;
	friend class CollisionManager;
};

/**
* @brief	GameObject에 Transform 부착 후 사용 가능
*/
class CircleCollider : public Collider
{
private:
	float radius_;

	CircleCollider(GameObject* owner);

public:
	void Update() override;

	json SaveToJson() override;

	const float& GetRadius() const { return radius_; }

	// for StateSerializer
	static constexpr const char* TypeName = "CircleCollider";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<EngineComponent>;
	friend class CollisionManager;
};