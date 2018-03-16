#include "stdafx.h"
#include "Vine.h"
#include "Chomp.h"
#include <iostream>
#include <vector>

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

int Vine::allVines(std::vector<Vine*> vines, GameObject * other)
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


bool Vine::collision(GameObject * other)
{
	bool x = false;
	setBB(sf::FloatRect(sf::Vector2f(getX() + 9, getY()),
		sf::Vector2f(2 * 3, 8 * length * 3)));

	//Check top and sides.
	if (getBB().intersects(other->getBB()))
	{
		if (!other->getOnVine() && other->getTeam() == 1)
		{
			other->setX(getX() - 20);
		}
		x = true;
		other->setOnVine(true);
	}
	else if(Chomp* c = dynamic_cast<Chomp*>(other))
	{
		if (dynamic_cast<Chomp*>(other)->getVineBox().intersects(getBB()))
		{
			dynamic_cast<Chomp*>(other)->vineIntersect(this);
			x = true;
		}
	}
	
	if(!x)
	{
		//other->setOnVine(false);
		x = false;
	}
	return x;
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