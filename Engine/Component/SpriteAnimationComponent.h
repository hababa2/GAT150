#pragma once

#include "Component\SpriteComponent.h"

#include <SDL_image.h>

namespace nh
{
	class SpriteAnimationComponent : public SpriteComponent
	{
	public:
		void Update() override;

		void Draw(Renderer* renderer) override;

	public:
		int frame{ 0 };
		int fps{ 24 };
		int framesX{ 0 };
		int framesY{ 0 };
		float frameTimer{ 0.0f };
		float frameTime{ 1.0f / 24 };
		SDL_Rect rect;
	};
}