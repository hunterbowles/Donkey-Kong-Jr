#include "stdafx.h"
#include "Platform.h"
#include <iostream>

Platform::Platform(int l, double x, double y) : GameObject(x, y)
{
	//TODO: MAKE THIS ABLE TO TAKE DIFFERENT TYPES OF PLATFORMS
	length = l;
	texture.loadFromFile("Sprites/spritesheet.png");
	for (int i = 0; i < l; i++)
	{
		sprites.push_back(sf::Sprite());
		sprites.at(i).setTexture(texture);
		if (i == 0)
			sprites.at(i).setTextureRect(sf::IntRect(532, 370, 8, 8));
		else if (i == l - 1)
			sprites.at(i).setTextureRect(sf::IntRect(550, 370, 8, 8));
		else
			sprites.at(i).setTextureRect(sf::IntRect(541, 370, 8, 8));
		sprites.at(i).setScale(sf::Vector2f(3, 3));
		sprites.at(i).setColor(sf::Color::White);
		sprites.at(i).setPosition(getX() + 8 * 3 * i, getY());
	}


}


Platform::~Platform()
{
}


bool Platform::collision(GameObject * other)
{
	setBB(sf::FloatRect(sf::Vector2f(getX(), getY()),
		sf::Vector2f(8 * length * 3, 8 * 3)));

	//Check top and sides.
	if (other->getY() <= (getY() - other->getBB().height)
		&& (other->getY() + other->getVY()) >= (getY() - other->getBB().height)
		&& (other->getX() + other->getBB().width) >= getX()
		&& other->getX() <= (getX() + getBB().width))
	{
		other->setVY(0);
		other->setType(1);
		other->setY(getY() - other->getBB().height);
		return true;
	}
	//Check bottom and sides.
	else if (other->getY() >= (getY() + getBB().height)
		&& (other->getY() + other->getVY()) <= (getY() + getBB().height)
		&& (other->getX() + other->getBB().width) >= getX()
		&& other->getX() <= (getX() + getBB().width))
	{
		other->setVY(0);
		other->setType(0);
		other->setY(getY() + getBB().height);
		return true;
	}

	return false;
}


void Platform::drawPlat(sf::RenderWindow & window)
{
	for (int i = 0; i < length; i++)
	{
		window.draw(sprites.at(i));
	}
}

void Platform::setSprite(sf::Sprite sprite)
{
	setBB(sf::FloatRect(sf::Vector2f(getX(), getY()),
		sf::Vector2f(8 * length * 3, 8 * 3)));
}


void Platform::step()
{
	setBB(sf::FloatRect(sf::Vector2f(getX(), getY()),
		sf::Vector2f(8 * length * 3, 8 * 3)));
}