#include "pch.h"
#include "program.hpp"

void Program::initVariables()
{
	this->window = nullptr;
	this->dt = 0;
}

void Program::initGraphicsSettings()
{
	this->programSettings.loadFromFile("config/graphics.ini");
}

//Initializer func
void Program::initWindow()
{
	sf::ContextSettings st;

	if (this->programSettings.fullscreen)
		this->window = new sf::RenderWindow(
			this->programSettings.resolution,
			this->stateData.programSettings->title,
			sf::Style::Fullscreen, st);
	else
		this->window = new sf::RenderWindow(
			this->programSettings.resolution,
			this->stateData.programSettings->title,
			sf::Style::Titlebar | sf::Style::Close, st);

	this->window->setFramerateLimit(this->programSettings.framerateLimit);
	this->window->setVerticalSyncEnabled(this->programSettings.verticalSync);

	this->stateData.window = this->window; /*связываем окно в program с stateData*/
}

void Program::initKeys()
{
	std::ifstream ifs("config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int value = 0;
		while (ifs >> key >> value)
		{
			this->supportedKeys[key] = std::move(value);
		}
	}

	ifs.close();

	//Debug remove later
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}

void Program::initStateData()
{
	this->stateData.programSettings = &this->programSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
}

void Program::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}


//Constructor/Destructor


Program::Program()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initStateData();
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Program::~Program()
{
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}

	delete this->window;
}


//func
void Program::endApplication()
{
	std::cout << "Ending Application!\n";
}

void Program::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Program::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Program::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else //App end
	{
		this->endApplication();
		this->window->close();
	}

}

void Program::render()
{
	this->window->clear();

	//render items
	if (!this->states.empty())
	{
		this->states.top()->render();
	}

	this->window->display();
}

void Program::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
