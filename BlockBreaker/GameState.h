#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "DEFINITIONS.h"

class GameState : public State
{
private:
	GameDataRef _data;

	sf::Sprite _background;
	sf::Sprite _player;
	sf::Sprite _ball;

	sf::Text _gameText;

	struct Brick
	{
		sf::Sprite brick;
		bool isActive;
		int level;
	};

	Brick* _brick[BRICK_COLUMN][BRICK_ROWS];
	sf::Vector2f brickPos;
	sf::Vector2f ballVelocity;

	float playerVelocity;
	int playerHealth;

	int brickCount;

	bool moveBall;
	
	void MovePlayer();
	void MoveBall();
	void BrickPhysics();
	bool CheckCollision(sf::Sprite rect, sf::Sprite circle);
public:
	GameState() { }
	GameState(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Render(float dt);
};

