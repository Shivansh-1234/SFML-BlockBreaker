#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

class SplashScreenState : public State
{
private:
	GameDataRef _data;
	sf::Clock _clock;
	sf::Sprite _background;

public:
	SplashScreenState(GameDataRef data);
	void Init();

	void HandleInput();
	void Update(float dt);
	void Render(float dt);
};

