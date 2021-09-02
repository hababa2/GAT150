#pragma once

#include "Engine.h"

class Game
{
public: 
	enum class eState
	{
		Reset,
		Title,
		StartGame,
		StartLevel,
		Level,
		PlayerDead,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool IsQuit() { return quit; }

private:
	void Reset();
	void Title();
	void StartGame();
	void StartLevel();
	void Level();
	void PlayerDead();
	void GameOver();
	void OnPlayerHit(const nh::Event& e);
	void OnAddScore(const nh::Event& e);
	void OnInvincibility(const nh::Event& e);

public:
	std::unique_ptr<nh::Scene> scene;
	std::unique_ptr<nh::Engine> engine;

private:
	bool quit{ false };

	eState state = eState::Reset;
	float stateTimer = 0;
	float coinSpawnTimer = 0;
	float enemySpawnTimer = 0;
	float respawnTimer = 0;
	float invincibilityTimer = 0;
	float powerUpSpawnTimer = 0;
	int score = 0;
	int lives = 3;
};