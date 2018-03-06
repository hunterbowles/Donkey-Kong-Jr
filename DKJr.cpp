// DKJr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Vine.h"
#include "Chomp.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 800), "DK Jr");
	window.setFramerateLimit(60);
	Platform pp(10, 150, 175);
	Platform p(10, 150, 500);
	Vine v(10, 312, 200);
	Vine vv(10, 260, 200);
	Player p1(300, 50);
	Chomp c(200, 100);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		p1.input();
		p1.setDualCollide(false);
		if (!pp.collision(&p1))
		{
			if (!p.collision(&p1))
			{
				if (vv.collision(&p1) && v.collision(&p1))
					p1.doubleCollide(v, vv);
				else if (!v.collision(&p1))
					if(!vv.collision(&p1))
						p1.setType(0);
			}
		}

		if (!pp.collision(&c))
			if (!p.collision(&c))
				c.setType(0);
			else
				c.changeRotation(0);
		else
			c.changeRotation(0);

		c.vineIntersect(v);
		c.vineIntersect(vv);
		
		c.step();
		p1.step();
		window.clear();
		pp.drawPlat(window);
		p.drawPlat(window);
		v.drawVine(window);
		vv.drawVine(window);
		window.draw(p1.getSprite());
		window.draw(c.getSprite());
		window.display();
	}

	return 0;
}