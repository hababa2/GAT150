#include "Tilemap.h"

#include "Engine.h"

void nh::Tilemap::Create()
{
	for (int i = 0; i < tiles.size(); ++i)
	{
		int index = tiles[i];

		if (!index) { continue; }

		auto a = ObjectFactory::Instance().Create<Actor>(tileNames[index]);

		if (a)
		{
			int x = i % tilesX;
			int y = i / tilesX;

			a->transform.position = start + nh::Vector2{ x, y } * size;
			scene->AddActor(std::move(a));
		}
	}
}

bool nh::Tilemap::Write(const rapidjson::Value& value) const
{
	return false;
}

bool nh::Tilemap::Read(const rapidjson::Value& value)
{
	JSON_READ(value, tilesX);
	JSON_READ(value, tilesY);
	JSON_READ(value, size);
	JSON_READ(value, start);
	JSON_READ(value, tileNames);
	JSON_READ(value, tiles);

	return true;
}
