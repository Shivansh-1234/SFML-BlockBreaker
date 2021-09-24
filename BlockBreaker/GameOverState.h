#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "DEFINITIONS.h"

class GameOverState : public State
{
private:
	GameDataRef _data;

	sf::Sprite _background;
	sf::Sprite _homeButton;
	sf::Sprite _quitButton;

	sf::Text _title;
	sf::Text _guiText;
	sf::Text _scoreText;
public:
	GameOverState(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Render(float dt);
};

