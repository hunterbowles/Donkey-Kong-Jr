#pragma once
#include "GameObject.h"
#include "Vine.h"

class Chomp : public GameObject
{
public:
	Chomp();
	Chomp(int, int);
	bool vineIntersect(Vine *);
	bool getOnVineAgain();
	//void goDown();
	//void fallOff();
	void step();
	void changeRotation(double);
	~Chomp();

	sf::FloatRect getVineBox();

protected:
	sf::Sprite open, closed;
	sf::Texture texture;
	sf::FloatRect boundingBox, vineBox;
	int spriteType;
	int counter;
	bool onVine;
};