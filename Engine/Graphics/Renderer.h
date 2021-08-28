#pragma once

#include "Framework\System.h"
#include "Graphics\Texture.h"
#include "Math\Vector2.h"
#include "Math\Transform.h"

#include <SDL.h>

#include <string>

namespace nh
{
	class Renderer : public System
	{
	public:
		void Startup() override;
		void Shutdown() override;
		void Update(float dt) override;

		void Create(const std::string& name, int width, int height);
		void BeginFrame();
		void EndFrame();

		void Draw(std::shared_ptr<Texture> texture, const Vector2& pos, float angle = 0, const Vector2& scale = Vector2::one);
		void Draw(std::shared_ptr<Texture> texture, const Transform& transform);
		void Draw(std::shared_ptr<Texture> texture, const SDL_Rect& source, const Transform& transform);

	private:
		SDL_Renderer* renderer{ nullptr };
		SDL_Window* window{ nullptr };

		friend class Texture;
	};
}