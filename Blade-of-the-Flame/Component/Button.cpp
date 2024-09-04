#include "Button.h"

#include "../State/GameState.h"
#include "../Manager/GameStateManager.h"

Button::Button(GameObject* owner) : EngineComponent(owner), pos_(), scl_()
{
	owner_->AddComponent<Transform>();
	owner_->AddComponent<Sprite>();
	owner_->AddComponent<Text>();

	trans_ = owner_->GetComponent<Transform>();

	sp_ = owner_->GetComponent<Sprite>();
	sp_->SetAnchor(Sprite::LEFT_UP);

	txt_ = owner_->GetComponent<Text>();
	txt_->SetFont("Assets/Roboto-Bold.ttf");
	txt_->SetSize(1.f);
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

	AEVec2 input{ x - 800, -2 * y + 1000 };

	bool pressed = false;

	// Check if button is pressed
	if (AEInputCheckCurr(AEVK_LBUTTON) &&
		input.x >= pos_.x && input.x <= pos_.x + scl_.x &&
		input.y >= pos_.y - scl_.y && input.y <= pos_.y)
	{
		sp_->SetColor({ 255, 0, 0 });

		pressed = true;
	}

	if (!pressed)
		return;

	switch (todo_)
	{
	case GAME:
	{
		GameState* gameState = new GameState();
		GameStateManager::GetInstance().ChangeState(gameState);
		break;
	}

	case HOW_TO:
		break;
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
}

ComponentSerializer* Button::CreateComponent(GameObject* owner)
{
	return nullptr;
}
