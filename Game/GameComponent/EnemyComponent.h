#pragma once

#include "Component\Component.h"

class EnemyComponent : public nh::Component
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<EnemyComponent>(*this); }

	virtual void Update() override;

	bool Write(const rapidjson::Value& value) const override;
	bool Read(const rapidjson::Value& value) override;

public:
	float speed{ 0.0f };
};