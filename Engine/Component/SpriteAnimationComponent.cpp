#include "SpriteAnimationComponent.h"

#include "Engine.h"

namespace nh
{
	void SpriteAnimationComponent::Update()
	{
		frameTime = 1.0f / fps;

		if ((frameTimer += owner->scene->engine->time.deltaTime) >= frameTime)
		{ 
			frameTimer = 0.0f;
			++frame *= frame < framesX * framesY;
		}

		Vector2 frameSize = texture->GetSize() / Vector2{ framesX, framesY };

		rect.x = static_cast<int>((frame % framesX) * frameSize.x); 
		rect.y = static_cast<int>((frame / framesX) * frameSize.y);
		rect.w = static_cast<int>(frameSize.x);
		rect.h = static_cast<int>(frameSize.y);
	}

	void SpriteAnimationComponent::Draw(Renderer* renderer)
	{
		renderer->Draw(texture, rect, owner->transform);
	}
}
