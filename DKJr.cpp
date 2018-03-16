// DKJr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Vine.h"
#include "Chomp.h"
#include <iostream>
#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "DK Jr");
	window.setFramerateLimit(60);
	Player* p = new Player(20, 20);

	std::vector<Platform*> plats;
	std::vector<Vine*> vines;
	std::vector<Chomp*> chomps;

	plats.push_back(new Platform(8, 0, 770));
	plats.push_back(new Platform(8, 0, 180));

	vines.push_back(new Vine(19, 53, 200));
	vines.push_back(new Vine(19, 106, 200));

	chomps.push_back(new Chomp(0, 100));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Reset
		p->input();
		p->setOnPlat(false);

		for (int i = 0; i < chomps.size(); i++)
		{
			chomps.at(i)->setOnVine(false);
			chomps.at(i)->setOnVine(false);
		}

		//Check collisions with the platforms
		//and draw platforms.
		for (int i = 0; i < plats.size(); i++)
		{
			plats.at(i)->collision(p);

			for (int j = 0; j < chomps.size(); j++)
			{
				plats.at(i)->collision(chomps.at(j));
			}
			plats.at(i)->drawPlat(window);
		}

		//Check collisions with the vines
		if (vines.at(0)->allVines(vines, p) == 0)
		{
			p->setOnVine(false);
			p->setDualCollide(false);
		}
		else if (vines.at(0)->allVines(vines, p) == 1)
		{
			p->setOnVine(true);
			p->setDualCollide(false);
		}
		else if (vines.at(0)->allVines(vines, p) == 2)
		{
			p->setDualCollide(true);
			p->setOnVine(true);
		}
		//Draw vines.
		for (int i = 0; i < vines.size(); i++)
		{
			vines.at(i)->drawVine(window);
		}

		//Check collision with the chomps
		for (int i = 0; i < chomps.size(); i++)
		{
			vines.at(0)->allVines(vines, chomps.at(i));
			chomps.at(i)->step();
			window.draw(chomps.at(i)->getSprite());
		}

		p->step();
		window.draw(p->getSprite());
		window.display();
		window.clear();
	}

	delete[] &plats;
	delete[] & vines;
	delete p;

	return 0;
}