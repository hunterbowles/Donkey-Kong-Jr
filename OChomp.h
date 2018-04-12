#pragma once
#include "Chomp.h"

class OChomp : public Chomp
{
public:
	OChomp();
	OChomp(int, int);
	bool atBottom();
	void backUp();
	void step();
	~OChomp();
};

