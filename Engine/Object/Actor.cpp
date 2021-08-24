#include "Actor.h"

#include "Engine.h"

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

	void Actor::AddComponent(std::unique_ptr<Component> cmp)
	{
		cmp->owner = this;
		components.push_back(std::move(cmp));
	}

	bool Actor::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool Actor::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, tag);
		if (value.HasMember("transform"))
		{
			transform.Read(value["transform"]);
		}

		if (value.HasMember("components") && value["components"].IsArray())
		{
			for (auto& c : value["components"].GetArray())
			{
				std::string type;
				JSON_READ(c, type);

				auto component = ObjectFactory::Instance().Create<Component>(type);
				if (component)
				{
					component->owner = this;
					component->Read(c);
					AddComponent(std::move(component));
				}
			}
		}

		return true;
	}
}