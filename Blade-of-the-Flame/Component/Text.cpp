#include "Text.h"

#include <typeindex>
#include "../GameObject/GameObject.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/EventManager.h"
#include "../Resource/FontResource.h"
#include "../Event/Event.h"

Text::Text(GameObject* owner) : GraphicsComponent(owner), string_(), fontName_()
{
	//position_.x = 0.5;
	//position_.y = 0.2;
}

Text::~Text()
{
	if (fontId_ >= 0)
		ResourceManager::GetInstance().Unload(fontName_);
}

void Text::RemoveFromManager()
{
	ComponentManager<GraphicsComponent>::GetInstance().DeleteComponent(static_cast<GraphicsComponent*>(this));
}

void Text::Update()
{
	if (fontId_ < 0)
		std::cerr << "Text::Update() " << owner_->GetName() << "'s font ID not found" << std::endl;
	else
	{
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);

		AEGfxPrint(fontId_, string_.c_str(), position_.x, position_.y, size_, color_.red, color_.green, color_.blue, 1.0f);
	}
}

void Text::LoadFromJson(const json&)
{
}

json Text::SaveToJson()
{
	return json();
}

void Text::OnEvent(BaseEvent* event)
{
}

void Text::SetFont(const std::string& name)
{
	fontName_ = name;
	fontId_ = ResourceManager::GetInstance().Get<FontResource>(name)->GetData();
}

ComponentSerializer* Text::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Text>())
		std::cout << "Text::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Text>();
}
