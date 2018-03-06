#pragma once
#include <SFML\Graphics.hpp>
#include <typeinfo>

class GameObject
{
public:
	GameObject(double, double);
	GameObject();
	virtual ~GameObject();
	void step();
	bool collision(GameObject *);
	void die();
	void useGravity();

	//Getters and setters
	double getX();
	double getY();
	double getVX();
	double getVY();
	double getGravity();
	int getType();
	sf::Sprite getSprite();
	int getTeam();
	void setSprite(sf::Sprite s);
	void setX(double i);
	void setY(double i);
	void setVX(double  i);
	void setVY(double i);
	void setSpritePos();
	void setType(int i);
	void setTeam(int);
	sf::FloatRect getBB();
	void setBB(sf::FloatRect);

private:
	double x, y, vX, vY, gravity;
	int team, type;
	sf::Sprite sprite;
	sf::FloatRect boundingBox;
};