#include "acid.h"
#include "Element.h"

// NAZIR YASSINE
Acid::Acid(int id, int x, int y, int xmat, int ymat) : Element(4, x, y, xmat, ymat)
{
}

void Acid::update(std::vector<std::vector<Element*>>* mat) {
    int x = getxMat();
    int y = getyMat();

    // repère les bords pour les conditins de bordures
    int width = mat->size();
    int height = (*mat)[0].size();

    if (y + 1 < height && (*mat)[x][y + 1]->getId() == 0) { // d'abord on teste si l'élément en dessous n'est pas du sable, pour la gravité
        moveTo(x, y + 1, mat);
    }
    else if (y + 1 < height && (*mat)[x][y + 1]->getId() == 4 || y+1 == height) { // si l'acide rencontre un acide il s'annule, ou si il atteint le bord en bas
        delete (*mat)[x][y];
        (*mat)[x][y] = new Element(0, x * 10, y * 10, x, y);
    }
    else if (y + 1 < height && (*mat)[x][y + 1]->getId() != 3 && (*mat)[x][y + 1] != 0){ // ici on teste afin de pouvoir "manger" les éléments qui sont soit sand soit rock
        delete (*mat)[x][y];
        (*mat)[x][y] = new Element(0, x * 10, y * 10, x, y); // on supprime donc notre acide
        delete (*mat)[x][y + 1];
        (*mat)[x][y + 1] = new Element(0, x * 10, (y + 1) * 10, x, y + 1); // et la case touchée
    }
    else if (x > 0 && y + 1 < height && (*mat)[x - 1][y + 1]->getId() == 0 && (*mat)[x - 1][y]->getId() == 0 && (*mat)[x][y + 1]->getId() == 3) { // ici il nous faut trois conditions, une en bas, une en bas à gauche et l'autre à gauche. Ainsi l'acide pourra se propager sur les pentes de Mushroom
        moveTo(x - 1, y + 1, mat);
    }
    else if (x + 1 < width && y + 1 < height && (*mat)[x + 1][y + 1]->getId() == 0 && (*mat)[x + 1][y]->getId() == 0 && (*mat)[x][y + 1]->getId() == 3) { // de même ici
        moveTo(x + 1, y + 1, mat);
    }
    else if (y + 1 < height && (*mat)[x][y + 1]->getId() == 3) { // ici on fait en sorte que l'acide puisse éliminer toute particule rock ou sand situé dans ses cases voisines
        bool isUsed = false; //ce booléen nous permettra de savoir si il faut ensuite supprimer notre case
        for (int i = x - 1; i <= x + 1;i++) {
            for (int j = y - 1; j <= y + 1; j++) { // on parcoure les boucles voisines
                if (i == x && j == y) continue;
                if (i > 0 && i < width && j>0 && j < height) { // test des bords
                    if ((*mat)[i][j]->getId() == 2 || (*mat)[i][j]->getId() == 1) { //savoir si la case voisine est un rock ou un sand
                        delete (*mat)[i][j];
                        (*mat)[i][j] = new Element(0, i * 10, j * 10, i, j); 
                        isUsed = true; // donc le booléen devient vrai
                    }
                }
            }
        }
        if (isUsed) { // et alors la case sera supprimée
            delete (*mat)[x][y];
            (*mat)[x][y] = new Element(0, x * 10, y * 10, x, y);
        }
    }

}

