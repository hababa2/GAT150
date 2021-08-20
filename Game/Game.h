#pragma once

#include "Engine.h"

class Game
{
public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool IsQuit() { return quit; }

public:
	std::unique_ptr<nh::Scene> scene;
	std::unique_ptr<nh::Engine> engine;

private:
	bool quit{ false };
};