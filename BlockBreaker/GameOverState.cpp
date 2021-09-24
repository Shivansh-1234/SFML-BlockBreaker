#pragma once

#include <sstream>
#include "GameOverState.h"
#include "DEFINITIONS.h"
#include "GameState.h"
#include "MainMenuState.h"

#include <iostream>

GameOverState::GameOverState(GameDataRef data) : _data(data) { }

void GameOverState::Init()
{
	this->_data->assetsManager.LoadTexture("GameOver_Background", PAUSE_BACKGROUND);
	this->_data->assetsManager.LoadTexture("Resume_Button", PAUSE_HOME_BUTTON);
	this->_data->assetsManager.LoadTexture("Quit_Button", PAUSE_QUIT_BUTTON);
	this->_data->assetsManager.LoadFont("Title_text", PAUSE_TITLE_FONT);
	this->_data->assetsManager.LoadFont("Gui_text", PAUSE_GUI_FONT);

	this->_background.setTexture(this->_data->assetsManager.GetTexture("GameOver_Background"));
	this->_homeButton.setTexture(this->_data->assetsManager.GetTexture("Resume_Button"));
	this->_quitButton.setTexture(this->_data->assetsManager.GetTexture("Quit_Button"));
	this->_title.setFont(this->_data->assetsManager.GetFont("Title_text"));
	this->_guiText.setFont(this->_data->assetsManager.GetFont("Gui_text"));
	this->_scoreText.setFont(this->_data->assetsManager.GetFont("Gui_text"));

	this->_quitButton.setScale(1.5f, 1.5f);
	this->_homeButton.setScale(1.5f, 1.5f);

	this->_title.setOrigin(this->_title.getGlobalBounds().width / 2, this->_title.getGlobalBounds().height / 2);
	this->_guiText.setOrigin(this->_guiText.getGlobalBounds().width / 2, this->_guiText.getGlobalBounds().height / 2);
	this->_scoreText.setOrigin(this->_scoreText.getGlobalBounds().width / 2, this->_scoreText.getGlobalBounds().height / 2);

	this->_homeButton.setPosition((SCREENWIDTH / 2) - (this->_homeButton.getGlobalBounds().width * 1.5f), (SCREENHEIGHT / 2));
	this->_quitButton.setPosition((SCREENWIDTH / 2) + (this->_quitButton.getGlobalBounds().width * 0.5f), (SCREENHEIGHT / 2));
	this->_title.setPosition((SCREENWIDTH / 2) - (this->_quitButton.getGlobalBounds().width * 1.7f), this->_title.getGlobalBounds().height * 0.1f);
	this->_guiText.setPosition((SCREENWIDTH / 2) - (this->_quitButton.getGlobalBounds().width), (SCREENHEIGHT / 1.5f) - this->_quitButton.getGlobalBounds().height);
	this->_scoreText.setPosition((SCREENWIDTH / 2.2f), (SCREENHEIGHT / 2.f) - this->_quitButton.getGlobalBounds().height);

	this->_title.setCharacterSize(80);
	this->_guiText.setCharacterSize(40);
	this->_scoreText.setCharacterSize(30);

	this->_title.setFillColor(sf::Color::Red);
	this->_guiText.setFillColor(sf::Color::Red);
	this->_scoreText.setFillColor(sf::Color::Blue);

	this->_title.setString("THANKS FOR PLAYING ! ");
	this->_guiText.setString("PRESS SPACEBAR TO RESTART");
}

void GameOverState::HandleInput()
{
	sf::Event ev;
	MainMenuState mm;

	while (this->_data->window.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->_data->window.close();
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				this->_data->stateHandler.AddState(StateRef(new GameState(_data)));
			break;
		}

		if (mm.CheckCollision(this->_homeButton, sf::Mouse::Left, this->_data->window))
		{
			this->_data->stateHandler.AddState(StateRef(new MainMenuState(_data)), true);
		}

		if (mm.CheckCollision(this->_quitButton, sf::Mouse::Left, this->_data->window))
		{
			this->_data->window.close();
		}
	}
}

void GameOverState::Update(float dt)
{
}

void GameOverState::Render(float dt)
{
	this->_data->window.clear(sf::Color::Blue);

	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_homeButton);
	this->_data->window.draw(this->_quitButton);
	this->_data->window.draw(this->_title);
	this->_data->window.draw(this->_guiText);
	this->_data->window.draw(this->_scoreText);

	this->_data->window.display();
}
