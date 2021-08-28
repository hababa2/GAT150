#pragma once

#include "Component\SpriteComponent.h"

#include <SDL_image.h>

#include <map>

namespace nh
{
	class SpriteAnimationComponent : public SpriteComponent
	{
	private:
		struct Sequence
		{
			int fps{ 0 };
			int startFrame{ 0 };
			int endFrame{ 0 };
		};

	public:
		void Update() override;

		void Draw(Renderer* renderer) override;

		void StartSequence(const std::string& name);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		int frame{ 0 };
		int fps{ 24 };
		int framesX{ 0 };
		int framesY{ 0 };
		int startFrame{ 0 };
		int endFrame{ 0 };
		float frameTimer{ 0.0f };
		float frameTime{ 1.0f / 24 };
		SDL_Rect rect;

		std::map<std::string, Sequence> sequences;
		std::string sequenceName;
	};
}