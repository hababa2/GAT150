#pragma once

//Math
#include "Math\Vector2.h"
#include "Math\Color.h"
#include "Math\Random.h"
#include "Math\MathUtils.h"
#include "Math\Transform.h"

//Core
#include "Core\FileSystem.h"
#include "Core\Timer.h"

//Graphics
#include "Graphics\Renderer.h"
#include "Graphics\Texture.h"
#include "Graphics\ParticleSystem.h"

//Audio
#include "Audio\AudioSystem.h"

//Input
#include "Input\InputSystem.h"

//Framework
#include "Framework\EventSystem.h"

//Resource
#include "Resource\ResourceSystem.h"

//Objects
#include "Object\Actor.h"
#include "Object\Scene.h"

#include <vector>
#include <memory>
#include <algorithm>

namespace nh
{
	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update();

		void Draw(Renderer* renderer);

		template<typename T>
		T* Get();

	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get()
	{
		for (const auto& system : systems)
		{
			T* t = dynamic_cast<T*>(system.get());
			if (t) { return t; }
		}

		return nullptr;
	}
}