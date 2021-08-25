#include "PlayerComponent.h"
#include "Engine.h"

using namespace nh;

void PlayerComponent::Update()
{
    PhysicsComponent* pc = owner->GetComponent<PhysicsComponent>();
    assert(pc);

    Vector2 force{ ((owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held) - 
        (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held)) * speed,
        ((owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == InputSystem::eKeyState::Pressed)) * -300.0f };

    pc->ApplyForce(force);
}

bool PlayerComponent::Write(const rapidjson::Value& value) const
{
    return false;
}

bool PlayerComponent::Read(const rapidjson::Value& value)
{
    JSON_READ(value, speed);
    return true;
}
