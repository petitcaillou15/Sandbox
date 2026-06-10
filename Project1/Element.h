#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <vector>
using namespace std;

// NAZIR YASSINE

	class Element {
		int id_;
		int x_;
		int y_;
		int xMat_;
		int yMat_;
	public :
		Element(int id = 0, int x = 0, int y = 0, int xmat = 0, int ymat = 0);
		void setid(int id) {
			id_ = id;
		}
		int getId() {
			return id_;
		}
		int getx() {
			return x_;
		}
		void setx(int x) {
			x_ = x;
		}
		void sety(int y) {
			y_ = y;
		}
		void setxMat(int xMat) {
			xMat_ = xMat;
		}
		void setyMat(int yMat) {
			yMat_ = yMat;
		}
		int gety() {
			return y_;
		}
		int getxMat() {
			return xMat_;
		}
		int getyMat() {
			return yMat_;
		}
		void setPosition(int x, int y) 
		{	x_ = x;
			y_ = y;}
		void print() const;
		virtual void update(vector<vector<Element*>>* mat) {};
		void moveTo(int x, int y, vector<vector<Element*>>* mat); // LA MAXIME
	};