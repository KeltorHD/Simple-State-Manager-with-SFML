#pragma once

#include "states/state.hpp"

class MainMenuState final:
	public State
{
public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	void render(sf::RenderTarget* target = nullptr) override;

	void update(const float& dt) override;

private:
	/*var*/
	sf::Text text;
	sf::Font font;

	void initVariables();
	void initKeybinds();

	//func
	void updateInput(const float& dt) override;
};