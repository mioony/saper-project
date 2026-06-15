#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Plansza.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

int main()
{
    srand(time(NULL));
    
    Plansza moja_gra(10,10,15);
    al_init();
    al_init_primitives_addon();
    al_install_mouse();
    al_init_font_addon();


    int okno_szerokosc = moja_gra.getSzerokosc() * 40;
    int okno_wysokosc = moja_gra.getWysokosc() * 40;

    ALLEGRO_DISPLAY *okno = al_create_display(okno_szerokosc, okno_wysokosc);
    ALLEGRO_EVENT_QUEUE *kolejka = al_create_event_queue();
    ALLEGRO_FONT *czcionka = al_create_builtin_font();

    al_register_event_source(kolejka, al_get_display_event_source(okno));
    al_register_event_source(kolejka, al_get_mouse_event_source());

    bool gra_dziala = true;


    while (gra_dziala) {
        al_clear_to_color(al_map_rgb(0, 0, 0)); //czarny ekran
        //rysowanie 100 kwadratów(bo 10x10 plansza)
        for (int x = 0; x < moja_gra.getSzerokosc(); x++) {
            for (int y = 0; y < moja_gra.getWysokosc(); y++) {

                Plansza::Pole aktualne_pole = moja_gra.getPole(x, y);
                ALLEGRO_COLOR kolor;
                    if (aktualne_pole.flaga == true) {
                        kolor = al_map_rgb(255,0,0);
                    }else if (aktualne_pole.odkryte == false) {
                        kolor = al_map_rgb(150,150,150);
                    } else {
                        kolor = al_map_rgb(200,200,200);
                    }

                //wspolrzedne planszy na piksele w oknie
                int x1 = x * 40;
                int y1 = y * 40;
                int x2 = x1 + 38;
                int y2 = y1 + 38;

                al_draw_filled_rectangle(x1, y1 , x2 , y2 ,kolor);

                if (aktualne_pole.odkryte == true && aktualne_pole.liczba > 0) {
                    al_draw_textf(czcionka, al_map_rgb(0,0,250), x1 + 20, y1+ 16, ALLEGRO_ALIGN_CENTER, "%d", aktualne_pole.liczba);
                }
            }

        }
        al_flip_display();
        ALLEGRO_EVENT zdarzenie;
        al_wait_for_event(kolejka, &zdarzenie);

        if (zdarzenie.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            gra_dziala = false;
        }else if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int klik_x = zdarzenie.mouse.x / 40 ;
            int klik_y = zdarzenie.mouse.y / 40;

            if (zdarzenie.mouse.button == 1) {
                moja_gra.lewyKlik(klik_x, klik_y);
            }else if (zdarzenie.mouse.button == 2) {
                moja_gra.prawyKlik(klik_x, klik_y);
            }
        }
        if (moja_gra.czyKoniecGry() == true) {
            gra_dziala = false;
        }
    }


        al_destroy_event_queue(kolejka);
        al_destroy_display(okno);
        al_destroy_font(czcionka);
        return 0;
    }
