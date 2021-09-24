#pragma once

#include <sstream>
#include "GameState.h"
#include "MainMenuState.h"
#include "PauseMenuState.h"
#include "GameOverState.h"
#include <iostream>

GameState::GameState(GameDataRef data) : _data(data) { }

void GameState::Init()
{
	this->_data->assetsManager.LoadTexture( "Player", GAME_PLAYER);
	this->_data->assetsManager.LoadTexture( "Ball", GAME_BALL);
	this->_data->assetsManager.LoadTexture( "Background", GAME_BACKGROUND);
	this->_data->assetsManager.LoadTexture( "Brick", GAME_BRICK);
	this->_data->assetsManager.LoadFont("TextFont", GAME_FONT);

	this->_player.setTexture(this->_data->assetsManager.GetTexture("Player"));
	this->_ball.setTexture(this->_data->assetsManager.GetTexture("Ball"));
	this->_background.setTexture(this->_data->assetsManager.GetTexture("Background"));
	this->_gameText.setFont(this->_data->assetsManager.GetFont("TextFont"));

	this->brickCount = 0;

	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLUMN; j++)
		{
			this->_brick[j][i] = new Brick;
			this->_brick[j][i]->brick.setScale(1.3f,1.3f);
			this->_brick[j][i]->brick.setTexture(this->_data->assetsManager.GetTexture("Brick"));
			this->_brick[j][i]->isActive = true;
			this->_brick[j][i]->level = (rand() % 3);
			this->brickCount++;
		}
	}

	this->_player.setPosition((SCREENWIDTH / 2) - (this->_player.getGlobalBounds().width / 2), (SCREENHEIGHT)-this->_player.getGlobalBounds().height);
	this->_ball.setOrigin(this->_ball.getGlobalBounds().width/2, this->_ball.getGlobalBounds().height/2);
	this->_ball.setPosition((SCREENWIDTH / 2) - (this->_ball.getGlobalBounds().width / 2), (SCREENHEIGHT / 2) - (this->_ball.getGlobalBounds().height / 2) + (SCREENHEIGHT/3.5f));
	this->_gameText.setPosition(0.f, (SCREENHEIGHT)-this->_player.getGlobalBounds().height);

	this->_gameText.setCharacterSize(32);
	this->_gameText.setFillColor(sf::Color::Yellow);

	this->brickPos.x = BRICK_ROW_STARTING;
	this->brickPos.y = BRICK_COLUMN_STARTING;

	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLUMN; j++)
		{
			this->_brick[j][i]->brick.setPosition(brickPos);
			this->brickPos.x += BRICK_ROW_GAP;
		}
		this->brickPos.x = BRICK_ROW_STARTING;
		this->brickPos.y += BRICK_COLUMN_GAP;
	}
	
	this->playerVelocity = 15.f;
	this->ballVelocity.x = 10.4f;
	this->ballVelocity.y = 10.4f;
	this->playerHealth = 3;
	this->moveBall = false;
}

void GameState::HandleInput()
{
	sf::Event ev;

	while (this->_data->window.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->_data->window.close();
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				moveBall = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				_data->stateHandler.AddState(StateRef(new PauseMenuState(this->_data)), false);
			break;
		}
	}

	this->MovePlayer();
	this->MoveBall();
}

void GameState::Update(float dt)
{
	this->BrickPhysics();	

	std::stringstream ss;
	ss << "HEALTH : " << this->playerHealth << " / 3";
	this->_gameText.setString(ss.str());

	if (this->playerHealth == 0 || this->brickCount == 0)
	{
		_data->stateHandler.AddState(StateRef(new GameOverState(this->_data)));
	}
}

void GameState::Render(float dt)
{
	this->_data->window.clear(sf::Color::Blue);

	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_ball);
	this->_data->window.draw(this->_player);
	this->_data->window.draw(this->_gameText);

	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLUMN; j++)
		{
			if (this->_brick[j][i]->isActive)
				this->_data->window.draw(this->_brick[j][i]->brick);
		}
	}

	this->_data->window.display();
}

void GameState::MovePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->_player.move(-playerVelocity, 0.f);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->_player.move(playerVelocity, 0.f);

	if (this->_player.getPosition().x <= 0.f)
		this->_player.setPosition(0.f,this->_player.getPosition().y);
	if (this->_player.getPosition().x >= SCREENWIDTH - this->_player.getGlobalBounds().width)
		this->_player.setPosition(SCREENWIDTH - this->_player.getGlobalBounds().width, this->_player.getPosition().y);
}
void GameState::MoveBall()
{
	if (moveBall)
		this->_ball.move(-ballVelocity);

	if (this->_ball.getPosition().y < 0)
		this->ballVelocity.y *= -1;

	if (this->_ball.getPosition().x < 0)
		this->ballVelocity.x *= -1;

	if (this->_ball.getPosition().x > SCREENWIDTH - (this->_ball.getGlobalBounds().width/2))
		this->ballVelocity.x *= -1;

	if (this->_ball.getPosition().y > SCREENHEIGHT)
	{
		this->playerHealth--;
		this->_ball.setPosition((SCREENWIDTH / 2) - (this->_ball.getGlobalBounds().width / 2), (SCREENHEIGHT / 2) - (this->_ball.getGlobalBounds().height / 2) + (SCREENHEIGHT / 3.5f));
		this->ballVelocity.y *= -1;
		moveBall = false;
	}

	if (this->CheckCollision(this->_player, this->_ball))
	{
		this->ballVelocity.y *= -1;
		this->ballVelocity.x = -(((this->_ball.getPosition().x - (this->_player.getPosition().x + (this->_player.getGlobalBounds().width / 2))) / (this->_player.getGlobalBounds().width / 2))) * 10;
	}

	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLUMN; j++)
		{
			if (this->CheckCollision(this->_brick[j][i]->brick, this->_ball))
			{
				this->ballVelocity.y *= -1;
				this->_brick[j][i]->level--;

				if (this->_brick[j][i]->level < 0)
				{
					this->_brick[j][i]->isActive = false;
					this->brickCount--;
				}
				
			}
		}
	}
}

void GameState::BrickPhysics()
{
	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLUMN; j++)
		{
			switch (this->_brick[j][i]->level)
			{
			case 0:
				this->_brick[j][i]->brick.setColor(sf::Color::White);
				break;
			case 1:
				this->_brick[j][i]->brick.setColor(sf::Color::Blue);
				break;
			case 2:
				this->_brick[j][i]->brick.setColor(sf::Color::Red);
				break;
			default:
				this->_brick[j][i]->brick.setColor(sf::Color::White);
				break;
			}

			if (!this->_brick[j][i]->isActive)
				this->_brick[j][i]->brick.setPosition(-100.f, -100.f);
		}
	}

}

bool GameState::CheckCollision(sf::Sprite rectangle, sf::Sprite circle)
{
	if ((circle.getPosition().y + circle.getGlobalBounds().height/2) >= (rectangle.getPosition().y) &&
		(circle.getPosition().y - circle.getGlobalBounds().height / 2) < (rectangle.getPosition().y + (rectangle.getGlobalBounds().height)) &&
		(circle.getPosition().x + circle.getGlobalBounds().width / 2) > (rectangle.getPosition().x) &&
		(circle.getPosition().x - circle.getGlobalBounds().width / 2) < (rectangle.getPosition().x + (rectangle.getGlobalBounds().width)))
	{
		return true;
	}

return false;	
}

