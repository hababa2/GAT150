#include "Game.h"

void Game::Initialize()
{
	engine = std::make_unique<nh::Engine>();
	engine->Startup();
	engine->Get<nh::Renderer>()->Create("GAT150", 800, 600);

	scene = std::make_unique<nh::Scene>();
	scene->engine = engine.get();

	nh::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nh::SetFilePath("../Resources");

	std::unique_ptr<nh::Actor> actor = std::make_unique<nh::Actor>(nh::Transform{ {400, 300} });

	std::unique_ptr<nh::SpriteComponent> sprtcmp = std::make_unique<nh::SpriteComponent>();
	sprtcmp->texture = engine->Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/Player.png", engine->Get<nh::Renderer>());

	std::unique_ptr<nh::PhysicsComponent> phscmp = std::make_unique<nh::PhysicsComponent>();
	phscmp->ApplyForce(nh::Vector2::right * 20);

	actor->AddComponent(std::move(sprtcmp));
	actor->AddComponent(std::move(phscmp));
	scene->AddActor(std::move(actor));
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
	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<nh::Renderer>()->BeginFrame();

	scene->Draw(engine->Get<nh::Renderer>());
	engine->Draw(engine->Get<nh::Renderer>());

	engine->Get<nh::Renderer>()->EndFrame();
}