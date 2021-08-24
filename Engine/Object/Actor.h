#pragma once

#include "Object.h"
#include "Math\Transform.h"
#include "Component\Component.h"
#include "Core\Serializable.h"

#include <memory>
#include <vector>

namespace nh
{
	class Scene;
	class Renderer;

	class Actor : public Object, public ISerializable
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

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void AddComponent(std::unique_ptr<Component> cmp);
		template<typename T>
		T* AddComponent();

	public:
		bool destroy{ false };
		std::string tag;

		Transform transform;
		Scene* scene{ nullptr };

		Actor* parent{ nullptr };
		std::vector<std::unique_ptr<Actor>> children;

		std::vector<std::unique_ptr<Component>> components;
	};

	template<typename T>
	inline T* Actor::AddComponent()
	{
		std::unique_ptr<T> component = std::make_unique<T>();

		component->owner = this;
		T* c = component.get();
		components.push_back(std::move(component));

		return c;
	}
}