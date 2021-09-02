#include "PickupComponent.h"
#include "Engine.h"

using namespace nh;

PickupComponent::~PickupComponent()
{
    owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
}

void PickupComponent::Create()
{
    owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PickupComponent::OnCollisionEnter, this, std::placeholders::_1), owner);

    owner->scene->engine->Get<AudioSystem>()->AddAudio("coin", "Audio/coin.wav");
}

void PickupComponent::OnCollisionEnter(const nh::Event& e)
{
    Actor* a = reinterpret_cast<Actor*>(std::get<void*>(e.data));
    
    if (ICompare(a->tag, "Player"))
    {
        owner->destroy = true;
        owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");

        Event e;

        if (ICompare(owner->name, "PowerUp"))
        {
            e.name = "invincibility";
            e.data = 100;
        }
        else
        {
            e.name = "add_score";
            e.data = 10;
        }

        owner->scene->engine->Get<EventSystem>()->Notify(e);
    }
}

bool PickupComponent::Write(const rapidjson::Value& value) const
{
    return false;
}

bool PickupComponent::Read(const rapidjson::Value& value)
{
    return true;
}

