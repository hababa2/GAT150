#include "SpriteAnimationComponent.h"

#include "Engine.h"

namespace nh
{
	void SpriteAnimationComponent::Update()
	{
		frameTime = 1.0f / fps;

		if ((frameTimer += owner->scene->engine->time.deltaTime) >= frameTime)
		{ 
			frameTimer = 0.0f;

			if (++frame > endFrame)
			{
				frame = startFrame;
			}

			//++frame = frame * (frame < endFrame) + startFrame * (frame >= endFrame);
		}

		Vector2 frameSize = texture->GetSize() / Vector2{ framesX, framesY };

		rect.x = static_cast<int>((frame % framesX) * frameSize.x); 
		rect.y = static_cast<int>((frame / framesX) * frameSize.y);
		rect.w = static_cast<int>(frameSize.x);
		rect.h = static_cast<int>(frameSize.y);
	}

	void SpriteAnimationComponent::Draw(Renderer* renderer)
	{
		renderer->Draw(texture, rect, owner->transform);
	}

	void SpriteAnimationComponent::StartSequence(const std::string& name)
	{
		if (sequenceName == name) { return; }

		sequenceName = name;

		if (sequences.find(name) != sequences.end())
		{
			Sequence sequence = sequences[name];
			startFrame = sequence.startFrame;
			endFrame = sequence.endFrame;
			fps = sequence.fps;

			frame = startFrame;
		}
	}

	bool SpriteAnimationComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool SpriteAnimationComponent::Read(const rapidjson::Value& value)
	{
		SpriteComponent::Read(value);

		JSON_READ(value, fps);
		JSON_READ(value, framesX);
		JSON_READ(value, framesY);
		JSON_READ(value, startFrame);
		JSON_READ(value, endFrame);

		endFrame += (framesX * framesY - 1) * (!endFrame);
		frame = startFrame;

		if (value.HasMember("sequences") && value["sequences"].IsArray())
		{
			for (auto& s : value["sequences"].GetArray())
			{
				std::string name;
				JSON_READ(s, name);

				Sequence seq;
				JSON_READ(s, seq.fps);
				JSON_READ(s, seq.startFrame);
				JSON_READ(s, seq.endFrame);

				sequences[name] = seq;
			}

			std::string defaultSequence;
			JSON_READ(value, defaultSequence);
			StartSequence(defaultSequence);
		}

		return true;
	}
}
