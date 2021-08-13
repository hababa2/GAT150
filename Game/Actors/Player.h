#pragma once

#include "Object\Actor.h"
#include "Math\Vector2.h"

class Player : public nh::Actor
{
public:
	Player(const nh::Transform& transform, std::shared_ptr<nh::Texture> texture, float speed);

	void Initialize() override;
	void Update(float dt) override;

	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ 0.0f };
	float fireRate{ 0.4f };
	float turnSpeed{ 3.0f };
	float speed{ 150.0f };
	nh::Vector2 velocity{ 0.0f };
};