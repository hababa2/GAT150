#include "Engine.h"
#include "Graphics\Renderer.h"

#include <SDL.h>
#include <SDL_Image.h>

#include <memory>
#include <iostream>

int main(int, char**)
{
	SDL_Point screen{ 800, 600 };

	nh::Engine engine;
	engine.Startup();

	engine.Get<nh::Renderer>()->Create("GAT150", screen.x, screen.y);

	nh::Scene scene;
	scene.engine = &engine;

	nh::SetFilePath("../Resources");

	std::shared_ptr<nh::Texture> texture = engine.Get<nh::ResourceSystem>()->Get<nh::Texture>("sf2.png", engine.Get<nh::Renderer>());

	for (int i = 0; i < 10; ++i)
	{
		nh::Transform transform{ {nh::RandomRangeInt(0, screen.x - 100), nh::RandomRangeInt(0, screen.y - 100)}, nh::RandomRange(0, 360), 1.0f };
		scene.AddActor(std::make_unique<nh::Actor>(transform, texture));
	}

	bool quit = false;
	SDL_Event event;

	while (!quit)
	{
		SDL_PollEvent(&event);

		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			screen.x = event.window.data1;
			screen.y = event.window.data1;
			break;
		case SDL_WINDOWEVENT_CLOSE:
			quit = true;
		}

		//Update
		engine.Update();
		scene.Update(engine.time.deltaTime);
		quit |= (engine.Get<nh::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nh::InputSystem::eKeyState::Pressed);

		//Draw
		engine.Get<nh::Renderer>()->BeginFrame();
		scene.Draw(engine.Get<nh::Renderer>());
		engine.Get<nh::Renderer>()->EndFrame();
	}
	
	SDL_Quit();
	return 0;
}

