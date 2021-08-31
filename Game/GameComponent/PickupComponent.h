#pragma once

#include "Component\Component.h"
#include "Framework\EventSystem.h"

#include <list>

class PickupComponent : public nh::Component
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<PickupComponent>(*this); }
	virtual ~PickupComponent();

	void Create() override;
	virtual void Update() override {}

	void OnCollisionEnter(const nh::Event& e);

	bool Write(const rapidjson::Value& value) const override;
	bool Read(const rapidjson::Value& value) override;
};