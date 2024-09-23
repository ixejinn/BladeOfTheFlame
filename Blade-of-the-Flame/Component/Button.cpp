#include "Button.h"

#include "../State/GameState.h"
#include "../Manager/GameStateManager.h"
#include "../Utils/Utils.h"

Button::Button(GameObject* owner) : EngineComponent(owner), pos_(), scl_()
{
	owner_->AddComponent<Transform>();
	owner_->AddComponent<Sprite>();
	owner_->AddComponent<Text>();

	trans_ = owner_->GetComponent<Transform>();

	sp_ = owner_->GetComponent<Sprite>();
	//sp_->SetAnchor(Sprite::LEFT_UP);

	txt_ = owner_->GetComponent<Text>();
	txt_->SetFont("Assets/Roboto-Bold.ttf");
	txt_->SetSize(1.2f);
}

void Button::RemoveFromManager()
{
	ComponentManager<EngineComponent>::GetInstance().DeleteComponent(static_cast<EngineComponent*>(this));
}

void Button::Update()
{
	AEInputInit();
	s32 x, y;
	AEInputGetCursorPosition(&x, &y);
	//std::cout << x << ", " << y << std::endl;

	AEVec2 input{ x - 800.f, 450.f - y };
	AEVec2 halfScl{ scl_.x / 2, scl_.y / 2 };

	// Check if button is pressed
	if (AEInputCheckCurr(AEVK_LBUTTON) &&
		input.x >= pos_.x - halfScl.x && input.x <= pos_.x + halfScl.x &&
		input.y >= pos_.y - halfScl.y && input.y <= pos_.y + halfScl.y)
	{
		sp_->SetColor({ 150, 150, 150 });

		clicked = true;
	}
}

void Button::LoadFromJson(const json&)
{
}

json Button::SaveToJson()
{
	return json();
}

void Button::SetScale(const AEVec2& scl)
{
	scl_ = scl;
	trans_->SetScale(scl);
}

void Button::SetPosition(const AEVec2& pos)
{
	pos_ = pos;
	trans_->SetPosition(pos);
}

void Button::SetTexture(const std::string& name)
{
	sp_->SetTexture(name);
}

void Button::SetText(const std::string& str)
{
	AEVec2 pos = trans_->GetPosition();
	pos.x /= float(windowWidth / 2);
	pos.y /= float(windowHeight / 2);

	//pos.x -= float(str.size() / windowWidth * 2);
	pos.x -= 0.04f;
	pos.y -= 0.007f;

	txt_->SetPosition(pos);
	txt_->SetString(str);
}

ComponentSerializer* Button::CreateComponent(GameObject* owner)
{
	return nullptr;
}
