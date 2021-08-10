#include "Engine.h"

namespace nh 
{
	void Engine::Startup()
	{
		systems.push_back(std::make_unique<InputSystem>());
		systems.push_back(std::make_unique<EventSystem>());
		systems.push_back(std::make_unique<ParticleSystem>());
		systems.push_back(std::make_unique<Renderer>());
		systems.push_back(std::make_unique<ResourceSystem>());

		for (auto& system : systems)
		{
			system->Startup();
		}
	}
	
	void Engine::Shutdown()
	{
		for (auto& system : systems)
		{
			system->Shutdown();
		}
	}
	
	void Engine::Update()
	{
		time.Tick();

		for (auto& system : systems)
		{
			system->Update(time.deltaTime);
		}
	}

	void Engine::Draw(Renderer* renderer)
	{
		for (auto& system : systems)
		{
			GraphicsSystem* gs = dynamic_cast<GraphicsSystem*>(system.get());
			if (gs) { gs->Draw(renderer); }
		}
	}
}