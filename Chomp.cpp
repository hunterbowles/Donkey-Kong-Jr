#include "stdafx.h"
#include "Chomp.h"
#include <iostream>


Chomp::Chomp()
{
	//EMPTY CONSTRUCTER WHHAT DO 
}


Chomp::Chomp(int x, int y) : GameObject(x, y)
{
	texture.loadFromFile("Sprites/spritesheet.png");

	onVine = false;

	setVX(1);
	setTeam(2);

	open.setTexture(texture);
	open.setScale(sf::Vector2f(2, 2));
	open.setColor(sf::Color::White);

	closed.setTexture(texture);
	closed.setScale(sf::Vector2f(2, 2));
	closed.setColor(sf::Color::White);

	open.setTextureRect(sf::IntRect(1, 229, 17, 12));
	closed.setTextureRect(sf::IntRect(19, 229, 18, 12));

	open.setPosition(x, y);
	closed.setPosition(x, y);

	setSprite(open);
	spriteType = 0;
	counter = 0;
}


void Chomp::step()
{
	setX(getX() + getVX());
	setY(getY() + getVY());
	open.setPosition(getX(), getY());
	closed.setPosition(getX(), getY());

	//Update the bounding box.
	setBB(getSprite().getGlobalBounds());
	vineBox = sf::FloatRect(getX() + 12, getY() + 24 + 24, 3, 3);

	if (getType() != 2)
	{
		useGravity();
		setVX(1);
	}
	else
	{
		setVY(1);
		setVX(0);
	}

	counter++;
	if (counter % 25 == 0)
	{
		if (counter % 50 == 0)
			spriteType = 1;
		else
			spriteType = 0;
	}

	if (getY() > 800)
	{
		setY(0);
		onVine = false;
		setX(200);
	}

	//Bad and inefficient pls fix
	if (getVX() > 0)
	{
		open.setTextureRect(sf::IntRect(18, 229, -17, 12));
		closed.setTextureRect(sf::IntRect(37, 229, -18, 12));
	}
	else if (getVX() < 0)
	{
		open.setTextureRect(sf::IntRect(1, 229, 17, 12));
		closed.setTextureRect(sf::IntRect(19, 229, 18, 12));
	}

	if (spriteType)
		setSprite(closed);
	else
		setSprite(open);
}


bool Chomp::vineIntersect(Vine v)
{
	if (vineBox.intersects(v.getBB()) &&  !onVine)
	{
		onVine = true;
		setY(getY() + 25);
		setType(2);
		open.setRotation(90);
		closed.setRotation(90);
		setX(getX() + 25);
		return true;
	}
	else if (getBB().intersects(v.getBB()) && onVine)
	{
		setType(2);		
		return true;
	}

	return false;
}

void Chomp::changeRotation(double angle)
{
	open.setRotation(angle);
	closed.setRotation(angle);
	if (onVine)
	{
		setX(getX() - 25);
		onVine = false;
	}
}

Chomp::~Chomp()
{
}
