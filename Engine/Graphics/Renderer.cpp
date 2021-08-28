#include "Renderer.h"

#include "Math\MathUtils.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

namespace nh
{
	void Renderer::Startup()
	{
		if (SDL_Init(SDL_INIT_VIDEO))
		{
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		}

		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();
	}

	void Renderer::Shutdown()
	{
		TTF_Quit();
		IMG_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	void Renderer::Update(float dt)
	{

	}

	void Renderer::Create(const std::string& name, int width, int height)
	{
		window = SDL_CreateWindow(name.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (!window)
		{
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}

	void Renderer::BeginFrame()
	{
		SDL_RenderClear(renderer);
	}

	void Renderer::EndFrame()
	{
		SDL_RenderPresent(renderer);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Vector2& pos, float angle, const Vector2& scale)
	{
		Vector2 size = texture->GetSize() * scale;
		SDL_Rect dest{ (int)pos.x - (size.x / 2.0f), (int)pos.y - (size.y / 2.0f), (int)size.x, (int)size.y };

		SDL_RenderCopyEx(renderer, texture->texture, nullptr, &dest, RadToDeg(angle), nullptr, SDL_FLIP_NONE);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Transform& transform)
	{
		Vector2 size = texture->GetSize() * transform.scale;
		SDL_Rect dest{ (int)transform.position.x - (size.x / 2.0f), (int)transform.position.y - (size.y / 2.0f), (int)size.x, (int)size.y };

		SDL_RenderCopyEx(renderer, texture->texture, nullptr, &dest, RadToDeg(transform.rotation), nullptr, SDL_FLIP_NONE);
	}
	
	void Renderer::Draw(std::shared_ptr<Texture> texture, const SDL_Rect& source, const Transform& transform)
	{
		SDL_Rect dest{ (int)transform.position.x - source.w, (int)transform.position.y - source.h, 
			(int)source.w * transform.scale.x, (int)source.h * transform.scale.y };

		SDL_RenderCopyEx(renderer, texture->texture, &source, &dest, RadToDeg(transform.rotation), nullptr, SDL_FLIP_NONE);
	}
}