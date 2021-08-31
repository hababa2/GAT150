#pragma once

#include "Component\Component.h"
#include "Framework\EventSystem.h"

#include <list>

class PlayerComponent : public nh::Component
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<PlayerComponent>(*this); }
	virtual ~PlayerComponent();

	void Create() override;
	virtual void Update() override;

	void OnCollisionEnter(const nh::Event& e);
	void OnCollisionExit(const nh::Event& e);

	bool Write(const rapidjson::Value& value) const override;
	bool Read(const rapidjson::Value& value) override;

public:
	float speed{ 0.0f };
	
private:
	std::list<nh::Actor*> contacts;
};