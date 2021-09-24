#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

class PauseMenuState : public State
{
private:
	GameDataRef _data;

	sf::Sprite _background;
	sf::Sprite _homeButton;
	sf::Sprite _quitButton;

	sf::Text _title;
	sf::Text _guiText;
public:
	PauseMenuState(GameDataRef data);

	void Init();
	
	void HandleInput();
	void Update(float dt);
	void Render(float dt);
};

