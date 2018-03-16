#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(double xVal, double yVal)
{
	x = xVal;
	y = yVal;
	vX = 0;
	vY = 0;
	gravity = 2;
	type = 0;
	team = 0;
	onVine = false;
	/*
	0 = Nothing
	1 = Platform
	2 = vine
	*/
}

GameObject::GameObject()
{
	x = 0;
	y = 0;
	vX = 0;
	vY = 0;
	gravity = 2;
	type = 0;
	team = 0;
	onVine = false;
}


GameObject::~GameObject()
{
}


void GameObject::step()
{
	//Change x and y positions according to the velocity.
	setX(getX() + getVX());
	setY(getY() + getVY());
	setVX(0);
	setSpritePos();

	//Update the bounding box.
	setBB(sprite.getGlobalBounds());

	//Give the object gravity.
	useGravity();

}


bool GameObject::collision(GameObject * other)
{
	if (other->team == team) //ignores same team collision
		return false;
	// if collision with an enemy
	else if (boundingBox.intersects(other->boundingBox))
	{
		return true;

	}


}


void GameObject::die()
{

}


void GameObject::useGravity()
{
	if(!onVine)
		setVY(getVY() + gravity);
	if (onVine)
		setVY(0);
}


//Getters
double GameObject::getX()
{
	return x;
}
double GameObject::getY()
{
	return y;
}
double GameObject::getVX()
{
	return vX;
}
double GameObject::getVY()
{
	return vY;
}
double GameObject::getGravity()
{
	return gravity;
}
sf::Sprite GameObject::getSprite()
{
	return sprite;
}
int GameObject::getType()
{
	return type;
}
sf::FloatRect GameObject::getBB()
{
	return boundingBox;
}
bool GameObject::getOnVine()
{
	return onVine;
}
bool GameObject::getOnPlat()
{
	return onPlat;
}
bool GameObject::getTouchingEnemy()
{
	return touchingEnemy;
}
int GameObject::getTeam()
{
	return team;
}

//Setters
void GameObject::setX(double i)
{
	x = i;
}
void GameObject::setY(double i)
{
	y = i;
}
void GameObject::setVX(double  i)
{
	vX = i;
}
void GameObject::setVY(double i)
{
	vY = i;
}
void GameObject::setSpritePos()
{
	sprite.setPosition(x, y);
}
void GameObject::setBB(sf::FloatRect BB)
{
	boundingBox = BB;
}
void GameObject::setSprite(sf::Sprite s)
{
	sprite = s;
}
void GameObject::setType(int i)
{
	type = i;
}
void GameObject::setOnVine(bool i)
{
	onVine = i;
}
void GameObject::setOnPlat(bool i)
{
	onPlat = i;
}
void GameObject::setTouchingEnemy(bool i)
{
	touchingEnemy = i;
}
void GameObject::setTeam(int i)
{
	team = i;
}