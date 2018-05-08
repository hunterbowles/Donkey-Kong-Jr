#include "stdafx.h"
#include "Chomp.h"
#include <iostream>
#include <cstdlib>


Chomp::Chomp()
{
	//EMPTY CONSTRUCTER WHHAT DO 
}

Chomp::~Chomp()
{
}

Chomp::Chomp(int x, int y) : GameObject(x, y)
{
	texture.loadFromFile("Sprites/spritesheet.png");

	onVine = false;

	int chance = rand() % 2;
	if (chance == 1)
		setVX(1);
	else
		setVX(-1);
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
	setTouchingEnemy(false);
	counter = 0;
}


//Method to overide GameObject step.
void Chomp::step()
{
	setX(getX() + getVX());
	setY(getY() + getVY());
	open.setPosition(getX(), getY());
	closed.setPosition(getX(), getY());

	//Update the bounding box.
	setBB(getSprite().getGlobalBounds());
	vineBox = sf::FloatRect(getX() + 12, getY() + 48, 1, 1);

	if (!getOnVine())
	{
		useGravity();
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
		setY(120);
		onVine = false;
		setX(80);

		int chance = rand() % 2;
		if (chance == 1)
			setVX(1);
		else
			setVX(-1);
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


//Method to dictate what happens when a chomp intersects
//with a vine.
bool Chomp::vineIntersect(Vine * v)
{
	if (vineBox.intersects(v->getBB()) && !onVine && rand() % 10 == 0)
	{
		onVine = true;
		setY(getY() + 50);
		open.setRotation(90);
		closed.setRotation(90);
		setX(getX() + 30);
		setVX(0);
		return true;
	}

	return false;
}


//Change rotation if a chomp is on a vine.
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


//Bounding box.
sf::FloatRect Chomp::getVineBox()
{
	return vineBox;
}


//Don't allow a chomp on two vines.
bool Chomp::getOnVineAgain()
{
	return onVine;
}