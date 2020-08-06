#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <stack>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <ctime>

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	unsigned type;

public:
	Tile();
	Tile(unsigned int type);
	virtual ~Tile();

	// Functions
	unsigned short int returnType();
	void setType(unsigned int type);
	void update();
	void render(sf::RenderTarget& target);
};

