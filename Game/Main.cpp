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

		if (event.type == SDL_WINDOWEVENT)
		{
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				screen.x = event.window.data1;
				screen.y = event.window.data1;
				break;
			}
		}
		else
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
		}

		engine.Update(0.0f);
		quit = (engine.Get<nh::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nh::InputSystem::eKeyState::Pressed);

		scene.Update(0.0f);

		engine.Get<nh::Renderer>()->BeginFrame();

		scene.Draw(engine.Get<nh::Renderer>());

		engine.Get<nh::Renderer>()->EndFrame();
	}
	
	SDL_Quit();
	return 0;
}

