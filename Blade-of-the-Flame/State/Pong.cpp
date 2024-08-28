#include "Pong.h"

#include "AEEngine.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/EventManager.h"
#include "../Serializer/StateSerializer.h"

void Pong::Init()
{
	Transform* trans;
	RigidBody* rb;
	PlayerController* pCtrl;
	Text* text;

	/* WALL */
	// UP
	GameObject* wallUp = GameObjectManager::GetInstance().CreateObject("wallUp");

	wallUp->AddComponent<Transform>();
	trans = wallUp->GetComponent<Transform>();
	trans->SetScale(Wall::size);
	trans->SetPosition(Wall::position);

	wallUp->AddComponent<Sprite>();
	wallUp->GetComponent<Sprite>()->SetColor(wallColor);

	wallUp->AddComponent<RigidBody>();
	wallUp->GetComponent<RigidBody>()->SetUseAcceleration(false);

	wallUp->AddComponent<BoxCollider>();

	wallUp->AddComponent<Wall>();

	// DOWN
	GameObject* wallDown = GameObjectManager::GetInstance().CreateObject("WallDown");

	wallDown->AddComponent<Transform>();
	trans = wallDown->GetComponent<Transform>();
	trans->SetScale(Wall::size);
	AEVec2 pos = Wall::position;
	pos.y *= -1;
	trans->SetPosition(pos);

	wallDown->AddComponent<Sprite>();
	wallDown->GetComponent<Sprite>()->SetColor(wallColor);

	wallDown->AddComponent<RigidBody>();
	wallDown->GetComponent<RigidBody>()->SetUseAcceleration(false);

	wallDown->AddComponent<BoxCollider>();

	wallDown->AddComponent<Wall>();

	/* RACKET */
	// LEFT
	GameObject* racketLeft = GameObjectManager::GetInstance().CreateObject("racketLeft");

	racketLeft->AddComponent<Racket>();

	racketLeft->AddComponent<Transform>();
	racketLeft->GetComponent<Transform>()->SetScale(Racket::size);
	racketLeft->GetComponent<Transform>()->SetPosition({ Racket::positionLeft, 0.f });

	racketLeft->AddComponent<Sprite>();
	racketLeft->GetComponent<Sprite>()->SetColor(racketColor);

	racketLeft->AddComponent<RigidBody>();
	rb = racketLeft->GetComponent<RigidBody>();
	rb->SetUseAcceleration(false);
	rb->SetDragCoefficient(racketDragCoefficient);

	racketLeft->AddComponent<PlayerController>();
	pCtrl = racketLeft->GetComponent<PlayerController>();
	pCtrl->SetOnlyUpDown(true);
	pCtrl->SetMoveSpeed(racketSpeed);

	racketLeft->AddComponent<BoxCollider>();
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(CollisionEvent)), static_cast<EventEntity*>(racketLeft->GetComponent<Racket>()));

	// RIGHT
	GameObject* racketRight = GameObjectManager::GetInstance().CreateObject("racketRight");

	racketRight->AddComponent<Racket>();

	racketRight->AddComponent<Transform>();
	racketRight->GetComponent<Transform>()->SetScale(Racket::size);
	racketRight->GetComponent<Transform>()->SetPosition({ Racket::positionRight, 0.f });

	racketRight->AddComponent<Sprite>();
	racketRight->GetComponent<Sprite>()->SetColor(racketColor);

	racketRight->AddComponent<RigidBody>();
	rb = racketRight->GetComponent<RigidBody>();
	rb->SetUseAcceleration(false);
	rb->SetDragCoefficient(racketDragCoefficient);

	racketRight->AddComponent<PlayerController>();
	pCtrl = racketRight->GetComponent<PlayerController>();
	pCtrl->SetOnlyUpDown(true);
	pCtrl->SetMoveKeys(PlayerController::UP, AEVK_UP);
	pCtrl->SetMoveKeys(PlayerController::DOWN, AEVK_DOWN);
	pCtrl->SetMoveSpeed(racketSpeed);

	racketRight->AddComponent<BoxCollider>();
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(CollisionEvent)), static_cast<EventEntity*>(racketRight->GetComponent<Racket>()));

	/* BALL */
	GameObject* ball = GameObjectManager::GetInstance().CreateObject("ball");

	ball->AddComponent<Transform>();
	trans = ball->GetComponent<Transform>();
	trans->SetScale(ballSize);
	trans->SetLimit(Ball::limit);

	ball->AddComponent<RigidBody>();
	rb = ball->GetComponent<RigidBody>();
	//rb->SetUseAcceleration(false);
	rb->SetDragCoefficient(0.001f);
	
	ball->AddComponent<Sprite>();
	ball->GetComponent<Sprite>()->SetColor(ballColor);

	ball->AddComponent<Audio>();
	ball->GetComponent<Audio>()->SetAudio("Assets/bouken.mp3");

	ball->AddComponent<CircleCollider>();

	ball->AddComponent<Ball>();
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(CollisionEvent)), static_cast<EventEntity*>(ball->GetComponent<Ball>()));

	/* SCORE */
	Score* score;

	// LEFT
	GameObject* scoreLeft = GameObjectManager::GetInstance().CreateObject("scoreLeft");

	scoreLeft->AddComponent<Score>();
	score = scoreLeft->GetComponent<Score>();
	score->SetWinScore(winScore);
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(ScoreEvent)), static_cast<EventEntity*>(score));
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(GameOverEvent)), static_cast<EventEntity*>(score));

	scoreLeft->AddComponent<Text>();
	text = scoreLeft->GetComponent<Text>();
	text->SetFont(scoreFontName);
	text->SetString("0");
	pos = scorePosition;
	pos.x *= -1;
	text->SetPosition(pos);
	text->SetSize(scoreSize);
	text->SetColor(scoreColor);
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(ScoreEvent)), static_cast<EventEntity*>(text));
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(GameOverEvent)), static_cast<EventEntity*>(text));

	// RIGHT
	GameObject* scoreRight = GameObjectManager::GetInstance().CreateObject("scoreRight");

	scoreRight->AddComponent<Score>();
	score = scoreRight->GetComponent<Score>();
	score->SetWinScore(winScore);
	score->SetTeam(1);
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(ScoreEvent)), static_cast<EventEntity*>(score));
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(GameOverEvent)), static_cast<EventEntity*>(score));

	scoreRight->AddComponent<Text>();
	text = scoreRight->GetComponent<Text>();
	text->SetFont(scoreFontName);
	text->SetString("0");
	text->SetPosition(scorePosition);
	text->SetSize(scoreSize);
	text->SetColor(scoreColor);
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(ScoreEvent)), static_cast<EventEntity*>(text));
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(GameOverEvent)), static_cast<EventEntity*>(text));
	
}

void Pong::Update()
{
}

void Pong::Exit()
{
}