#pragma once

#include "Object.h"
#include "Math\Transform.h"
#include "Component\Component.h"

#include <memory>
#include <vector>

namespace nh
{
	class Scene;
	class Renderer;

	class Actor : public Object
	{
	public:
		Actor() {}
		Actor(const Transform& transform) : transform{ transform } {}

		void Initialize() {};

		void Update(float dt);
		void Draw(Renderer* renderer);

		void OnCollision(Actor* actor) {}

		void AddChild(std::unique_ptr<Actor> a);

		float GetRadius();

		void AddComponent(std::unique_ptr<Component> component);

	public:
		bool destroy{ false };
		std::string tag;

		Transform transform;
		Scene* scene{ nullptr };

		Actor* parent{ nullptr };
		std::vector<std::unique_ptr<Actor>> children;

		std::vector<std::unique_ptr<Component>> components;
	};
}