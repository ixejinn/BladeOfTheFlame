#include "Sprite.h"

#include "Transform.h"
#include "../Manager/ResourceManager.h"
#include "../GameObject/GameObject.h"
#include "../Resource/TextureResource.h"

Sprite::Sprite(GameObject* owner)
	: GraphicsComponent(owner), color_(), texture_(nullptr), textureName_(), mesh_()
{
	SetMesh();
}

Sprite::~Sprite()
{
	AEGfxMeshFree(mesh_);

	if (texture_ != nullptr && !textureName_.empty())
		ResourceManager::GetInstance().Unload(textureName_);
}

void Sprite::RemoveFromManager()
{
	ComponentManager<GraphicsComponent>::GetInstance().DeleteComponent(static_cast<GraphicsComponent*>(this));
}

void Sprite::Update()
{
	// Set background color
	//AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Set render mode
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// Set color to multiply
	AEGfxSetColorToMultiply(1, 1, 1, 1);

	// Set color to add
	AEGfxSetColorToAdd(color_.red / 255.f, color_.green / 255.f, color_.blue / 255.f, alpha_);

	// Set blend mode
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// Set transparency
	AEGfxSetTransparency(1);

	// Set texture
	AEGfxTextureSet(texture_, 0, 0);

	// Set transform
	AEMtx33 transf = (owner_->GetComponent<Transform>())->GetMatrix();
	AEGfxSetTransform(transf.m);

	// Draw mesh
	AEGfxMeshDraw(mesh_, AE_GFX_MDM_TRIANGLES);
	//AEGfxMeshDraw(mesh, AE_GFX_MDM_LINES);
}

void Sprite::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");
	if (compData != data.end())
	{
		auto it = compData->find("color");
		color_.red = it->begin().value();
		color_.green = (it->begin() + 1).value();
		color_.blue = (it->begin() + 2).value();

		it = compData->find("textureName");
		textureName_ = it.value();
		SetTexture(textureName_);
	}
}

json Sprite::SaveToJson()
{
	json data, compData;
	data["type"] = TypeName;

	compData["color"] = { color_.red, color_.green, color_.blue };
	compData["textureName"] = textureName_;

	data["compData"] = compData;
	return data;
}

void Sprite::SetMesh()
{
	// Set mesh
	AEGfxMeshStart();

	Transform* trans = owner_->GetComponent<Transform>();

	switch (anchor_)
	{
	case CENTER:
	{
		AEVec2 halfLength = { trans->GetLocalScale().x / 2, trans->GetLocalScale().y / 2 };
		AEGfxTriAdd(
			-halfLength.x, -halfLength.y, 0xFFFFFFFF, 0.0f, 1.0f,
			halfLength.x, -halfLength.y, 0xFFFFFFFF, 1.0f, 1.0f,
			-halfLength.x, halfLength.y, 0xFFFFFFFF, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			halfLength.x, -halfLength.y, 0xFFFFFFFF, 1.0f, 1.0f,
			halfLength.x, halfLength.y, 0xFFFFFFFF, 1.0f, 0.0f,
			-halfLength.x, halfLength.y, 0xFFFFFFFF, 0.0f, 0.0f
		);
		break;
	}

	case LEFT_CENTER:
		AEVec2 length = { trans->GetLocalScale().x, trans->GetLocalScale().y };
		AEGfxTriAdd(
			0.f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
			length.x, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			0.f, length.y - 0.5f, 0xFFFFFFFF, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			length.x, 0.f - 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			length.x, length.y - 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			0.f, length.y - 0.5f, 0xFFFFFFFF, 0.0f, 0.0f
		);
		break;
	}

	mesh_ = AEGfxMeshEnd();
}

void Sprite::SetAnchor(AnchorPoint anchor)
{
	anchor_ = anchor;
	SetMesh();
}

void Sprite::SetColor(const Color& col)
{
	color_ = col;
}

void Sprite::SetTexture(const std::string& name)
{
	textureName_ = name;
	texture_ = ResourceManager::GetInstance().Get<TextureResource>(name)->GetData();
}

ComponentSerializer* Sprite::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Sprite>())
		std::cout << "Sprite::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Sprite>();
}
