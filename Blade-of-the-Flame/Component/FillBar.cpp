//#include "FillBar.h"
//#include "../Manager/GameObjectManager.h"
//
//FillBar::FillBar(GameObject* owner)
//	: GraphicsComponent(owner), backMesh_(), fillColor_()
//{
//	owner_->AddComponent<Transform>();
//
//	trans_ = owner_->GetComponent<Transform>();
//
//	GameObject* player = GameObjectManager::GetInstance().GetObjectA("player");
//	player_ = player->GetComponent<Player>();
//	playerTrans_ = player->GetComponent<Transform>();
//
//	// Set fillMesh_
//	AEGfxMeshStart();
//
//	AEVec2 halfLength = { trans_->GetLocalScale().x / 2, trans_->GetLocalScale().y / 2 };
//
//	AEGfxTriAdd(
//		-halfLength.x, -halfLength.y, 0xFFFFFFFF, 0.0f, 1.0f,
//		halfLength.x, -halfLength.y, 0xFFFFFFFF, 1.0f, 1.0f,
//		-halfLength.x, halfLength.y, 0xFFFFFFFF, 0.0f, 0.0f
//	);
//	AEGfxTriAdd(
//		halfLength.x, -halfLength.y, 0xFFFFFFFF, 1.0f, 1.0f,
//		halfLength.x, halfLength.y, 0xFFFFFFFF, 1.0f, 0.0f,
//		-halfLength.x, halfLength.y, 0xFFFFFFFF, 0.0f, 0.0f
//	);
//
//	backMesh_ = AEGfxMeshEnd();
//}
//
//FillBar::~FillBar()
//{
//	AEGfxMeshFree(backMesh_);
//}
//
//void FillBar::RemoveFromManager()
//{
//	ComponentManager<GraphicsComponent>::GetInstance().DeleteComponent(static_cast<GraphicsComponent*>(this));
//}
//
//void FillBar::Update()
//{
//	
//
//	// Set render mode
//	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
//
//	// Set color to multiply
//	AEGfxSetColorToMultiply(1, 1, 1, 1);
//
//	// Set color to add
//	AEGfxSetColorToAdd(fillColor_.red / 255.f, fillColor_.green / 255.f, fillColor_.blue / 255.f, 0);
//
//	// Set blend mode
//	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
//
//	// Set transparency
//	AEGfxSetTransparency(1);
//
//	// Set texture
//	AEGfxTextureSet(nullptr, 0, 0);
//
//	// Set transform
//	AEMtx33 transf = (owner_->GetComponent<Transform>())->GetMatrix();
//	AEGfxSetTransform(transf.m);
//
//	// Draw mesh
//	AEGfxMeshDraw(backMesh_, AE_GFX_MDM_TRIANGLES);
//}
//
//void FillBar::LoadFromJson(const json&)
//{
//}
//
//json FillBar::SaveToJson()
//{
//	return json();
//}
//
//ComponentSerializer* FillBar::CreateComponent(GameObject* owner)
//{
//	if (!owner->AddComponent<FillBar>())
//		std::cout << "FillBar::CreateComponent() Component already exists" << std::endl;
//
//	return owner->GetComponent<FillBar>();
//}
