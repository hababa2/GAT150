#pragma once

#include "Object\Actor.h"

class Enemy : public nh::Actor
{
public:
	Enemy(const nh::Transform& transform, std::shared_ptr<nh::Texture> texture, float speed, bool shoots) : 
		nh::Actor{ transform, texture }, speed{ speed }, shoots{ shoots }{}

	void Update(float dt) override;

	void OnCollision(Actor* actor) override;

	int size{ 3 };
	bool shoots{ false };

private:
	float fireTimer{ 0.0f };
	float fireRate{ 1.0f };
	float speed{ 200.0f };
};