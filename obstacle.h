#ifndef Obstacle_H
#define Obstacle_H

#include"plaszczak.h"

class Obstacle
{
	int x;
	int y;
public:
	Obstacle(int x = 0, int y = 0) : x(x), y(y) {}
	~Obstacle() { cout << "~Obstacle"; }

	int getx() const { return x; }
	int gety() const { return y; }
	void setx(int x) { this->x = x; }
	void sety(int y) { this->y = y; }

	void wypisz() { cout << "Obstacle: " << x << ":" << y; }

};


#endif // !1


