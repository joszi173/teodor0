#ifndef Monetka_H
#define Monetka_H

#include"plaszczak.h"

class Monetka
{
	int x;
	int y;
	bool czy_zeb;
public:
	Monetka(int x = 0, int y = 0, bool czy_zeb = false) : x(x), y(y), czy_zeb(czy_zeb) {}
	~Monetka() { cout << "Monetka zebrana! "; }

	int getx() const { return x; }
	int gety() const { return y; }
	bool getzeb() const { return czy_zeb; }
	void setx(int x) { this->x = x; }
	void sety(int y) { this->y = y; }
	void setz(bool z) { this->czy_zeb = z; }

	void wypisz() { cout << "Monetka: " << x << ":" << y << ", " << czy_zeb << endl; }

};


#endif // !1


