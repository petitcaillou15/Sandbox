#include "rock.h"
#include "Element.h"
#include "mushroom.h"

// NAZIR YASSINE

Rock::Rock(int id, int x, int y, int xmat, int ymat) : Element(1, x, y, xmat, ymat)
{
}


void Rock::update(vector<vector<Element*>>* mat) { // rock ne change pas, alors update est vide
}