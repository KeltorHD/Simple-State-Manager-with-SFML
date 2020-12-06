#pragma once

class ProgramSettings
{
public:
	ProgramSettings();

	//variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned framerateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	//func
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};