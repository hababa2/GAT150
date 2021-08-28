#include "EnemyComponent.h"
#include "Engine.h"

using namespace nh;

void EnemyComponent::Update()
{
    Actor* player = owner->scene->FindActor("Player");
    if (player)
    {
        PhysicsComponent* pc = owner->GetComponent<PhysicsComponent>();
        assert(pc);

        Vector2 dir = player->transform.position - owner->transform.position;

        pc->ApplyForce(dir.Normalized() * speed);
    }
}

bool EnemyComponent::Write(const rapidjson::Value& value) const
{
    return false;
}

bool EnemyComponent::Read(const rapidjson::Value& value)
{
    JSON_READ(value, speed);
    return true;
}
