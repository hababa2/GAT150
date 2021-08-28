#include "TextComponent.h"
#include "Engine.h"

void nh::TextComponent::Update()
{

}

void nh::TextComponent::Draw(Renderer* renderer)
{
    renderer->Draw(texture, owner->transform);
}

void nh::TextComponent::SetText(const std::string& text)
{
    texture->Create(font->CreateSurface(text, color));
}

bool nh::TextComponent::Write(const rapidjson::Value& value) const
{
    return false;
}

bool nh::TextComponent::Read(const rapidjson::Value& value)
{
    JSON_READ(value, fontName);
    JSON_READ(value, fontSize);
    JSON_READ(value, color);
    JSON_READ(value, text);

    font = owner->scene->engine->Get<ResourceSystem>()->Get<Font>(fontName, &fontSize);
    texture = owner->scene->engine->Get<ResourceSystem>()->Get<Texture>("texture", owner->scene->engine->Get<Renderer>());

    SetText(text);

    return true;
}
