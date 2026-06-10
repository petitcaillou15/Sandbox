#include "mushroom.h"
#include "Element.h"

// NAZIR YASSINE

Mushroom::Mushroom(int id, int x, int y, int xmat, int ymat) : Element(3,x,y,xmat,ymat)
{
}


void Mushroom::update(vector<vector<Element*>>* mat) {
	int x = getxMat();
	int y = getyMat();
	int width = mat->size();
	int height = (*mat)[0].size();
	bool EmptyNeighbors = true;

	if (y + 1 > height) { // d'abord on teste si la case en bas ne dépasse pas notre matrice
		EmptyNeighbors = false;
	}
	else {
		for (int i = x - 1; i <= x + 1;i++) { // sinon on regarde tous les voisins, pour savoir si il y a une pierre. Cette partie là permet une propagation en surface sur la pierre, gérant le cas des diagonales
			for (int j = y - 1; j <= y + 1;j++) {
				if (i > 0 && i < width && j>0 && j < height) {
					if (i == x && j == y) continue;
					if ((*mat)[i][j]->getId() == 1) {
						EmptyNeighbors = false;
					}
				}
			}
		}
	}

	if (y + 1 < height && (*mat)[x][y + 1]->getId() == 2 || y+1 == height) { // si jamais du sable se présente au champignon, alors il disparaît ou si il atteint le bord bas
		delete (*mat)[x][y];
		(*mat)[x][y] = new Element(0, x * 10, y * 10, x, y);
	} else if (EmptyNeighbors) { // ensuite, on peut faire notre test de gravité
		moveTo(x, y + 1, mat); 
	} else {
		for (int i = x - 1; i <= x + 1;i++) {
			for (int j = y - 1; j <= y + 1;j++) { // on regarde tous les voisins du mushroom
				if (i > 0 && i < width && j>0 && j < height) {
					if ((*mat)[i][j]->getId() == 0) { // si un voisin est vide, on regarde ses voisins à lui
						for (int k = i - 1;k <= i + 1;k++) {
							for (int l = j - 1;l <= j + 1;l++) {
								if (k > 0 && k < width && l>0 && l < height) {
									if ((*mat)[k][l]->getId() == 1) { // si voisin a un voisin pierre, il devient automatiquement un mushroom	
										delete (*mat)[i][j];
										(*mat)[i][j] = new Mushroom(3, i * 10, j * 10, i, j);
										return;
									}

								}
							}
						}
					}
				}
			}
		}
	}
}