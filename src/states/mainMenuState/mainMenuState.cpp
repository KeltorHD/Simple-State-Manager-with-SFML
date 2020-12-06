#include "pch.h"
#include "mainMenuState.hpp"


//Init func
void MainMenuState::initVariables()
{
	this->font.loadFromFile("font.ttf");

	this->text.setString("Hello world!");
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setOrigin
	(
		this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.f,
		this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.f
	);
	this->text.setPosition(this->stateData->programSettings->resolution.width / 2.f, this->stateData->programSettings->resolution.height / 2.f);
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(std::move(key2));
		}
	}

	ifs.close();
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initKeybinds();
}

MainMenuState::~MainMenuState()
{
	
}

void MainMenuState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->text);
}