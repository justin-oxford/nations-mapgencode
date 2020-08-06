#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(unsigned int type)
{
	//this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	//this->shape.setFillColor(sf::Color::Green);
	//this->shape.setPosition(x, y);
	this->type = type;
}

Tile::~Tile()
{

}

unsigned short int Tile::returnType()
{
	unsigned short int tp;
	if (this->type >= 1) {
		tp = 1;
	}
	else
	{
		tp = 0;
	}
	
	return tp;
}

void Tile::setType(unsigned int type)
{
	this->type = type;
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
