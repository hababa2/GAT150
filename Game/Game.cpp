#include "Game.h"
#include "GameComponent\PlayerComponent.h"
#include "GameComponent\EnemyComponent.h"
#include "GameComponent\PickupComponent.h"

void Game::Initialize()
{
	engine = std::make_unique<nh::Engine>();
	engine->Startup();
	engine->Get<nh::Renderer>()->Create("GAT150", 800, 600);

	REGISTER_CLASS(PlayerComponent);
	REGISTER_CLASS(EnemyComponent);
	REGISTER_CLASS(PickupComponent);

	scene = std::make_unique<nh::Scene>();
	scene->engine = engine.get();

	nh::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nh::SetFilePath("../Resources");

	engine->Get<nh::EventSystem>()->Subscribe("add_score", std::bind(&Game::OnAddScore, this, std::placeholders::_1));
	engine->Get<nh::EventSystem>()->Subscribe("player_hurt", std::bind(&Game::OnPlayerHit, this, std::placeholders::_1));
	engine->Get<nh::EventSystem>()->Subscribe("invincibility", std::bind(&Game::OnInvincibility, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->RemoveAll();
	engine->Shutdown();
}

void Game::Update()
{
	float dt = engine->time.deltaTime;

	engine->Update();
	quit |= (engine->Get<nh::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nh::InputSystem::eKeyState::Pressed);

	switch (state)
	{
	case Game::eState::Reset:
		Reset();
		break;
	case Game::eState::Title:
		Title();
		break;
	case Game::eState::StartGame:
		StartGame();
		break;
	case Game::eState::StartLevel:
		StartLevel();
		break;
	case Game::eState::Level:
		Level();
		break;
	case Game::eState::PlayerDead:
		PlayerDead();
		break;
	case Game::eState::GameOver:
		GameOver();
		break;
	default: 
		break;
	}

	auto scoreActor = scene->FindActor("Score");
	auto livesActor = scene->FindActor("Lives");
	if (scoreActor)
	{
		scoreActor->GetComponent<nh::TextComponent>()->SetText("Score: " + std::to_string(score));
	}
	if (livesActor)
	{
		livesActor->GetComponent<nh::TextComponent>()->SetText("Lives: " + std::to_string(lives));
	}

	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<nh::Renderer>()->BeginFrame();

	scene->Draw(engine->Get<nh::Renderer>());
	engine->Draw(engine->Get<nh::Renderer>());

	engine->Get<nh::Renderer>()->EndFrame();
}

void Game::Reset()
{
	scene->RemoveAll();

	rapidjson::Document doc;
	assert(nh::json::Load("Title.txt", doc));
	scene->Read(doc);

	scene->FindActor("Title")->active = true;
	scene->FindActor("GameOver")->active = false;
	lives = 3;
	score = 0;

	state = Game::eState::Title;
}

void Game::Title()
{
	if (engine->Get<nh::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nh::InputSystem::eKeyState::Pressed)
	{
		state = Game::eState::StartGame;
		auto title = scene->FindActor("Title");
		if (title)
		{
			title->active = false;
		}
	}
}

void Game::StartGame()
{
	rapidjson::Document doc;
	assert(nh::json::Load("scene.txt", doc));
	scene->Read(doc);

	nh::Tilemap tilemap;
	tilemap.scene = scene.get();
	assert(nh::json::Load("map.txt", doc));
	tilemap.Read(doc);
	tilemap.Create();

	state = Game::eState::StartLevel;
}

void Game::StartLevel()
{
	stateTimer += engine->time.deltaTime;
	if (stateTimer >= 1.0f)
	{
		stateTimer = 0;
		auto player = nh::ObjectFactory::Instance().Create<nh::Actor>("Player");
		player->transform.position = { 400, 250 };
		scene->AddActor(std::move(player));

		state = Game::eState::Level;
		coinSpawnTimer = 2.0f;
		enemySpawnTimer = 5.0f;
		powerUpSpawnTimer = 10.0f;
	}
}

void Game::Level()
{
	coinSpawnTimer -= engine->time.deltaTime;
	enemySpawnTimer -= engine->time.deltaTime;
	powerUpSpawnTimer -= engine->time.deltaTime;
	if (invincibilityTimer > 0) 
	{ 
		invincibilityTimer -= engine->time.deltaTime;

		if (invincibilityTimer <= 0.0f)
		{
			scene->FindActor("Player")->transform.scale = 2.0f;
			scene->FindActor("Player")->GetComponent<nh::RBPhysicsComponent>()->data.size = { 32, 48 };
		}
	}

	if (respawnTimer > 0)
	{
		respawnTimer -= engine->time.deltaTime;

		if (respawnTimer <= 0)
		{
			auto player = nh::ObjectFactory::Instance().Create<nh::Actor>("Player");
			player->transform.position = { 400, 250 };
			scene->AddActor(std::move(player));
		}
	}

	if (coinSpawnTimer <= 0.0f)
	{
		coinSpawnTimer = nh::RandomRange(2.0f, 4.0f);

		auto coin = nh::ObjectFactory::Instance().Create<nh::Actor>("Coin");
		coin->transform.position = { nh::RandomRange(100, 700), 150.0f };
		scene->AddActor(std::move(coin));
	}

	if (powerUpSpawnTimer <= 0.0f)
	{
		powerUpSpawnTimer = nh::RandomRange(12.0f, 14.0f);

		auto powerUp = nh::ObjectFactory::Instance().Create<nh::Actor>("PowerUp");
		powerUp->transform.position = { nh::RandomRange(100, 700), 150.0f };
		scene->AddActor(std::move(powerUp));
	}

	if (enemySpawnTimer <= 0.0f)
	{
		enemySpawnTimer = nh::RandomRange(4.0f, 6.0f);

		auto enemy = nh::ObjectFactory::Instance().Create<nh::Actor>("Bat");
		enemy->transform.position = { nh::RandomRange(100, 700), 150.0f };
		scene->AddActor(std::move(enemy));
	}
}

void Game::OnPlayerHit(const nh::Event& e)
{
	if (invincibilityTimer <= 0)
	{
		engine->Get<nh::AudioSystem>()->PlayAudio("hurt");
		auto a = scene->FindActor("Player");
		a->destroy = true;

		if (--lives > 0)
		{
			respawnTimer = 1.0f;
		}
		else
		{
			state = Game::eState::PlayerDead;
		}
	}
}

void Game::PlayerDead()
{
	scene->FindActor("GameOver")->active = true;
	state = Game::eState::GameOver;
}

void Game::GameOver()
{
	if (engine->Get<nh::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nh::InputSystem::eKeyState::Pressed)
	{
		state = Game::eState::Reset;
		scene->FindActor("Title")->active = false;
	}
}

void Game::OnAddScore(const nh::Event& e)
{
	score += std::get<int>(e.data);
}

void Game::OnInvincibility(const nh::Event& e)
{
	invincibilityTimer = 5.0f;
	scene->FindActor("Player")->transform.scale = 4.0f;
	scene->FindActor("Player")->GetComponent<nh::RBPhysicsComponent>()->data.size = { 64, 96 };

	OnAddScore(e);
}
