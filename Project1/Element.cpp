#include "Element.h"
#include <iostream>
using namespace std;

// NAZIR YASSINE

Element::Element(int id, int x, int y, int xmat, int ymat) {
	id_ = id;
	x_ = x;
	y_ = y;
	yMat_ = ymat;
	xMat_ = xmat;
}

void Element::print() const {
	cout << "id : " << id_ << endl;
	cout << "position : " << x_ << ", " << y_ << endl;
	cout << "position matrice : " << xMat_ << ", " << yMat_ << endl;
}

// LA MAXIME
void Element::moveTo(int newX, int newY, vector<vector<Element*>>* mat) {
	int width = mat->size();
	int height = (*mat)[0].size();
	int x = getxMat();
	int y = getyMat();
	if (newX < 0 || newX >= width || newY < 0 || newY >= height)
		return;

	delete (*mat)[newX][newY]; // Libère l'emplacement de l'élément
	(*mat)[newX][newY] = this; // Déplace l'élément
	(*mat)[x][y] = new Element(0, x * 10, y * 10, x, y); // remplace l'ancienne case par du vide

	// Change les valeurs de l'élément
	setxMat(newX);
	setyMat(newY);
	setx(newX * 10);
	sety(newY * 10);
};
