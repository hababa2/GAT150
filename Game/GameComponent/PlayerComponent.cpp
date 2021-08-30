#include "PlayerComponent.h"
#include "Engine.h"

using namespace nh;

void PlayerComponent::Create()
{
    owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
    owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), owner);

    owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt", "Audio/hurt.wav");
    owner->scene->engine->Get<AudioSystem>()->AddAudio("coin", "Audio/coin.wav");
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

    if(ICompare(a->tag, "coin")) 
    {
        owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");
        a->destroy = true;
    }
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
