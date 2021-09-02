#pragma once

//Core
#include "Core\Utilities.h"
#include "Core\FileSystem.h"
#include "Core\Timer.h"
#include "Core\Serializable.h"

//Math
#include "Math\Vector2.h"
#include "Math\Color.h"
#include "Math\Random.h"
#include "Math\MathUtils.h"
#include "Math\Transform.h"

//Framework
#include "Framework\EventSystem.h"
#include "Framework\Singleton.h"
#include "Framework\Factory.h"

//Graphics
#include "Graphics\Font.h"
#include "Graphics\Renderer.h"
#include "Graphics\Texture.h"
#include "Graphics\ParticleSystem.h"

//Physics
#include "Physics\PhysicsSystem.h"

//Audio
#include "Audio\AudioSystem.h"

//Input
#include "Input\InputSystem.h"

//Resource
#include "Resource\ResourceSystem.h"

//Objects
#include "Object\Actor.h"
#include "Object\Scene.h"
#include "Object\Tilemap.h"

//Components
#include "Component\SpriteAnimationComponent.h"
#include "Component\PhysicsComponent.h"
#include "Component\RBPhysicsComponent.h"
#include "Component\AudioComponent.h"
#include "Component\TextComponent.h"

#include <vector>
#include <memory>
#include <algorithm>

#include "box2d\box2d.h"

#define REGISTER_CLASS(T) nh::ObjectFactory::Instance().Register<T>(#T)

namespace nh
{
	typedef Singleton<Factory<std::string, Object>> ObjectFactory;

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