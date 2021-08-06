#pragma once

#include "Resource\Resource.h"
#include "Math\Vector2.h"

#include <SDL_image.h>

namespace nh
{
	class Texture : public Resource
	{
	public:
		bool Load(const std::string& filename, void* data) override;

		Vector2 GetSize() const;

	private:
		SDL_Texture* texture{ nullptr };
		SDL_Renderer* renderer{ nullptr };

		friend class Renderer;
	};
}