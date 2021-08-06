#include "Scene.h"

#include "Actor.h"

namespace nh
{
	void Scene::Update(float dt)
	{
		for (auto it = actors.begin(); it != actors.end();)
		{
			(*it)->Update(dt);
			auto it2 = it;
			++it2;
			for (; it2 != actors.end(); ++it2)
			{
				if ((!it->get()->destroy && !it2->get()->destroy) && 
					nh::Vector2::Distance((*it)->transform.position, (*it2)->transform.position) < (it->get()->GetRadius() + it2->get()->GetRadius()))
				{
					it->get()->OnCollision(it2->get());
					it2->get()->OnCollision(it->get());
				}
			}

			if ((*it)->destroy) { it = actors.erase(it); }
			else { ++it; }
		}
	}

	void Scene::Draw(Renderer* renderer)
	{
		for (auto& a : actors)
		{
			a->Draw(renderer);
		}
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor->scene = this;
		actors.push_back(std::move(actor));
	}

	void Scene::RemoveActor(Actor* actor)
	{
		for (auto it = actors.begin(); it != actors.end(); ++it)
		{
			if ((*it).get() == actor) { actors.erase(it); return; }
		}
	}

	void Scene::RemoveAll()
	{
		actors.clear();
	}
}