#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <iostream>
#include "Element.h"
#include "Sand.h"
#include "Mushroom.h"
#include "Rock.h"
#include "Acid.h"

// LA MAXIME

using namespace std;
using namespace sf;

#define GRAY Color(112, 128, 144)
#define RED Color(220, 20, 60)
#define YELLOW Color(194, 178, 128)
#define GREEN Color(173, 255, 47)

void Game::run() const
{
    cout << "taille de la fenetre :" << endl;
    cout << "\n 1 - petite \n 2 - moyenne \n 3 - grande \n";
    int choix;
    cin >> choix;
    while (choix != 1 && choix != 2 && choix != 3) {
        cout << "taille de la fenetre :" << endl;
        cout << "\n 1 - petite \n 2 - moyenne \n 3 - grande \n";
        cin >> choix;
    }
    int x;
    int y;
    if (choix == 1) {
        x = 900;
        y = 500;
    }
    if (choix == 2) {
        x = 1200;
        y = 800;
    }
    if (choix == 3) {
        x = 1400;
        y = 1000;
    }

    // Création de la fenêtre
    RenderWindow window(VideoMode(x, y), "Sandbox");
    window.setFramerateLimit(75); 

    vector<vector<Element*>> Grains;
    // initialisation de la matrice
    Grains.resize(floor(window.getSize().x / 10));
    for (int i = 0; i < Grains.size(); i++) {
        Grains[i].resize(floor(window.getSize().y / 10));
        for (int j = 0; j < Grains[i].size(); j++) {
            Grains[i][j] = new Element(0, i * 10, j * 10, i, j);
        }
    }

    // Charge une police et créer une variable txt de type text
    Font font;
    if (!font.loadFromFile("Res/Poppins-Regular.ttf")) {
        cerr << "Erreur : impossible de charger la police" << endl;
        return;
    }

    // crétation des textes
    Text txt;
    txt.setString("Erase");
    txt.setFont(font);
    txt.setCharacterSize(15);
    txt.setFillColor(Color::White);
    txt.setStyle(Text::Bold);

    Text txtP;
    txtP.setString("Taille du pinceau : 1");
    txtP.setFont(font);
    txtP.setCharacterSize(15);
    txtP.setFillColor(Color::White);
    txtP.setStyle(Text::Bold);
    txtP.setPosition(0, 20);

    Text txtC;
    txtC.setString("Clear : C");
    txtC.setFont(font);
    txtC.setCharacterSize(15);
    txtC.setFillColor(Color::White);
    txtC.setStyle(Text::Bold);
    txtC.setPosition(0, 40);

    // Création des textures et des images
    sf::Texture sandTexture;
    if (!sandTexture.create(10, 10)) {
        cerr << "Erreur : impossible de créer la texture de sable" << endl;
        return;
    }

    sf::Image sandImage;
    sandImage.create(10, 10, YELLOW);
    sandTexture.update(sandImage);

    sf::Texture rockTexture;
    if (!rockTexture.create(10, 10)) {
        cerr << "Erreur : impossible de créer la texture de roche" << endl;
        return;
    }

    sf::Image rockImage;
    rockImage.create(10, 10, GRAY);
    rockTexture.update(rockImage);

    sf::Texture mushroomTexture;
    if (!mushroomTexture.create(10, 10)) {
        cerr << "Erreur : impossible de créer la texture de champignon" << endl;
        return;
    }

    sf::Image mushroomImage;
    mushroomImage.create(10, 10, RED);
    mushroomTexture.update(mushroomImage);

    sf::Texture acidTexture;
    if (!acidTexture.create(10, 10)) {
        cerr << "Erreur : impossible de créer la texture de champignon" << endl;
        return;
    }

    sf::Image acidImage;
    acidImage.create(10, 10, GREEN);
   acidTexture.update(acidImage);

    int id = 0; // Permet de savoir quel matériau on utilise
    int brosse = 0; // Permet de connaitre la taille du pinceau

    // boucle qui permet de laisser tourner la page tant qu'on ne la ferme pas
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // Ferme la fenêtre si on appuie sur la croix
            if (event.type == Event::Closed) {
                window.close();
            }

            // Donne les coordonnées de la position de la souris quand on appuie sur le clic gauche.
            int mouseMatX = floor(Mouse::getPosition(window).x / 10); //position de la souris dans la matrice
            int mouseMatY = floor(Mouse::getPosition(window).y / 10);
            if (Mouse::isButtonPressed(Mouse::Left)) {
                for (int i = mouseMatX - brosse; i < mouseMatX + brosse + 1; i++) { // balayage pour la largeur du pinceau
                    for (int j = mouseMatY - brosse; j < mouseMatY + brosse + 1; j++) {
                        if (i >= 0 && i < Grains.size() && j >= 0 && j < Grains[i].size()) {
                            delete Grains[i][j];
                            if (id == 1) {
                                Grains[i][j] = new Rock(1, i * 10, j * 10, i, j);
                            }
                            else if (id == 2) {
                                Grains[i][j] = new Sand(2, i * 10, j * 10, i, j);
                            }
                            else if (id == 3) {
                                Grains[i][j] = new Mushroom(3, i * 10, j * 10, i, j);
                            }
                            else if (id == 4) {
                                Grains[i][j] = new Acid(4, i * 10, j * 10, i, j);
                            }
                            else {
                                Grains[i][j] = new Element(0, i * 10, j * 10, i, j);
                            }
                        }
                    }
                }
                
            }

            // Gestion des inputs
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Num0) {
                    txt.setString("Erase");
                    txt.setFillColor(Color::White);
                    id = 0;
                }
                if (event.key.code == Keyboard::Num1) {
                    txt.setString("Rock");
                    txt.setFillColor(GRAY);
                    id = 1;
                }
                if (event.key.code == Keyboard::Num2) {
                    txt.setString("Sand");
                    txt.setFillColor(YELLOW);
                    id = 2;
                }
                if (event.key.code == Keyboard::Num3) {
                    txt.setString("Mushroom");
                    txt.setFillColor(RED);
                    id = 3;
                }
                if (event.key.code == Keyboard::Num4) {
                    txt.setString("Acid");
                    txt.setFillColor(GREEN);
                    id = 4;
                }
                if (event.key.code == Keyboard::Up && brosse < 9) {
                    brosse++; 
                    txtP.setString("Taille du pinceau : " + to_string(brosse));
                }
                if (event.key.code == Keyboard::Down && brosse > 0) {
                    brosse--;
                    txtP.setString("Taille du pinceau : " + to_string(brosse + 1));
                }
                if (event.key.code == Keyboard::C) {
                    for (int i = 0; i < Grains.size(); i++) {
                        for (int j = 0; j < Grains[i].size(); j++) {
                            Grains[i][j] = new Element(0, i * 10, j * 10, i, j);
                        }
                    }
                }
            }
        }

        // Met le fond de la fenêtre en noir
        window.clear(Color::Black);
        // Parcour de la liste et dessin des différents éléments
        for (vector<Element*> pos : Grains) {
            for (int i = 0; i < pos.size(); i++) {
                if (pos[i]->getId() == 1) { 
                    sf::Sprite grain(rockTexture);
                    grain.setPosition(pos[i]->getx(), pos[i]->gety());
                    pos[i]->update(&Grains);
                    window.draw(grain);
                }
                else if (pos[i]->getId() == 2) {
                    sf::Sprite grain(sandTexture);
                    grain.setPosition(pos[i]->getx(), pos[i]->gety());
                    pos[i]->update(&Grains);
                    window.draw(grain);
                }
                else if (pos[i]->getId() == 3) {
                    sf::Sprite grain(mushroomTexture);
                    grain.setPosition(pos[i]->getx(), pos[i]->gety());
                    pos[i]->update(&Grains);
                    window.draw(grain);
                }
                else if (pos[i]->getId() == 4) {
                    sf::Sprite grain(acidTexture);
                    grain.setPosition(pos[i]->getx(), pos[i]->gety());
                    pos[i]->update(&Grains);
                    window.draw(grain);
                }
                else {

                }
            }
        }
        window.draw(txtC);
        window.draw(txtP);
        window.draw(txt);
        window.display();
    }
}