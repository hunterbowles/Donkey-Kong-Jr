#include "stdafx.h"
#include "Vine.h"
#include <iostream>

Vine::Vine(int l, double x, double y) : GameObject(x, y)
{
	//TODO: MAKE THIS ABLE TO TAKE DIFFERENT TYPES OF PLATFORMS
	length = l;
	texture.loadFromFile("Sprites/spritesheet.png");
	for (int i = 0; i < l; i++)
	{
		sprites.push_back(sf::Sprite());
		sprites.at(i).setTexture(texture);
		if (i == l - 1)
			sprites.at(i).setTextureRect(sf::IntRect(161, 123, 8, 8));
		else
			sprites.at(i).setTextureRect(sf::IntRect(161, 114, 8, 8));
		sprites.at(i).setScale(sf::Vector2f(3, 3));
		sprites.at(i).setColor(sf::Color::White);
		sprites.at(i).setPosition(getX(), getY() + 8 * 3 * i);
	}


}


Vine::~Vine()
{
}


bool Vine::collision(GameObject * other)
{
	
	setBB(sf::FloatRect(sf::Vector2f(getX() + 9, getY()),
		sf::Vector2f(2 * 3, 8 * length * 3)));

	//Check top and sides.
	if (getBB().intersects(other->getBB()))
	{
		if (other->getType() != 2)
		{
			other->setType(2);
			other->setX(getX() - 20);
		}
		return true;
	}

	return false;
}


void Vine::drawVine(sf::RenderWindow & window)
{
	for (int i = 0; i < length; i++)
	{
		window.draw(sprites.at(i));
	}
}

void Vine::setSprite(sf::Sprite sprite)
{
	setBB(sf::FloatRect(sf::Vector2f(getX(), getY()),
		sf::Vector2f(8 * 3, 8 * length * 3)));
}