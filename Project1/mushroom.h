#pragma once
#include "Element.h"
#include <vector>

// NAZIR YASSINE


class Mushroom : public Element
{
public: 
	Mushroom(int id = 3, int x = 0, int y = 0, int xmat = 0, int ymat = 0);
	void update(vector<vector<Element*>>* mat);
};


