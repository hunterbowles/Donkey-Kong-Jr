#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"

class Platform : public GameObject
{
public:
	Platform(int l, double x, double y, int type);
	~Platform();
	bool collision(GameObject * other);
	void drawPlat(sf::RenderWindow& window);
	void setSprite(sf::Sprite sprite);
	void step();
private:
	std::vector<sf::Sprite> sprites;
	sf::Texture texture;
	int length;
};