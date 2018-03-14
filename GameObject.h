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

	//Getters
	double getX();
	double getY();
	double getVX();
	double getVY();
	double getGravity();
	int getType();
	sf::Sprite getSprite();
	sf::FloatRect getBB();
	bool getOnVine();
	bool getOnPlat();
	bool getTouchingEnemy();
	int getTeam();

	//Setters
	void setSprite(sf::Sprite s);
	void setX(double i);
	void setY(double i);
	void setVX(double  i);
	void setVY(double i);
	void setSpritePos();
	void setType(int i);
	void setBB(sf::FloatRect);
	void setOnVine(bool i);
	void setOnPlat(bool i);
	void setTouchingEnemy(bool i);
	void setTeam(int i);

private:
	double x, y, vX, vY, gravity;
	int team, type;
	bool onVine, onPlat, touchingEnemy;
	sf::Sprite sprite;
	sf::FloatRect boundingBox;
};