#include "Engine.h"

namespace nh 
{
	void Engine::Startup()
	{
		systems.push_back(std::make_unique<InputSystem>());
		systems.push_back(std::make_unique<EventSystem>());
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
	
	void Engine::Update(float dt)
	{
		for (auto& system : systems)
		{
			system->Update(dt);
		}
	}

	void Engine::Draw()
	{
		
	}
}