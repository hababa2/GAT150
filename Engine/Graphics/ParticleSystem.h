#pragma once

#include "Framework/System.h"
#include "Math/Vector2.h"
#include "Math/Color.h"


#include <vector>

namespace nh
{
	class ParticleSystem : public GraphicsSystem
	{
	private:
		struct Particle
		{
			Vector2	position;
			Vector2	prevPosition;
			Vector2	velocity;
			std::shared_ptr<class Texture> texture;
			float lifetime{ 0.0f };
			bool isActive{ false };

			static bool IsNotActive(Particle p) { return !p.isActive; }
		};

	public:
		void Startup() override;
		void Shutdown() override;

		void Update(float dt) override;
		void Draw(class Renderer* renderer) override;

		void Create(const Vector2& position, size_t count, float lifetime, const std::shared_ptr<Texture>& texture, float speed);
		//void Create(const Vector2& position, size_t count, float lifetime, const std::vector<Color>& colors, float speed, float angle, float angleRange);

	private:
		std::vector<Particle> particles;
	};
}