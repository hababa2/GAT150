#include "Engine.h"
#include "Graphics\Renderer.h"
#include "Graphics\Font.h"

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

	engine.Get<nh::AudioSystem>()->AddAudio("Explosion", "Audio/explosion.wav");
	engine.Get<nh::AudioSystem>()->AddAudio("Laser", "Audio/laser.wav");
	engine.Get<nh::AudioSystem>()->AddAudio("Music", "Audio/music.wav");
	nh::AudioChannel channel = engine.Get<nh::AudioSystem>()->PlayAudio("Music", 1.0f, 1.0f, true);

	std::shared_ptr<nh::Texture> texture = engine.Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/sf2.png", engine.Get<nh::Renderer>());
	std::shared_ptr<nh::Texture> explosion = engine.Get<nh::ResourceSystem>()->Get<nh::Texture>("Textures/explosion.png", engine.Get<nh::Renderer>());

	int size = 32;
	std::shared_ptr<nh::Font> font = engine.Get<nh::ResourceSystem>()->Get<nh::Font>("Fonts/CHELON.ttf", &size);

	std::shared_ptr<nh::Texture> textTexture = std::make_shared<nh::Texture>(engine.Get<nh::Renderer>());
	textTexture->Create(font->CreateSurface("hello world", nh::Color{ 1, 1, 1 }));
	engine.Get<nh::ResourceSystem>()->Add("textTexture", textTexture);

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

		nh::Vector2 mousePos = engine.Get<nh::InputSystem>()->GetMousePosition();

		if (engine.Get<nh::InputSystem>()->GetButtonState((int)nh::InputSystem::eMouseButton::Left) == nh::InputSystem::eKeyState::Pressed)
		{
			engine.Get<nh::ParticleSystem>()->Create(mousePos, 10, 0.5f, explosion, 300.0f);
			engine.Get<nh::AudioSystem>()->PlayAudio("Explosion", 1, nh::RandomRange(0.2f, 2.0f), false);
			channel.SetPitch(nh::RandomRange(0.2f, 2.0f));
		}

		//Draw
		engine.Get<nh::Renderer>()->BeginFrame();

		scene.Draw(engine.Get<nh::Renderer>());
		engine.Draw(engine.Get<nh::Renderer>());
		nh::Transform t; 
		t.position = { 30, 30 }; 
		engine.Get<nh::Renderer>()->Draw(textTexture, t);

		engine.Get<nh::Renderer>()->EndFrame();
	}
	
	SDL_Quit();
	return 0;
}

