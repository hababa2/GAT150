#include "Game.h"

#include "Actors\Player.h"
#include "Actors\Enemy.h"

void Game::Initialize()
{
	engine = std::make_unique<nh::Engine>();
	engine->Startup();
	engine->Get<nh::Renderer>()->Create("GAT150", 800, 600);

	scene = std::make_unique<nh::Scene>();
	scene->engine = engine.get();

	nh::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nh::SetFilePath("../Resources");
	engine->Get<nh::AudioSystem>()->AddAudio("Explosion", "Audio/explosion.wav");
	engine->Get<nh::AudioSystem>()->AddAudio("Laser", "Audio/laser.wav");
	//engine->Get<nh::AudioSystem>()->AddAudio("Music", "Audio/music.wav");
	//musicChannel = engine->Get<nh::AudioSystem>()->PlayAudio("Music", 1.0f, 1.0f, true);

	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Background.jpg", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/explosion1.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/explosion2.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid23.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid22.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid21.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid13.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid12.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid11.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid03.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid02.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid01.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Player.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/PlayerLaser.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Alien.png", engine->Get<nh::Renderer>());
	engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/AlienLaser.png", engine->Get<nh::Renderer>());

	int size = 16;
	font = engine->Get<nh::ResourceSystem>()->Get<nh::Font>("Fonts/CHELON.ttf", &size);

	std::shared_ptr<nh::Texture> scoreText = std::make_shared<nh::Texture>(engine->Get<nh::Renderer>());
	scoreText->Create(font->CreateSurface(("Score: " + std::to_string(score)).c_str(), nh::Color::white));
	engine->Get<nh::ResourceSystem>()->Add("Score", scoreText);

	std::shared_ptr<nh::Texture> highScoreText = std::make_shared<nh::Texture>(engine->Get<nh::Renderer>());
	highScoreText->Create(font->CreateSurface(("High Score: " + std::to_string(highScore)).c_str(), nh::Color::white));
	engine->Get<nh::ResourceSystem>()->Add("HighScore", highScoreText);

	std::shared_ptr<nh::Texture> livesText = std::make_shared<nh::Texture>(engine->Get<nh::Renderer>());
	livesText->Create(font->CreateSurface(("Lives: " + std::to_string(3)).c_str(), nh::Color::white));
	engine->Get<nh::ResourceSystem>()->Add("Lives", livesText);

	std::shared_ptr<nh::Texture> topText = std::make_shared<nh::Texture>(engine->Get<nh::Renderer>());
	topText->Create(font->CreateSurface("ASEROIDS", nh::Color::blue));
	engine->Get<nh::ResourceSystem>()->Add("TopText", topText);

	std::shared_ptr<nh::Texture> bottomText = std::make_shared<nh::Texture>(engine->Get<nh::Renderer>());
	bottomText->Create(font->CreateSurface("PRESS SPACE TO START", nh::Color::blue));
	engine->Get<nh::ResourceSystem>()->Add("BottomText", bottomText);

	engine->Get<nh::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<nh::EventSystem>()->Subscribe("PlayerHit", std::bind(&Game::OnPlayerHit, this, std::placeholders::_1));
	engine->Get<nh::EventSystem>()->Subscribe("EnemyHit", std::bind(&Game::OnEnemyHit, this, std::placeholders::_1));

	state = eState::Title;
}

void Game::Shutdown()
{
	scene->RemoveAll();
	engine->Shutdown();
}

void Game::Update()
{
	float dt = engine->time.deltaTime;
	stateTimer += dt;

	switch (state)
	{
	case Game::eState::Title:
		UpdateTitle(dt);
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		UpdateStartLevel(dt);
		break;
	case Game::eState::Game:
		UpdateGame(dt);
		break;
	case Game::eState::GameOver:
		if (engine->Get<nh::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nh::InputSystem::eKeyState::Pressed)
		{ state = eState::StartGame; }
		break;
	default:
		break;
	}

	engine->Update();
	scene->Update(engine->time.deltaTime);
	quit |= (engine->Get<nh::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nh::InputSystem::eKeyState::Pressed);

	nh::Vector2 mousePos = engine->Get<nh::InputSystem>()->GetMousePosition();

	if (engine->Get<nh::InputSystem>()->GetButtonState((int)nh::InputSystem::eMouseButton::Left) == nh::InputSystem::eKeyState::Pressed)
	{
		engine->Get<nh::ParticleSystem>()->Create(mousePos, 1, 0.25f, 
			engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/explosion1.png"), 0.0f);
		engine->Get<nh::ParticleSystem>()->Create(mousePos, 10, 0.5f, 
			engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/explosion2.png"), 300.0f);
		engine->Get<nh::AudioSystem>()->PlayAudio("Explosion", 1, nh::RandomRange(0.2f, 2.0f), false);
		musicChannel.SetPitch(nh::RandomRange(0.2f, 2.0f));
	}
}

void Game::Draw()
{
	engine->Get<nh::Renderer>()->BeginFrame();

	engine->Get<nh::Renderer>()->Draw(engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Background.jpg"), 0.0f, 0.0f, 1.7f);
	scene->Draw(engine->Get<nh::Renderer>());
	engine->Draw(engine->Get<nh::Renderer>());
	engine->Get<nh::Renderer>()->Draw(engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Score"), nh::Transform{ {10, 10} }, false);
	engine->Get<nh::Renderer>()->Draw(engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("HighScore"), nh::Transform{ {10, 30} }, false);
	engine->Get<nh::Renderer>()->Draw(engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Lives"), nh::Transform{ {740, 10} }, false);

	switch (state)
	{
	case Game::eState::Title:
		engine->Get<nh::Renderer>()->Draw(engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("TopText"), 
			nh::Transform{ {400, 300 + static_cast<int>(std::sin(stateTimer * 3.0f) * 4.0f)} });
		engine->Get<nh::Renderer>()->Draw(engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("BottomText"), nh::Transform{ {400, 400} });
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		engine->Get<nh::Renderer>()->Draw(engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("TopText"),
			nh::Transform{ {400, 300 + static_cast<int>(std::sin(stateTimer * 3.0f) * 4.0f)} });
		engine->Get<nh::Renderer>()->Draw(engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("BottomText"), nh::Transform{ {400, 400} });
		break;
	default:
		break;
	}

	engine->Get<nh::Renderer>()->EndFrame();
}

void Game::UpdateTitle(float dt)
{
	if (engine->Get<nh::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nh::InputSystem::eKeyState::Pressed) { state = eState::StartGame; }
}

void Game::UpdateStartLevel(float dt)
{
	std::shared_ptr<nh::Texture> scoreText = engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Score");
	scoreText->Create(font->CreateSurface(("Score: " + std::to_string(score)).c_str(), nh::Color::white));
	engine->Get<nh::ResourceSystem>()->Add("Score", scoreText);

	scene->RemoveAll();

	scene->AddActor(std::make_unique<Player>(nh::Transform{ { 400, 300 }, 0.0f},
		engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Player.png"), 200.0f));
	scene->GetActor<Player>()->Initialize();
	notSpawned = false;

	for (size_t i = 0; i < 10; i++)
	{
		scene->AddActor(std::make_unique<Enemy>(nh::Transform{ { nh::RandomRange(-100.0f, 900.0f), nh::RandomRange(-100.0f, 700.0f) },
			nh::RandomRange(0.0f, nh::TwoPi)},
			engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid" + std::to_string(nh::RandomRangeInt(0, 2)) + "3.png"), 
			nh::RandomRange(10.0f, 100.0f), false));
	}

	state = eState::Game;
}

void Game::UpdateGame(float dt)
{
	if ((iFrameCounter -= dt) <= 0.0f && notSpawned)
	{
		notSpawned = false;
		scene->AddActor(std::make_unique<Player>(nh::Transform{ { 400, 300 }, 0.0f},
			engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Player.png"), 200.0f));
	}

	if ((spawnerTimer -= dt) <= 0.0f)
	{
		spawnerTimer = 5.0f;
		
		if ((rand() % 5) == 0)
		{
			scene->AddActor(std::make_unique<Enemy>(nh::Transform{ { nh::RandomRange(-100.0f, 900.0f), nh::RandomRange(-100.0f, 700.0f) },
			0.0f}, engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Alien.png"), 60.0f, true));
		}
		else
		{
			scene->AddActor(std::make_unique<Enemy>(nh::Transform{ { nh::RandomRange(-100.0f, 900.0f), nh::RandomRange(-100.0f, 700.0f) },
				nh::RandomRange(0.0f, nh::TwoPi)},
				engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid" + std::to_string(rand() % 3) + "3.png"), nh::RandomRange(10.0f, 100.0f), false));
		}
	}
}

void Game::OnAddPoints(const nh::Event& e)
{
	score += std::get<int>(e.data);
	highScore = nh::Max(score, highScore);

	std::shared_ptr<nh::Texture> scoreText = engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Score");
	scoreText->Create(font->CreateSurface(("Score: " + std::to_string(score)).c_str(), nh::Color::white));
	engine->Get<nh::ResourceSystem>()->Add("Score", scoreText);
	std::shared_ptr<nh::Texture> highScoreText = engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("HighScore");
	highScoreText->Create(font->CreateSurface(("High Score: " + std::to_string(highScore)).c_str(), nh::Color::white));
	engine->Get<nh::ResourceSystem>()->Add("HighScore", highScoreText);
}	


void Game::OnPlayerHit(const nh::Event& e)
{
	if (iFrameCounter <= 0.0f)
	{
		iFrameCounter = 1.0f;
	
		Player* p = scene->GetActor<Player>();
		engine->Get<nh::ParticleSystem>()->Create(p->transform.position, 1, 0.25f,
			engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/explosion1.png"), 0.0f);
		scene->engine->Get<nh::AudioSystem>()->PlayAudio("explosion");
		p->destroy = true;
		notSpawned = true;
	
		std::shared_ptr<nh::Texture> livesText = engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Lives");
		livesText->Create(font->CreateSurface(("Lives: " + std::to_string(--lives)).c_str(), nh::Color::white));
		engine->Get<nh::ResourceSystem>()->Add("Lives", livesText);

		if (lives == 0)
		{
			state = eState::GameOver;
		}
	}
}

void Game::OnEnemyHit(const nh::Event& e)
{
	Enemy* enemy = dynamic_cast<Enemy*>(std::get<nh::Actor*>(e.data));
	enemy->destroy = true;

	enemy->size--;

	if (enemy->size > 0 && !enemy->shoots)
	{
		nh::Transform t = enemy->transform;
		t.rotation = nh::RandomRange(0.0f, nh::TwoPi);

		for (int i = 0; i < 2; ++i)
		{
			std::unique_ptr newEnemy = std::make_unique<Enemy>(t, 
				engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Asteroid" + std::to_string(nh::RandomRangeInt(0, 2)) +
					std::to_string(enemy->size) + ".png"), nh::RandomRange(30.0f, 100.0f), false);
			newEnemy->size = enemy->size;
			scene->AddActor(std::move(newEnemy));
			t.rotation = nh::RandomRange(0.0f, nh::TwoPi);
		}
	}
}
