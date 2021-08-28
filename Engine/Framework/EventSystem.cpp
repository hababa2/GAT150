#include "EventSystem.h"
#include "Object\Object.h"

namespace nh
{
	void EventSystem::Startup()
	{

	}

	void EventSystem::Shutdown()
	{

	}

	void EventSystem::Update(float dt)
	{
		
	}

	void EventSystem::Subscribe(const std::string& name, function_t fn, Object* receiver)
	{
		observers[name].push_back({ fn, receiver });
	}

	void EventSystem::Notify(const Event& e)
	{
		auto& eventObservers = observers[e.name];

		for (const auto& o : eventObservers)
		{
			if (e.receiver == nullptr || e.receiver == o.receiver)
			{
				o.fn(e);
			}
		}
	}
}