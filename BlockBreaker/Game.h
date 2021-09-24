#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateHandler.h"
#include "AssetsManager.h"

struct GameData
{
	sf::RenderWindow window;
	StateHandler stateHandler;
	AssetsManager assetsManager;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
private:
	const float dt = 1.0f / 60.0f;
	sf::Clock _clock;

	GameDataRef _data = std::make_shared<GameData>();

	void Run();
public:
	Game(int screenWidth, int screenHeight , std::string title);
};

