#include "stdafx.h"
#include "Platform.h"
#include "Chomp.h"
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
		if (Chomp* c = dynamic_cast<Chomp*>(other))
			dynamic_cast<Chomp*>(other)->changeRotation(0);
		other->setVY(0);
		other->setY(getY() - other->getBB().height);
		other->setOnPlat(true);
		return true;
	}
	//Check bottom and sides.
	else if (other->getY() >= (getY() + 24)
		&& (other->getY() + other->getVY()) <= (getY() + 24)
		&& (other->getX() + other->getBB().width) >= getX()
		&& other->getX() <= (getX() + getBB().width))
	{
		other->setVY(0);
		other->setY(getY() + 28);
		other->setOnPlat(true);
		return true;
	}
	other->setOnPlat(false);
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