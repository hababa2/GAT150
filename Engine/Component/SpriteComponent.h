#pragma once

#include "Component\GraphicsComponent.h"

#include <memory>

namespace nh
{
	class SpriteComponent : public GraphicsComponent
	{
	public:
		void Update() override;
		void Draw(Renderer* renderer) override;

	public:
		std::shared_ptr<class Texture> texture;
	};
}