#pragma once

#include "Engine.h"

class Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver,
	};

public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool IsQuit() { return quit; }

private:
	void UpdateTitle(float dt);
	void UpdateStartLevel(float dt);
	void UpdateGame(float dt);
	void OnAddPoints(const nh::Event& e);
	void OnPlayerHit(const nh::Event& e);
	void OnEnemyHit(const nh::Event& e);

public:
	std::unique_ptr<nh::Scene> scene;
	std::unique_ptr<nh::Engine> engine;

private:
	eState state = eState::Title;
	float stateTimer{ 0.0f };

	float iFrameCounter{ 0.0f };
	float spawnerTimer{ 5.0f };
	bool notSpawned{ false };

	unsigned int score{ 0 };
	unsigned int highScore{ 0 };
	unsigned char lives{ 0 };

	bool quit{ false };
	nh::AudioChannel musicChannel;
	std::shared_ptr<nh::Font> font;
};

