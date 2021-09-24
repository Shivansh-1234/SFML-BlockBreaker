#pragma once

#include <sstream>
#include "SplashScreenState.h"
#include "MainMenuState.h"
#include "DEFINITIONS.h"
#include <iostream>


SplashScreenState::SplashScreenState(GameDataRef data) : _data(data) { }

void SplashScreenState::Init()
{
	this->_data->assetsManager.LoadTexture("SplashScreen_BG", SPLASH_SCREEN_BG_IMG);

	_background.setTexture(this->_data->assetsManager.GetTexture("SplashScreen_BG"));
}

void SplashScreenState::HandleInput()
{
	sf::Event ev;

	while (this->_data->window.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->_data->window.close();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				this->_data->window.close();
			break;
		default:
			break;
		}
	}
}

void SplashScreenState::Update(float dt)
{
	if (this->_clock.getElapsedTime().asSeconds() > SPLASHSCREEN_TIME)
	{
		_data->stateHandler.AddState(StateRef(new MainMenuState(this->_data)));
	}
}

void SplashScreenState::Render(float dt)
{
	this->_data->window.clear(sf::Color::Blue);
	this->_data->window.draw(this->_background);
	this->_data->window.display();
}
