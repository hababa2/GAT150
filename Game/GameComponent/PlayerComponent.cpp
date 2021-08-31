#include "PlayerComponent.h"
#include "Engine.h"

using namespace nh;

PlayerComponent::~PlayerComponent()
{
    owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
    owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}

void PlayerComponent::Create()
{
    owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
    owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), owner);

    owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt", "Audio/hurt.wav");
}

void PlayerComponent::Update()
{
    PhysicsComponent* pc = owner->GetComponent<PhysicsComponent>();
    assert(pc);

    Vector2 force{ ((owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held) - 
        (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held)) * speed,
        ((owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == InputSystem::eKeyState::Pressed)) * -1000.0f *
        (contacts.size() > 0)};

    pc->ApplyForce(force);

    SpriteAnimationComponent* sac = owner->GetComponent<SpriteAnimationComponent>();
    assert(sac);
    if (pc->velocity.x > 0) { sac->StartSequence("walk_right"); }
    else if (pc->velocity.x < 0) { sac->StartSequence("walk_left"); }
    else { sac->StartSequence("idle"); }
}

void PlayerComponent::OnCollisionEnter(const Event& e)
{
    Actor* a = reinterpret_cast<Actor*>(std::get<void*>(e.data));

    if (ICompare(a->tag, "ground")) { contacts.push_back(a); }

    if (ICompare(a->tag, "enemy")) { owner->scene->engine->Get<AudioSystem>()->PlayAudio("hurt"); }
}

void PlayerComponent::OnCollisionExit(const Event& e)
{
    Actor* a = reinterpret_cast<Actor*>(std::get<void*>(e.data));

    if (ICompare(a->tag, "ground")) { contacts.remove(a); }
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
