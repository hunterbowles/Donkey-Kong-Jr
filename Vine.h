#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"

class Vine : public GameObject
{
public:
	Vine(int l, double x, double y);
	~Vine();
	bool collision(GameObject * other);
	void drawVine(sf::RenderWindow& window);
	void setSprite(sf::Sprite sprite);
private:
	std::vector<sf::Sprite> sprites;
	sf::Texture texture;
	int length;
	sf::FloatRect boundingBox;
};