#include "stdafx.h"
#include "Platform.h"
#include "Chomp.h"
#include <iostream>

Platform::Platform(int l, double x, double y, int type) : GameObject(x, y)
{
	//TODO: MAKE THIS ABLE TO TAKE DIFFERENT TYPES OF PLATFORMS
	length = l;
	texture.loadFromFile("Sprites/spritesheet.png");
	for (int i = 0; i < l; i++)
	{
		sprites.push_back(sf::Sprite());
		sprites.at(i).setTexture(texture);
		if (type == 1)
		{
			if (i == 0)
				sprites.at(i).setTextureRect(sf::IntRect(532, 370, 8, 8));
			else if (i == l - 1)
				sprites.at(i).setTextureRect(sf::IntRect(550, 370, 8, 8));
			else
				sprites.at(i).setTextureRect(sf::IntRect(541, 370, 8, 8));
		}
		else if (type == 2)
		{
			if (i == 0)
				sprites.at(i).setTextureRect(sf::IntRect(172, 128, 8, 8));
			else if (i == l - 1)
				sprites.at(i).setTextureRect(sf::IntRect(190, 128, 8, 8));
			else
				sprites.at(i).setTextureRect(sf::IntRect(181, 128, 8, 8));
		}
		sprites.at(i).setScale(sf::Vector2f(3, 3));
		sprites.at(i).setColor(sf::Color::White);
		sprites.at(i).setPosition(getX() + 8 * 3 * i, getY());
	}

	setBB(sf::FloatRect(sf::Vector2f(getX(), getY()),
		sf::Vector2f(8 * length * 3, 8 * 3)));
}


Platform::~Platform()
{
}


bool Platform::collision(GameObject * other)
{
	setBB(sf::FloatRect(sf::Vector2f(getX(), getY()),
		sf::Vector2f(8 * length * 3, 8 * 3)));

	//Check top.
	if (other->getY() <= (getY() - other->getBB().height)
		&& (other->getY() + other->getVY()) >= (getY() - other->getBB().height)
		&& (other->getX() + other->getBB().width) > getX()
		&& other->getX() < (getX() + getBB().width))
	{
		if (Chomp* c = dynamic_cast<Chomp*>(other))
			dynamic_cast<Chomp*>(other)->changeRotation(0);
		other->setVY(0);
		other->setY(getY() - other->getBB().height);
		if(!other->getOnVine())
		 return true;
	}
	//Check bottom.
	else if (other->getY() >= (getY() + 24)
		&& (other->getY() + other->getVY()) <= (getY() + 24)
		&& (other->getX() + other->getBB().width) > getX()
		&& other->getX() < (getX() + getBB().width))
	{
		other->setVY(0);
		other->setY(getY() + 28);
	}
	else if ((other->getX() + other->getBB().width <= getX()
		&& (other->getX() + other->getVX() + other->getBB().width) >= getX())
		|| other->getBB().intersects(this->getBB())
		&& ((other->getY() + other->getBB().height) > getY())
		&& (other->getY() < getY() + 24))
	{
		other->setX(getX() - other->getBB().width);
	}
	else if ((other->getX() >= getX() + getBB().width
		&& (other->getX() + other->getVX()) <= getX() + getBB().width)
		&& ((other->getY() + other->getBB().height) > getY())
		&& (other->getY() < getY() + 24))
	{
		other->setX(getX() + getBB().width + 5);
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