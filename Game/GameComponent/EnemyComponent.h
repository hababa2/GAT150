#pragma once

#include "Component\Component.h"

class EnemyComponent : public nh::Component
{
public:
	virtual void Update() override;

	bool Write(const rapidjson::Value& value) const override;
	bool Read(const rapidjson::Value& value) override;

public:
	float speed{ 0.0f };
};