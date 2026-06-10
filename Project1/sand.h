#pragma once
#include "Element.h"
#include <vector>

// LA MAXIME

class Sand : public Element
{
public:
	Sand(int id = 2, int x = 0, int y = 0, int xmat = 0, int ymat = 0);
	void update(vector<vector<Element*>>* mat);
};
