#include "stdafx.h"
#include "Vine.h"
#include "Chomp.h"
#include <iostream>
#include <vector>


bool isChomp(GameObject *thing)
{
	Chomp *test = dynamic_cast<Chomp*>(thing);
	//std::cout << test << std::endl;
	if (test == NULL)
		return false;
	return true;
}


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

int Vine::allVines(std::vector<Vine*> vines, GameObject *other)
{
	int numVines = 0;

	for (int i = 0; i < vines.size(); i++)
	{
		if (vines.at(i)->collision(other))
		{
			numVines++;
		}
	}
	return numVines;
}


bool Vine::collision(GameObject *other)
{
	bool x = false;
	setBB(sf::FloatRect(sf::Vector2f(getX() + 10, getY()),
		sf::Vector2f(1.75 * 3, 8 * length * 3)));

	//Put some log output here to see what object you are talking about.
	//std::cout << other->getTeam() << std::endl;
	//Now put some log output in isChomp() or rather just catch the return and log that.

	//Check top and sides.
	if (!isChomp(other) && getBB().intersects(other->getBB()))
	{
		if (!other->getOnVine() && other->getTeam() == 1)
		{
			other->setX(getX() - 20);
		}
		x = true;
		other->setOnVine(true);
	}
	else if (Chomp* c = dynamic_cast<Chomp*>(other))
	{
		if (getBB().intersects(other->getBB()) 
			&& dynamic_cast<Chomp*>(other)->getOnVineAgain() == true)
		{
			other->setOnVine(true);
		}

		if (dynamic_cast<Chomp*>(other)->getVineBox().intersects(getBB()))
		{
			dynamic_cast<Chomp*>(other)->vineIntersect(this);
			x = true;
		}
	}
	return x;
}


void Vine::drawVine(sf::RenderWindow &window)
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