#pragma once
#include "AEMath.h"
#include "AEEngine.h"
#include "EngineComponent.h"
#include "../Manager/ComponentManager.h"
#include "../Utils/MathUtils.h"
#include "../Utils/Utils.h"
#include "../Event/EventEntity.h"

#define LAYER_NUM 7

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

	// LAYER_NUM(line: 8)과 개수 맞춰야 함
	enum CollisionLayer
	{
		P_AABB,
		P_CIRCLE,
		P_ATTACK,
		E_BODY,
		E_ATTACK,
		ITEM,
		EXP_ITEM
	};

protected:
	ColliderType type_ = AABB_TYPE;
	CollisionLayer layer_;

	EventEntity* collisionHandler_;

	Transform* trans_ = nullptr;
	AEVec2 center_ = { 0.0f, 0.0f };	// Transform의 position으로부터 얼마나 이동했는지를 나타냄
	AEVec2 scale_ = { 1.f, 1.f };		// Collider의 local scale

	Vec3 vertices_[4];
	Vec3 bottomLeft_;
	Vec3 topRight_;

	AEGfxVertexList* mesh_;
	Color color_;

	virtual void SetMesh() = 0;

	Collider(GameObject* owner);
	virtual ~Collider();

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;

	void SetType(const ColliderType& type) { type_ = type; }
	void SetLayer(const CollisionLayer& layer) { layer_ = layer; }
	void SetHandler(EventEntity* entity) { collisionHandler_ = entity; }
	void SetScale(const AEVec2& scale);
	void SetCenter(const AEVec2& center);

	const CollisionLayer& GetLayer() const { return layer_; }
	const AEVec2 GetBottomLeft() const { return AEVec2{ bottomLeft_.x, bottomLeft_.y }; }
	const AEVec2 GetTopRight() const { return AEVec2{ topRight_.x, topRight_.y }; }

	void CallHandler(CollisionEvent* event);

	friend class CollisionManager;
};

/**
* @brief	GameObject에 Transform 부착 후 사용 가능
*/
class BoxCollider : public Collider
{
private:
	void SetMesh() override;

	BoxCollider(GameObject* owner);

public:
	void Update() override;

	json SaveToJson() override;

	const AEVec2 GetBottomLeft() const { return AEVec2{ bottomLeft_.x, bottomLeft_.y }; }
	const AEVec2 GetTopRight() const { return AEVec2{ topRight_.x, topRight_.y }; }
	
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

	void SetMesh() override;

	CircleCollider(GameObject* owner);

public:
	void Update() override;

	json SaveToJson() override;

	const float& GetRadius() const { return radius_; }

	void SetRadius(float r);
	void MultiplyRadius(float m);
	void ResetRadius();

	// for StateSerializer
	static constexpr const char* TypeName = "CircleCollider";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<EngineComponent>;
	friend class CollisionManager;
};