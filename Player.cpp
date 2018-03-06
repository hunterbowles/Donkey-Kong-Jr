
#include "stdafx.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <typeinfo>
#include <iostream>


Player::Player(double x, double y) : GameObject(x, y)
{
	texture.loadFromFile("Sprites/spritesheet.png");

	//Get the sprites ready to capture image.
	for (int i = 0; i < 4; i++)
	{
		up[i].setTexture(texture);
		up[i].setScale(sf::Vector2f(2, 2));
		up[i].setColor(sf::Color::White);

		//There is not a fourth right or left sprite.
		//Make sure that you are not going out of bounds.
		if (i < 3)
		{
			right[i].setTexture(texture);
			right[i].setScale(sf::Vector2f(2, 2));
			right[i].setColor(sf::Color::White);

			left[i].setTexture(texture);
			left[i].setScale(sf::Vector2f(2, 2));
			left[i].setColor(sf::Color::White);
		}

		//There is not a third up or jump sprite.
		//Make sure that you are not going out of bounds.
		if (i < 2)
		{
			jump[i].setTexture(texture);
			jump[i].setScale(sf::Vector2f(2, 2));
			jump[i].setColor(sf::Color::White);

			grab[i].setTexture(texture);
			grab[i].setScale(sf::Vector2f(2, 2));
			grab[i].setColor(sf::Color::White);
		}
	}

	//Load sprites
	right[0].setTextureRect(sf::IntRect(0, 278, 27, 18));
	right[1].setTextureRect(sf::IntRect(28, 278, 20, 18));
	right[2].setTextureRect(sf::IntRect(49, 278, 26, 18));

	left[0].setTextureRect(sf::IntRect(27, 278, -27, 18));
	left[1].setTextureRect(sf::IntRect(48, 278, -20, 18));
	left[2].setTextureRect(sf::IntRect(75, 278, -26, 18));

	up[0].setTextureRect(sf::IntRect(29, 297, 21, 18));
	up[1].setTextureRect(sf::IntRect(51, 297, 19, 18));
	up[2].setTextureRect(sf::IntRect(50, 297, -21, 18));
	up[3].setTextureRect(sf::IntRect(70, 297, -19, 18));

	jump[0].setTextureRect(sf::IntRect(76, 279, 28, 17));
	jump[1].setTextureRect(sf::IntRect(0, 297, 28, 18));

	grab[0].setTextureRect(sf::IntRect(71, 297, 32, 18));
	grab[1].setTextureRect(sf::IntRect(103, 297, -32, 18));

	setSprite(right[0]);
	counter = 1;
	dualCollide = false;

	/*SpriteType rules:
		1: right[0]
		2: right[1]
		3: right[2]
		4: left[0]
		5: left[1]
		6: left[2]
		7: up[0]
		8: up[1]
		9: up[2]
		10: up[3]
		11: jump[0]
		12: jump[1]
		13: grab[0]
		14: grab[1]
		15: dualClimb[0]
		16: dualClimb[1]
	*/
	spriteType = 1;
}


Player::~Player()
{
}


//Move Donky Kong Jr and change sprites to give
// it the appierance that it is moving.
void Player::input()
{
	//Change sprites depending on which way the player is going.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (getType() != 2)
		{
			setVX(5);
			counter++;
			//Don't change the sprite every frame. DK Jr looks
			//like he is moving really fast if you do.
			if (counter % 4 == 0)
				spriteType = (counter % 3)  + 1;
		}
		else
		{
			if (spriteType != 14)
			{
				if (spriteType == 13)
				{
					spriteType = 7;
					setX(getX() + 20 + 6);
				}
				else if (spriteType == 7 || spriteType == 8)
				{
					spriteType = 9;
					setX(getX() + 20);
				}
				else if (spriteType == 9 || spriteType == 10)
				{
					spriteType = 14;
					setX(getX() + 20 - 14);
				}
			}
			else if (!dualCollide)
			{
				spriteType = 11;
			}
			//Make sure that the Left arrow is not pressed more than once.
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {}

		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//Don't change the sprite every frame. DK Jr looks
		//like he is moving really fast if you do.
		if (getType() != 2)
		{
			setVX(-5);
			counter++;
			if (counter % 4 == 0)
				spriteType = (counter % 3) + 4;
		}
		else
		{
			if (spriteType != 13)
			{
				if (spriteType == 14)
				{
					spriteType = 9;
					setX(getX() - 20 + 14);
				}
				else if (spriteType == 9 || spriteType == 10)
				{
					spriteType = 7;
					setX(getX() - 20);
				}
				else if (spriteType == 7 || spriteType == 8)
				{
					spriteType = 13;
					setX(getX() - 20 - 6);
				}
			}
			//Make sure that the Left arrow is not pressed more than once.
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (getType() == 2)
		{
			//Don't change the sprite every frame. DK Jr looks
			//like he is moving really fast if you do.
			setVY(-10);
			counter++;
			if (!dualCollide)
			{
				if (counter % 3 == 0)
					if (spriteType == 7 || spriteType == 8)
						spriteType = (counter % 2) + 7;
					else
						spriteType = (counter % 2) + 9;
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (getType() == 2)
		{
			//Don't change the sprite every frame. DK Jr looks
			//like he is moving really fast if you do.
			setVY(10);
			counter++;
			if (!dualCollide)
			{
				if (counter % 3 == 0)
					if (spriteType == 7 || spriteType == 8)
						spriteType = (counter % 2) + 7;
					else
						spriteType = (counter % 2) + 9;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//Keep the sprite the same until DK Jr is about to hit
		//the ground
		if (getType() == 1)
		{
			setVY(-20);
			spriteType = 11;
		}
		//Need to setup bounding box to tell when to switch
		//Sprite to second jump

		//NOT FINISHED
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		setX(sf::Mouse::getPosition().x);
		setY(sf::Mouse::getPosition().y);
		setSpritePos();
	}
	changeSprite();
}


void Player::changeSprite()
{
	switch(spriteType)
	{
	case 1: 
		setSprite(right[0]);
		break;
	case 2:
		setSprite(right[1]);
		break;
	case 3:
		setSprite(right[2]);
		break;
	case 4:
		setSprite(left[0]);
		break;
	case 5:
		setSprite(left[1]);
		break;
	case 6:
		setSprite(left[2]);
		break;
	case 7:
		setSprite(up[0]);
		break;
	case 8:
		setSprite(up[1]);
		break;
	case 9:
		setSprite(up[2]);
		break;
	case 10:
		setSprite(up[3]);
		break;
	case 11:
		setSprite(jump[0]);
		break;
	case 12:
		setSprite(jump[1]);
		break;
	case 13:
		setSprite(grab[0]);
		break;
	case 14:
		setSprite(grab[1]);
		break;
	default:
		std::cout << "What in the heck are you doing." << std::endl;
	}
}


void Player::step()
{
	if (getType() == 2 && (spriteType != 13 && spriteType != 8 && spriteType != 7 && spriteType != 10 && spriteType != 9 && spriteType != 14))
		spriteType = 7;
	else if (getType() == 2 && (spriteType != 13 && spriteType != 8 && spriteType != 7 && spriteType != 10 && spriteType != 9 && spriteType != 14) && (spriteType == 0 || spriteType == 1 || spriteType == 2))
		spriteType = 9;

	if (getType() == 1 && !(spriteType >= 1 && spriteType <= 6))
	{
		setY(getY() - 2);
		spriteType = 1;
	}
	
	if (getY() > 800)
		setY(0);

	GameObject::step();
}


void Player::doubleCollide(Vine v, Vine vv)
{
	setVY(getVY() * 1.5);
	dualCollide = true;
	
	if(counter % 3 == 0)
		spriteType = (counter % 2) + 13;
}


//Getters
int Player::getLives()
{
	return lives;
}
int Player::getScore()
{
	return score;
}
int Player::getSpriteType()
{
	return spriteType;
}
bool Player::getDualCollide()
{
	return dualCollide;
}

//Setters
void Player::setLives(int i)
{
	lives = i;
}
void Player::setScore(int i)
{
	score = i;
}
void Player::setSpriteType(int i)
{
	spriteType = i;
}
void Player::setDualCollide(bool set)
{
	dualCollide = set;
}