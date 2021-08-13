#include "Actor.h"

#include "Graphics\Texture.h"
#include "Graphics\Renderer.h"
#include "Math/MathUtils.h"

namespace nh
{
	void Actor::Update(float dt)
	{
		transform.Update();

		for (auto& c : children)
		{
			c->transform.Update(transform.matrix);
		}
	}

	void Actor::Draw(Renderer* renderer)
	{
		if (texture) { renderer->Draw(texture, transform); }

		for (auto& c : children)
		{
			c->Draw(renderer);
		}
	}

	void Actor::AddChild(std::unique_ptr<Actor> a)
	{
		a->parent = this;
		children.push_back(std::move(a));
	}

	float Actor::GetRadius()
	{
		return (texture) ? texture->GetSize().Length() * 0.5f : 0.0f;
	}
}