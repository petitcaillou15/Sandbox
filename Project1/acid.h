#pragma once
#include "Element.h"
#include <vector>

// NAZIR YASSINE
using namespace std;

class Acid : public Element
{
public:
	Acid(int id = 4, int x = 0, int y = 0, int xmat = 0, int ymat = 0);
	void update(vector<vector<Element*>>* mat);
};

