#include "Game.h"
#include "Core/json.h"

int main(int, char**)
{
	Game game;
	game.Initialize();

	rapidjson::Document document;
	bool success = nh::json::Load("json.txt", document);
	assert(success);

	std::string str;
	nh::json::Get(document, "string", str);
	std::cout << str << std::endl;
	
	bool b;
	nh::json::Get(document, "boolean", b);
	std::cout << b << std::endl;
	
	int i1;
	nh::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;
	
	int i2;
	nh::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;
	
	float f;
	nh::json::Get(document, "float", f);
	std::cout << f << std::endl;

	nh::Vector2 v2;
	nh::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;
	
	nh::Color color;
	nh::json::Get(document, "color", color);
	std::cout << color << std::endl;

	bool quit = false;
	SDL_Event event;

	while (!quit && !game.IsQuit())
	{
		SDL_PollEvent(&event);

		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			quit = true;
			break;
		}

		game.Update();
		game.Draw();
	}
	
	SDL_Quit();
	return 0;
}

