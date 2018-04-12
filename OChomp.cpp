#include "stdafx.h"
#include "OChomp.h"


OChomp::OChomp()
{
}


OChomp::OChomp(int x, int y) : Chomp(x, y)
{
	open.setTextureRect(sf::IntRect(38, 229, 17, 12));
	closed.setTextureRect(sf::IntRect(56, 229, 18, 12));
	
}


void OChomp::step()
{
	Chomp::step();

	if (getVX() > 0)
	{
		open.setTextureRect(sf::IntRect(55, 229, -17, 12));
		closed.setTextureRect(sf::IntRect(74, 229, -18, 12));
	}
	else if (getVX() < 0)
	{
		open.setTextureRect(sf::IntRect(38, 229, 17, 12));
		closed.setTextureRect(sf::IntRect(56, 229, 18, 12));
	}
	if (spriteType)
		setSprite(closed);
	else
		setSprite(open);
}


OChomp::~OChomp()
{
}
