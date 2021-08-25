#include "Game.h"
#include "GameComponent\PlayerComponent.h"

void Game::Initialize()
{
	engine = std::make_unique<nh::Engine>();
	engine->Startup();
	engine->Get<nh::Renderer>()->Create("GAT150", 800, 600);

	REGISTER_CLASS(PlayerComponent);

	scene = std::make_unique<nh::Scene>();
	scene->engine = engine.get();

	nh::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nh::SetFilePath("../Resources");

	rapidjson::Document doc;
	assert(nh::json::Load("scene.txt", doc));
	scene->Read(doc);
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