#include "Game.h"
#include "SplashScreenState.h"

Game::Game(int screenWidth, int screenHeight, std::string title)
{
	_data->window.create(sf::VideoMode(screenWidth, screenHeight), title, sf::Style::Titlebar | sf::Style::Close);
	_data->window.setFramerateLimit(240);
	_data->stateHandler.AddState(StateRef(new SplashScreenState(this->_data)));

	this->Run();
}

void Game::Run()
{
	float newTime, frameTime, lerp;

	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->_data->window.isOpen())
	{
		this->_data->stateHandler.ProcessChanges();

		newTime = this->_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->_data->stateHandler.GetActiveState()->HandleInput();
			this->_data->stateHandler.GetActiveState()->Update(dt);

			accumulator -= dt;
		}

		lerp = accumulator / dt;
		this->_data->stateHandler.GetActiveState()->Render(lerp);
	}
}
