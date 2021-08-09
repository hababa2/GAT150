#include "Actor.h"

#include "Graphics\Texture.h"
#include "Graphics\Renderer.h"
#include "Math/MathUtils.h"

namespace nh
{
	void Actor::Update(float dt)
	{
		transform.rotation += 180.0f * dt;
		transform.Update();

		for (auto& c : children)
		{
			c->transform.Update(transform.matrix);
		}
	}

	void Actor::Draw(Renderer* renderer)
	{
		renderer->Draw(texture, transform);
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