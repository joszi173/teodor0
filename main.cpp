#include"planeta.h"
#include"monetka.h"

//allegro.h




int main()
{
    srand(time(NULL));
    al_init_primitives_addon();
    if (!al_init())
    {
        return -1;
    }

    if (!al_init_image_addon())
    {
        return -1;
    }


    int szer = 10;
    int wys = 10;

    ALLEGRO_DISPLAY* display = al_create_display(1260, 600);
    if (!display)
    {
        return -1;
    }






    Plaszczak Teodor(char(1));



    Planeta Rect001(szer, wys, &Teodor);



    Monetka* M1 = new Monetka(los(szer), los(wys), 0);
    Rect001.dodajM(M1);

    Monetka* M2 = new Monetka(los(szer), los(wys), 0);
    Rect001.dodajM(M2);

    Monetka* M3 = new Monetka(los(szer), los(wys), 0);
    Rect001.dodajM(M3);

    Monetka* M4 = new Monetka(los(szer), los(wys), 0);
    Rect001.dodajM(M4);



    Obstacle* O1 = new Obstacle(los(szer), los(wys));
    Rect001.dodajO(O1);

    Obstacle* O2 = new Obstacle(los(szer), los(wys));
    Rect001.dodajO(O2);

    Obstacle* O3 = new Obstacle(los(szer), los(wys));
    Rect001.dodajO(O3);





    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_COLOR kolor = al_map_rgb(255, 255, 255);


    al_install_keyboard();
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    ALLEGRO_EVENT ev;
    bool exit = false;



    zasady(3);



    while (!exit)
    {
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_W: Teodor.ruchGora(); break;
            case ALLEGRO_KEY_S: Teodor.ruchDol(); break;
            case ALLEGRO_KEY_A: Teodor.ruchLewo(); break;
            case ALLEGRO_KEY_D: Teodor.ruchPrawo(); break;
            case ALLEGRO_KEY_SPACE: al_draw_textf(font, kolor, 1000, 120, ALLEGRO_ALIGN_CENTER, "Pominieto ture"); al_flip_display(); al_rest(0.5);  break;
            case ALLEGRO_KEY_ESCAPE: exit = true; break;
            }

            Rect001.drukuj2();
        }
    }

    al_destroy_font(font);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_uninstall_system();
    al_uninstall_keyboard();

    delete M1;
    delete M2;
    delete M3;
    delete M4;


    delete O1;
    delete O2;
    delete O3;


    return 0;
}

