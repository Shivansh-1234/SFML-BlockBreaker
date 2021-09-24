#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

class MainMenuState : public State
{
private:
	GameDataRef _data;
	
	sf::Sprite _background;
	sf::Sprite _playButton;
	sf::Sprite _title;
	sf::Sprite _madeby;
public:
	MainMenuState() { }
	MainMenuState(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Render(float dt);
	bool CheckCollision(sf::Sprite obj, sf::Mouse::Button button, sf::RenderWindow &window);
};

