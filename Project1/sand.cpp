#include "sand.h"
#include "Element.h"

// LA MAXIME

Sand::Sand(int id, int x, int y, int xmat, int ymat) : Element(2, x, y, xmat, ymat)
{
}

void Sand::update(std::vector<std::vector<Element*>>* mat) {
    int x = getxMat();
    int y = getyMat();

    // repère les bords pour les conditiOns de bordures
    int width = mat->size();
    int height = (*mat)[0].size();

    if (y + 1 < height && (*mat)[x][y + 1]->getId() == 0) {
        moveTo(x, y + 1, mat); // en bas
    }
    else if (x > 0 && y + 1 < height && (*mat)[x - 1][y + 1]->getId() == 0 && (*mat)[x - 1][y]->getId() == 0) { // on regarde si la case à gauche et en bas à gauche sont vides
        moveTo(x - 1, y + 1,mat); // bas gauche
    }
    else if (x + 1 < width && y + 1 < height && (*mat)[x + 1][y + 1]->getId() == 0 && (*mat)[x + 1][y]->getId() == 0) { // Pareil à droite
        moveTo(x + 1, y + 1,mat); // bas droite
    }
}

