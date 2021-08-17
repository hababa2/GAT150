#include "Actor.h"

#include "Graphics\Texture.h"
#include "Graphics\Renderer.h"
#include "Math/MathUtils.h"
#include "Component\GraphicsComponent.h"

namespace nh
{
	void Actor::Update(float dt)
	{
		for (auto& c : components)
		{
			c->Update();
		}

		transform.Update();

		for (auto& c : children)
		{
			c->transform.Update(transform.matrix);
		}
	}

	void Actor::Draw(Renderer* renderer)
	{
		for (auto& c : components)
		{
			GraphicsComponent* g;
			if (g = dynamic_cast<GraphicsComponent*>(c.get()))
			{
				g->Draw(renderer);
			}
		}

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
		return 0.0f;
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this;
		components.push_back(std::move(component));
	}
}