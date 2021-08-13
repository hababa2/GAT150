#pragma once

#include "Object\Actor.h"

class Projectile : public nh::Actor
{
public:
	Projectile(const nh::Transform& transform, std::shared_ptr<nh::Texture> texture, float speed) : nh::Actor{ transform, texture }, speed{ speed }{}

	void Update(float dt) override;

private:
	float lifetime{ 2.0f };
	float speed{ 200.0f };
};