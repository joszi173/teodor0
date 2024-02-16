#ifndef Planeta_H
#define Planeta_H

#include"plaszczak.h"
#include"monetka.h"
#include"obstacle.h"

class Planeta
{
    int szer;
    int wys;
    Plaszczak* p;

    Monetka* tab[100];
    int ilosc_m = 0;

    Obstacle* tab1[100];
    int ilosc_o = 0;





public:

    Planeta(int szer, int wys, Plaszczak* p);
    ~Planeta() { cout << '~' << "Planeta"; }


    void drukuj() const;
    void drukuj2() const;
    void dodajM(Monetka* M1);
    void dodajO(Obstacle* O1);


    void pokaz();

    int getIlosc() { return ilosc_m; }
};



void Planeta::drukuj2() const
{
    system("cls");
    //kolory
    ALLEGRO_COLOR kolor = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR tlo = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR kolor1 = al_map_rgb(198, 198, 198);
    ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);


    ALLEGRO_FONT* font = al_create_builtin_font();



    int multi = 40; //multiplikator

    int tabx = -1;
    int taby = -1;
    int tab1y = -1;
    int tab1x = -1;
    int mon = 0;


    ALLEGRO_BITMAP* plaszczak1 = al_load_bitmap("teodor3.png"); //ladowanie obrazow
    if (plaszczak1 == NULL)
    {
        fprintf(stderr, "Nie udalo sie wczytac obrazu teodor3!\n");
        return;
    }
    ALLEGRO_BITMAP* coin = al_load_bitmap("coin.png");
    if (coin == NULL)
    {
        fprintf(stderr, "Nie udalo sie wczytac obrazu coin!\n");
        return;
    }

    ALLEGRO_BITMAP* obstacle = al_load_bitmap("smoczek.png");
    if (coin == NULL)
    {
        fprintf(stderr, "Nie udalo sie wczytac obrazu smoczek!\n");
        return;
    }






    if (p->getp() >= ilosc_o * 10)
    {
        al_draw_filled_rectangle(0, 0, 9999, 9999, tlo);
        al_draw_textf(font, kolor, 500, 50, ALLEGRO_ALIGN_CENTER, "VICTORY");
        al_draw_textf(font, kolor, 500, 70, ALLEGRO_ALIGN_CENTER, "Udalo ci sie zdobyc maksymalna liczbe punktow (%d) na %d. poziomie trudnosci!", p->getp(), ilosc_o);
        al_draw_textf(font, red, 500, 90, ALLEGRO_ALIGN_CENTER, "Dziekuje za gre :)");
        al_flip_display();
        al_rest(5);
        exit(1);

    }



    al_draw_filled_rectangle(0, 0, 9999, 9999, tlo);



    for (int n = 0; n < ilosc_m; n++) //rozstawianie monetek
    {
        if (tab[n]->getx() == tabx && tab[n]->gety() == taby)
        {
            //sprawdzam czy monetki siê nie stackuja
            tab[n]->setx(los(szer));
            tab[n]->sety(los(wys));
        }

        if (!tab[n]->getzeb()) //jak nie jest zebrana to jest widoczna na planszy
        {
            al_draw_bitmap(coin, tab[n]->getx() * multi, tab[n]->gety() * multi, 0);
        }

        if (p->getx() == tab[n]->getx() && p->gety() == tab[n]->gety() && !tab[n]->getzeb())
        {
            //ludzik zbiera monetke i wspolrzedne sie zmieniaja
            p->addP();
            tab[n]->setz(1);
            al_draw_textf(font, kolor, 1000, 100, ALLEGRO_ALIGN_CENTER, "Zebrano monetke");
            tab[n]->setx(los(szer));
            tab[n]->sety(los(wys));
            tab[n]->setz(0);
        }

        tabx = tab[n]->getx(); //zapisuje 'stare' wspolrzedne monetki
        taby = tab[n]->gety();
    }



    for (int n = 0; n < ilosc_o; n++) //rozstawianie przeszkod
    {

        if (tab1[n]->getx() == tab1x && tab1[n]->gety() == tab1y)
        {
            //sprawdzam czy obstacle siê nie stackuja
            if (los2())
                tab1[n]->setx(tab1[n]->getx() + ruch());
            else
                tab1[n]->setx(tab1[n]->getx() - ruch());
            if (los2())
                tab1[n]->sety(tab1[n]->gety() + ruch());
            else
                tab1[n]->sety(tab1[n]->gety() - ruch());
        }

        al_draw_bitmap(obstacle, tab1[n]->getx() * multi, tab1[n]->gety() * multi, 0);
        //al_draw_filled_rectangle(tab1[n]->getx() * multi, tab1[n]->gety() * multi, (tab1[n]->getx() + 1) * multi, (tab1[n]->gety() + 1) * multi, red);
        if (tab1[n]->getx() == p->getx() && tab1[n]->gety() == p->gety())
        {
            al_draw_filled_rectangle(0, 0, 9999, 9999, tlo);
            if (p->gets() == 0)
            {

                al_draw_textf(font, kolor, 500, 50, ALLEGRO_ALIGN_CENTER, "GAME OVER");
                al_draw_textf(font, kolor, 500, 70, ALLEGRO_ALIGN_CENTER, "Udalo ci sie zdobyc %d punktow na %d. poziomie trudnosci!", p->getp(), ilosc_o);

                al_flip_display();

                al_rest(5.0);
                al_destroy_bitmap(plaszczak1);
                al_destroy_bitmap(obstacle);
                al_destroy_bitmap(coin);
                al_destroy_font(font);

                exit(1);
            }
            else
            {
                al_draw_textf(font, red, 500, 50, ALLEGRO_ALIGN_CENTER, "Uwaga, wszedles w smoka, zostalo ci %d szans", p->gets() - 1);
                al_draw_textf(font, red, 500, 70, ALLEGRO_ALIGN_CENTER, "Teleportuje cie w inne miejsce...");
                al_draw_textf(font, red, 500, 90, ALLEGRO_ALIGN_CENTER, "[wcisnij dowolny przycisk]");
                al_flip_display();
                p->sets(p->gets() - 1);
                p->setx(los(szer));
                p->setx(los(wys));

                return;
            }
        }

        //jesli obstacle dotknie monetki, ona zmienia wspolrzedne i odejmuje jeden punkt
        for (int u = 0; u < ilosc_m; u++)
        {
            if (tab1[n]->getx() == tab[u]->getx() && tab1[n]->gety() == tab[u]->gety())
            {
                al_draw_textf(font, kolor, 1000, 110, ALLEGRO_ALIGN_CENTER, "Smok zjadl monetke");
                mon = 1;
                tab[u]->setx(los(szer));
                tab[u]->sety(los(wys));
                p->delP();
            }
        }


        //zmiana wspolrzednych
        if (los2())
        {
            if (los2())
                tab1[n]->setx(tab1[n]->getx() + ruch());
            else
                tab1[n]->setx(tab1[n]->getx() - ruch());

        }
        else
        {
            if (los2())
                tab1[n]->sety(tab1[n]->gety() + ruch());
            else
                tab1[n]->sety(tab1[n]->gety() - ruch());

        }
        //cout << "Wspolrzedne: " << tab1[n]->getx() << " " << tab1[n]->gety() << endl;



        if (tab1[n]->getx() > szer) //jesli obstacle wyjdzie poza pole- x
            tab1[n]->setx(0);
        if (tab1[n]->getx() < 0)
            tab1[n]->setx(szer);

        if (tab1[n]->gety() > wys) //jesli obstacle wyjdzie poza pole- y
            tab1[n]->sety(0);
        if (tab1[n]->gety() < 0)
            tab1[n]->sety(wys);

        tab1x = tab1[n]->getx();
        tab1y = tab1[n]->gety();
    }









    for (int i = 0; i <= wys; i++) //rysowanie planszy
    {



        for (int j = 0; j <= szer; j++)
        {



            al_draw_rectangle(j * multi, i * multi, (j + 1) * multi, (i + 1) * multi, kolor, 1); //rysuje plansze zlozona z kwadratow

            /*if (j == p->getx() && i == p->gety())
                al_draw_filled_rectangle(j*multi, i*multi, (j+1) * multi, (i+1) * multi, kolor1); //pokazuje kafelek na ktorym jest ludzik*/

            if (p->getx() > szer) //jesli ludzik wyjdzie poza pole- x
                p->setx(0);
            if (p->getx() < 0)
                p->setx(szer);

            if (p->gety() > wys) //jesli ludzik wyjdzie poza pole- y
                p->sety(0);
            if (p->gety() < 0)
                p->sety(wys);
        }


        al_draw_bitmap(plaszczak1, p->getx() * multi, p->gety() * multi, 0); //rysuje ludzika



    }

    al_draw_textf(font, kolor, 1000, 50, ALLEGRO_ALIGN_CENTER, "Poziom trudnosci: %d", ilosc_o);
    al_draw_textf(font, kolor, 1000, 70, ALLEGRO_ALIGN_CENTER, "Punkty: %d/%d", p->getp(), ilosc_o * 10);
    al_draw_textf(font, kolor, 1000, 90, ALLEGRO_ALIGN_CENTER, "Serduszka: %d", p->gets());


    if (p->getp() <= -10) //przegrana przez punkty
    {
        al_draw_filled_rectangle(0, 0, 9999, 9999, tlo);
        al_draw_textf(font, kolor, 500, 50, ALLEGRO_ALIGN_CENTER, "GAME OVER");
        al_draw_textf(font, kolor, 500, 70, ALLEGRO_ALIGN_CENTER, "Przegrales ze smokami :(");

        al_flip_display();

        al_rest(5.0);
        al_destroy_bitmap(plaszczak1);
        al_destroy_bitmap(obstacle);
        al_destroy_bitmap(coin);
        al_destroy_font(font);

        exit(1);
    }




    al_flip_display();
    al_destroy_bitmap(plaszczak1);
    al_destroy_bitmap(obstacle);
    al_destroy_bitmap(coin);
    al_destroy_font(font);

    // cout << "Punkty: " << p->getp() << endl;
     //cout << "Twoje wspolrzedne: " << p->getx() << " " << p->gety() << endl;
    // cout << "Poziom trudnosci: " << ilosc_o << endl;
}





void Planeta::pokaz()
{
    for (int i = 0; i < ilosc_m; i++)
    {
        cout << "tab[" << i << "]= ";
        tab[i]->wypisz();
    }
}

void Planeta::dodajM(Monetka* M1)
{
    tab[ilosc_m] = M1;
    ilosc_m++;

}

void Planeta::dodajO(Obstacle* O1)
{
    tab1[ilosc_o] = O1;
    ilosc_o++;

}

Planeta::Planeta(int szer, int wys, Plaszczak* p)
{
    this->szer = szer;
    this->wys = wys;
    this->p = p;
    p->setx(szer / 2);
    p->sety(wys / 2);
}

void Planeta::drukuj() const
{
    bool znak = 0;
    for (int i = 0; i <= wys - 1; i++)
    {

        for (int j = 0; j <= szer - 1; j++)
        {
            if (i == 0 || i == wys - 1) //ramka
            {
                cout << "-";
            }

            if (j == 0 || j == szer - 1) //ramka
            {
                if (i != 0 && i != wys - 1)
                    cout << "|";
            }

            if (i != 0 && i != wys - 1 && j != 0 && j != szer - 1) //puste pola
            {
                if (i == p->gety() && j == p->getx())
                {
                    cout << p->getz();
                    znak = 1;
                }

                for (int n = 0; n < ilosc_m; n++)
                {
                    if (i == tab[n]->gety() && j == tab[n]->getx())
                    {
                        cout << 'O';
                        znak = 1;
                    }
                }
                if (znak == 0)
                {
                    cout << " ";
                    znak = 0;
                }
                znak = 0;
            }
            if (p->getx() >= szer - 1) //jesli wyjdzie poza pole- x
                p->setx(1);
            if (p->getx() <= 0)
                p->setx(szer - 2);

            if (p->gety() >= wys - 1) //jesli wyjdzie poza pole- y
                p->sety(1);
            if (p->gety() <= 0)
                p->sety(wys - 2);


        }
        cout << endl;
    }
    cout << "Pozycja: " << p->getx() << ":" << p->gety() << endl;
}

#endif // !1


