#pragma once

#include <sstream>
#include "MainMenuState.h"
#include "GameState.h"
#include "DEFINITIONS.h"

#include <iostream>

MainMenuState::MainMenuState(GameDataRef data) : _data(data) { }

void MainMenuState::Init()
{
	this->_data->assetsManager.LoadTexture("Background", MAIN_MENU_SCREEN_BG_IMG);
	this->_data->assetsManager.LoadTexture("Title", MAIN_MENU_SCREEN_TITLE);
	this->_data->assetsManager.LoadTexture("Play Button", MAIN_MENU_SCREEN_PLAY);
	this->_data->assetsManager.LoadTexture("MADE BY SHIVANSH", MAIN_MENU_MADE_BY);

	this->_background.setTexture(this->_data->assetsManager.GetTexture("Background"));
	this->_title.setTexture(this->_data->assetsManager.GetTexture("Title"));
	this->_playButton.setTexture(this->_data->assetsManager.GetTexture("Play Button"));
	this->_madeby.setTexture(this->_data->assetsManager.GetTexture("MADE BY SHIVANSH"));

	this->_title.setPosition((SCREENWIDTH / 2) - (this->_title.getGlobalBounds().width / 2), this->_title.getGlobalBounds().height * 0.1);
	this->_playButton.setPosition((SCREENWIDTH / 2) - (this->_playButton.getGlobalBounds().width / 2), (SCREENHEIGHT / 2) - (this->_playButton.getGlobalBounds().height / 2));
	this->_madeby.setPosition((SCREENWIDTH / 2) - (this->_madeby.getGlobalBounds().width / 2), (SCREENHEIGHT)-this->_madeby.getGlobalBounds().height);
}

void MainMenuState::HandleInput()
{
	sf::Event ev;

	while (this->_data->window.pollEvent(ev))
	{
		if (sf::Event::Closed == ev.type)
		{
			this->_data->window.close();
		}

		if (this->CheckCollision(this->_playButton, sf::Mouse::Left, this->_data->window))
		{
			std::cout << "Game State" << std::endl;
			_data->stateHandler.AddState(StateRef(new GameState(this->_data)));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			this->_data->window.close();
		}
	}
}

void MainMenuState::Update(float dt)
{
}

void MainMenuState::Render(float dt)
{
	this->_data->window.clear(sf::Color::Blue);

	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_title);
	this->_data->window.draw(this->_playButton);
	this->_data->window.draw(this->_madeby);

	this->_data->window.display();
}

bool MainMenuState::CheckCollision(sf::Sprite obj, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect rect(obj.getPosition().x, obj.getPosition().y, obj.getGlobalBounds().width, obj.getGlobalBounds().height);

		if (rect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}

	return false;
}
