#pragma once
#include <string>
#include "AEVec2.h"
#include "State.h"
#include "../Utils/Utils.h"

class Pong : public State
{
private:
	Color wallColor{ 200, 200, 200 };

	float racketDragCoefficient{ 10.f };
	float racketSpeed{ 200.f };
	Color racketColor{ 200, 200, 200 };

	AEVec2 ballSize{ 50, 50 };
	AEVec2 ballPosition{ 0.f, windowHeight / 2.f - ballSize.y / 2.f };
	Color ballColor{ 200, 200, 200 };

	std::string scoreFontName = "Assets/Roboto-Bold.ttf";
	AEVec2 scorePosition = { 800.f / windowWidth, (windowHeight - 300.f) / windowHeight };
	float scoreSize = 1.f;
	Color scoreColor{ 255, 255, 255 };

	int winScore = 11;

public:
	void Init() override;
	void Update() override;
	void Exit() override;
};