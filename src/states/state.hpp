#pragma once

#include "programSettings/programSettings.hpp"

class State;

class StateData
{
public:
	StateData();

	//var
	sf::RenderWindow* window;
	ProgramSettings* programSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
};

class State
{
public:
	State(StateData* state_data);
	virtual ~State();

	//accessors
	const bool& getQuit() const;
	const bool getKeyTime();

	//func
	void endState();
	void pauseState();
	void unpauseState();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
	StateData* stateData;
	std::stack<State*>* states;

	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keyTime;
	float keyTimeMax;
	
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Func
	virtual void initKeybinds() = 0;

	virtual void updateMousePositions(sf::View* view = nullptr);
	virtual void updateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;

};