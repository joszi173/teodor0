#ifndef Plaszczak_H
#define Plaszczak_H

#include <iostream>
#include<conio.h>
#include<math.h>
#include<ctime>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

using namespace std;
int los(int x, int max);

class Plaszczak
{
	int x;
	int y;
	char z;
	int serduszka;
	int punkty = 0;
public:
	Plaszczak(char z = '?', int x = 0, int y = 0, int s = 2) : z(z), x(x), y(y), serduszka(s) {}
	~Plaszczak() { cout << '~' << z << endl; }

	//gettery, settery
	int getx() const { return x; }
	int gety() const { return y; }
	int gets() const { return serduszka; }
	int getp() const { return punkty; }
	char getz() const { return z; }

	void setx(int x) { this->x = x; }
	void sety(int y) { this->y = y; }
	void sets(int s) { this->serduszka = s; }
	void setp(int p) { this->punkty = p; }

	void addP() { punkty++; }
	void delP() { punkty--; }

	void ruchLewo() { x = x - 1; } //nie moze isc poza pole, albo pojawia sie po drugiej stronie planszy
	void ruchPrawo() { x = x + 1; }
	void ruchGora() { y = y - 1; }
	void ruchDol() { y = y + 1; }

	void drukuj() { cout << z; }
};

int los(int max)
{
	int x = rand() % max;
	if (x >= max)
		x = x - 2;
	if (x <= 0)
		x = x + 2;
	return x;
}

int ruch()
{
	//przypadki, 1 - w gore, w dol, w lewo, w prawo
	// 2- w gore, w dol, w lewo, w prawo
	int x = rand() % 2;
	if (x % 2 == 0)
	{
		x = rand() % 2;
		if (x % 2 == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

bool los2()
{
	int x = rand() % 2;
	if (x % 2 == 0)
	{
		return true;
	}
	else
		return false;
}


void zasady(float czas)
{
	ALLEGRO_BITMAP* smoczek = al_load_bitmap("smoczekd.png"); //ladowanie obrazow
	if (smoczek == NULL)
	{
		fprintf(stderr, "Nie udalo sie wczytac obrazu!\n");
		return;
	}

	ALLEGRO_BITMAP* teodor = al_load_bitmap("teodord.png"); //ladowanie obrazow
	if (teodor == NULL)
	{
		fprintf(stderr, "Nie udalo sie wczytac obrazu!\n");
		return;
	}

	al_draw_bitmap(smoczek, 100, 300, 0);
	al_draw_bitmap(teodor, 700, 20, 0);


	ALLEGRO_COLOR kolor = al_map_rgb(255, 255, 255);
	ALLEGRO_FONT* font = al_create_builtin_font();

	int i = 50;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Czesc, witaj w mojej grze");
	al_flip_display();
	al_rest(1.5);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Zasady:");
	al_flip_display();
	al_rest(1.0);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Poruszasz sie WSADem, a spacja to pasowanie tury");
	al_flip_display();
	al_rest(czas);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Zbieraj monetki, one daja ci punkty");
	al_flip_display();
	al_rest(czas);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Wygrywasz jesli masz 10 x (poziom trudnosci) monetek");
	al_flip_display();
	al_rest(czas);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Dla przykladu: do wygrania na 5 poziomie, musisz zebrac 50 monetek");
	al_flip_display();
	al_rest(czas);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Ilosc smokow na mapie wyznacza poziom trudnosci, 6 smokow = 6. poziom itp");
	al_flip_display();
	al_rest(czas);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Jesli bedziesz mial -10 monetek, koniec gry");
	al_flip_display();
	al_rest(czas);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Uwazaj na smoki, jesli w nie wejdziesz tracisz serduszko");
	al_flip_display();
	al_rest(czas);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Jesli bedziesz mial 0 serduszek przegrywasz");
	al_flip_display();
	al_rest(czas);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Smoki poruszaja sie po mapie i moga zjesc monetki");
	al_flip_display();
	al_rest(czas);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Wtedy moneta teleportuje sie w inne miejsce, a twoje punkty skurczaja sie o 1");
	al_flip_display();
	al_rest(czas);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Wyjscie z gry - ESCAPE");
	al_flip_display();
	al_rest(czas);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "Dobrej zabawy!");
	al_flip_display();
	al_rest(2.0);

	i = i + 20;
	al_draw_textf(font, kolor, 500, i, ALLEGRO_ALIGN_CENTER, "[kliknij dowolny klawisz, aby zaczac]");
	al_flip_display();
	//al_rest(1.0);

	al_destroy_bitmap(smoczek);
	al_destroy_bitmap(teodor);
	al_destroy_font(font);
}


#endif // !1


