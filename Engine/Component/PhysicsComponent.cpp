#include "PhysicsComponent.h"

#include "Object\Actor.h"
#include "Engine.h"

namespace nh
{
	void PhysicsComponent::Update()
	{
		velocity += acceleration * owner->scene->engine->time.deltaTime;
		owner->transform.position += velocity * owner->scene->engine->time.deltaTime;
		owner->transform.position.x = (float)nh::Wrap((int)owner->transform.position.x, -10, 810);
		owner->transform.position.y = (float)nh::Wrap((int)owner->transform.position.y, -10, 810);
	}

	bool PhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool PhysicsComponent::Read(const rapidjson::Value& value)
	{
		return true;
	}
}
