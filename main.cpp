#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Plansza.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

int main()
{
    srand(time(NULL));
    // Inicjalizacja biblioteki Allegro 5 oraz jej modułów (klawiatura, mysz, grafika, czcionki TTF)
    Plansza moja_gra(10,10,15);
    al_init();
    al_init_primitives_addon();
    al_install_mouse();
    al_init_font_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_init_ttf_addon();

    int okno_szerokosc = moja_gra.getSzerokosc() * 40;
    int okno_wysokosc = moja_gra.getWysokosc() * 40;

    //funkcje z biblioteki allegro by można było utworzyc czcionke, zeby okno działało, albo tęz żeby byla kolejka zdarzeń
    ALLEGRO_DISPLAY *okno = al_create_display(okno_szerokosc, okno_wysokosc);
    ALLEGRO_EVENT_QUEUE *kolejka = al_create_event_queue();
    ALLEGRO_FONT *czcionka = al_create_builtin_font();
    ALLEGRO_BITMAP *obrazek_miny = al_load_bitmap("mina.png");
    ALLEGRO_BITMAP *obrazek_flagi = al_load_bitmap("flaga.png");
    ALLEGRO_FONT *czcionka2 = al_load_ttf_font("czcionka.ttf", 15, 0);

    al_register_event_source(kolejka, al_get_display_event_source(okno));
    al_register_event_source(kolejka, al_get_mouse_event_source());
    al_register_event_source(kolejka, al_get_keyboard_event_source());

    //musimy oznaczyc ekrany, żeby gra wiedziała w którym panelu jesteśmy i oznaczamy ekran = 0 jako menu głowne, samą plansze oraz gre
    //oznaczymy jako 1
    int ekran = 0;

    bool gra_dziala = true;

    while (gra_dziala) {
        // Czyszczenie okna i nałożenie granatowego tła
        al_clear_to_color(al_map_rgb(30, 34, 45));
        if (ekran == 0) {
            //Tytuł i Autorzy
            al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, 50, ALLEGRO_ALIGN_CENTER, "SAPER");
            al_draw_textf(czcionka2, al_map_rgb(200, 200, 200), okno_szerokosc/2, 90, ALLEGRO_ALIGN_CENTER, "Autorzy: Jakub Horążek, Bartosz Guzy 1ID11B");
            //Przycisk "Graj"
            al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 100, 150, okno_szerokosc/2 + 100, 190, 10, 10, al_map_rgb(39, 174, 96));
            al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, 160, ALLEGRO_ALIGN_CENTER, "GRAJ");

            // Przycisk wyboru trudności
            al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 100, 210, okno_szerokosc/2 + 100, 250, 10, 10, al_map_rgb(41, 128, 185));
            al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, 220, ALLEGRO_ALIGN_CENTER, "WYBOR TRUDNOSCI");

            // Przycisk wychodzenia
            al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 100, 270, okno_szerokosc/2 + 100, 310, 10, 10, al_map_rgb(231, 76, 60));
            al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, 280, ALLEGRO_ALIGN_CENTER, "WYJDZ");

        }
        else if (ekran == 1) {
            for (int x = 0; x < moja_gra.getSzerokosc(); x++) {
                for (int y = 0; y < moja_gra.getWysokosc(); y++) {

                    Plansza::Pole aktualne_pole = moja_gra.getPole(x, y);
                    ALLEGRO_COLOR kolor;
                    //wspołrzedne planszy i kratka ma 40 pikseli
                    int x1 = x * 40;
                    int y1 = y * 40;
                    int x2 = x1 + 38;
                    int y2 = y1 + 38;

                    if (aktualne_pole.flaga == true) {
                        // Niebieskie tło pod flagą, spójne z nieodkrytymi polami
                        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(70, 130, 180));
                        al_draw_scaled_bitmap(obrazek_flagi, 0, 0,
                            al_get_bitmap_width(obrazek_flagi),
                            al_get_bitmap_height(obrazek_flagi),
                            x1, y1, 38, 38, 0);
                    }
                    else if (aktualne_pole.odkryte == false) {
                        kolor = al_map_rgb(70, 130, 180);
                        al_draw_filled_rectangle(x1, y1, x2, y2, kolor);
                    }
                    else {
                        kolor = al_map_rgb(220, 225, 230);
                        al_draw_filled_rectangle(x1, y1, x2, y2, kolor);
                    }
                    //OBRAZEK BOMBY
                    if (aktualne_pole.odkryte == true && aktualne_pole.mina == true) {
                        al_draw_scaled_bitmap(obrazek_miny, 0, 0, al_get_bitmap_width(obrazek_miny), al_get_bitmap_height(obrazek_miny), x1, y1, 38, 38, 0);
                    }
                    //"rysowanie" cyfr na odkrytym obszarze i dany kolor
                    if (aktualne_pole.odkryte == true && aktualne_pole.liczba > 0) {
                        ALLEGRO_COLOR kolor_cyfry;
                        switch (aktualne_pole.liczba) {
                            case 1:
                                kolor_cyfry = al_map_rgb(41, 128, 185); // Niebieski
                                break;
                            case 2:
                                kolor_cyfry = al_map_rgb(39, 174, 96);  // Zielony
                                break;
                            case 3:
                                kolor_cyfry = al_map_rgb(231, 76, 60);  // Czerwony
                                break;
                            case 4:
                                kolor_cyfry = al_map_rgb(0, 0, 0);      // Czarny
                                break;
                            default:
                                kolor_cyfry = al_map_rgb(142, 68, 173); // Fioletowy
                                break;
                        }
                    al_draw_textf(czcionka2, kolor_cyfry, x1 + 20, y1 + 10, ALLEGRO_ALIGN_CENTER, "%d", aktualne_pole.liczba);
                    }
                }
            }

           if (moja_gra.czyWygrana() == true) {
                // Nieco wyższe tło panelu, żeby pomieścić 3 przyciski
                al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 110, okno_wysokosc/2 - 100, okno_szerokosc/2 + 110, okno_wysokosc/2 + 110, 15, 15, al_map_rgb(44, 62, 80));

                // Piękny złoty napis "WYGRAŁEŚ!"
                al_draw_textf(czcionka2, al_map_rgb(255, 215, 0), okno_szerokosc/2, okno_wysokosc/2 - 80, ALLEGRO_ALIGN_CENTER, "WYGRALES!");

                // 1. Przycisk "Zacznij od nowa" (Niebieski)
                al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 90, okno_wysokosc/2 - 30, okno_szerokosc/2 + 90, okno_wysokosc/2, 10, 10, al_map_rgb(41, 128, 185));
                al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, okno_wysokosc/2 - 25, ALLEGRO_ALIGN_CENTER, "ZACZNIJ OD NOWA");

                // 2. Przycisk "Wybierz poziom trudności" (Zielony)
                al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 90, okno_wysokosc/2 + 15, okno_szerokosc/2 + 90, okno_wysokosc/2 + 45, 10, 10, al_map_rgb(39, 174, 96));
                al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, okno_wysokosc/2 + 20, ALLEGRO_ALIGN_CENTER, "POZIOM TRUDNOSCI");

                // 3. Przycisk "Wyjdź" (Czerwony)
                al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 90, okno_wysokosc/2 + 60, okno_szerokosc/2 + 90, okno_wysokosc/2 + 90, 10, 10, al_map_rgb(231, 76, 60));
                al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, okno_wysokosc/2 + 65, ALLEGRO_ALIGN_CENTER, "WYJDZ");
            }
            // JEŚLI TO NIE WYGRANA, A JEST KONIEC GRY
            else if (moja_gra.czyKoniecGry() == true) {
                // Szare tło
                al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 100, okno_wysokosc/2 - 80, okno_szerokosc/2 + 100, okno_wysokosc/2 + 80, 15, 15, al_map_rgb(44, 62, 80));
                // Napis "Koniec Gry"
                al_draw_textf(czcionka2, al_map_rgb(231, 76, 60), okno_szerokosc/2, okno_wysokosc/2 - 60, ALLEGRO_ALIGN_CENTER, "KONIEC GRY");
                // Przycisk "Zacznij od nowa"
                al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 80, okno_wysokosc/2 - 10, okno_szerokosc/2 + 80, okno_wysokosc/2 + 20, 10, 10, al_map_rgb(41, 128, 185));
                al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, okno_wysokosc/2 - 5, ALLEGRO_ALIGN_CENTER, "ZACZNIJ OD NOWA");
                // Przycisk "Wyjdź"
                al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 80, okno_wysokosc/2 + 35, okno_szerokosc/2 + 80, okno_wysokosc/2 + 65, 10, 10, al_map_rgb(231, 76, 60));
                al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, okno_wysokosc/2 + 40, ALLEGRO_ALIGN_CENTER, "WYJDZ");
            }

        }
        else if (ekran == 2) {

            al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, 50, ALLEGRO_ALIGN_CENTER, "WYBIERZ POZIOM TRUDNOSCI");

            // 1. Przycisk "TRUDNY"
            al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 100, 150, okno_szerokosc/2 + 100, 190, 10, 10, al_map_rgb(231, 76, 60));
            al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, 160, ALLEGRO_ALIGN_CENTER, "TRUDNY");

            // 2. Przycisk "SREDNI"
            al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 100, 210, okno_szerokosc/2 + 100, 250, 10, 10, al_map_rgb(41, 128, 185));
            al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, 220, ALLEGRO_ALIGN_CENTER, "SREDNI");

            // 3. Przycisk "LATWY"
            al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 100, 270, okno_szerokosc/2 + 100, 310, 10, 10, al_map_rgb(39, 174, 96));
            al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, 280, ALLEGRO_ALIGN_CENTER, "LATWY");
            // 4. Przycisk "MENU"
            al_draw_filled_rounded_rectangle(okno_szerokosc/2 - 100, 330, okno_szerokosc/2 + 100, 370, 10, 10, al_map_rgb(127, 140, 141));
            al_draw_textf(czcionka2, al_map_rgb(255, 255, 255), okno_szerokosc/2, 340, ALLEGRO_ALIGN_CENTER, "MENU");
        }
        //al_flip_display działa tak że jest double buffering i najpierw program rysuje wszystko, plansze itd a potem "kurtyna" opada i pokazuje wszystko wyrysowane
        al_flip_display();
        ALLEGRO_EVENT zdarzenie;
        /// al_wait_for_event zatrzymuje pętlę i "usypia" program (oszczędzając moc procesora).
        // Funkcja wybudza się natychmiast po ruchu gracza (np. kliknięciu) i pobiera to zdarzenie.
        al_wait_for_event(kolejka, &zdarzenie);


        // Zamknięcie programu po kliknięciu krzyżyka (X) na pasku okna
        if (zdarzenie.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            gra_dziala = false;
        } else if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (ekran == 0) {
                if (zdarzenie.mouse.x > okno_szerokosc/2 - 100 && zdarzenie.mouse.x < okno_szerokosc/2 + 100 && zdarzenie.mouse.y > 150 && zdarzenie.mouse.y < 190) {
                    ekran = 1;
                    moja_gra = Plansza(10, 10, 15);
                    //resizing planszy
                    okno_szerokosc = moja_gra.getSzerokosc() * 40;
                    okno_wysokosc = moja_gra.getWysokosc() * 40;
                    al_resize_display(okno, okno_szerokosc, okno_wysokosc);
                } else if (zdarzenie.mouse.x > okno_szerokosc/2 - 100 && zdarzenie.mouse.x < okno_szerokosc/2 + 100 && zdarzenie.mouse.y > 210 && zdarzenie.mouse.y < 250) {
                    ekran = 2;
                } else if (zdarzenie.mouse.x > okno_szerokosc/2 - 100 && zdarzenie.mouse.x < okno_szerokosc/2 + 100 && zdarzenie.mouse.y > 270 && zdarzenie.mouse.y < 310) {
                    gra_dziala = false;
                }
            } else if (ekran == 1) {
                int klik_x = zdarzenie.mouse.x / 40 ;
                int klik_y = zdarzenie.mouse.y / 40;
                // Obsługa kliknięć na planszy (tylko wtedy, gdy gra wciąż trwa)
                if (moja_gra.czyKoniecGry() == false && moja_gra.czyWygrana() == false){
                    if (zdarzenie.mouse.button == 1){
                        moja_gra.lewyKlik(klik_x, klik_y);
                    } else if (zdarzenie.mouse.button == 2){
                        moja_gra.prawyKlik(klik_x, klik_y);
                    }
                }
                // Działanie przyciskow jak sie wygra
                else if (moja_gra.czyWygrana() == true) {
                    // Przycisk "Zacznij od nowa"
                    if (zdarzenie.mouse.x > okno_szerokosc/2 - 90 && zdarzenie.mouse.x < okno_szerokosc/2 + 90 && zdarzenie.mouse.y > okno_wysokosc/2 - 30 && zdarzenie.mouse.y < okno_wysokosc/2) {
                        moja_gra = Plansza(moja_gra.getSzerokosc(), moja_gra.getWysokosc(), moja_gra.getIloscMin());
                    }
                    // Przycisk "Poziom trudnosci"
                    else if (zdarzenie.mouse.x > okno_szerokosc/2 - 90 && zdarzenie.mouse.x < okno_szerokosc/2 + 90 && zdarzenie.mouse.y > okno_wysokosc/2 + 15 && zdarzenie.mouse.y < okno_wysokosc/2 + 45) {
                        ekran = 2;
                    }
                    // Przycisk "Wyjdz"
                    else if (zdarzenie.mouse.x > okno_szerokosc/2 - 90 && zdarzenie.mouse.x < okno_szerokosc/2 + 90 && zdarzenie.mouse.y > okno_wysokosc/2 + 60 && zdarzenie.mouse.y < okno_wysokosc/2 + 90) {
                        gra_dziala = false;
                    }
                }
                // Dzialanie dla przyciskow jak sie przegra
                else if (moja_gra.czyKoniecGry() == true) {
                    if (zdarzenie.mouse.x > okno_szerokosc/2 - 80 && zdarzenie.mouse.x < okno_szerokosc/2 + 80 && zdarzenie.mouse.y > okno_wysokosc/2 - 10 && zdarzenie.mouse.y < okno_wysokosc/2 + 20) {
                        moja_gra = Plansza(moja_gra.getSzerokosc(), moja_gra.getWysokosc(), moja_gra.getIloscMin());
                    }else if (zdarzenie.mouse.x > okno_szerokosc/2 - 80 && zdarzenie.mouse.x < okno_szerokosc/2 + 80 && zdarzenie.mouse.y > okno_wysokosc/2 + 35 && zdarzenie.mouse.y < okno_wysokosc/2 + 65) {
                        gra_dziala = false;
                    }
                }//odwołanie do 3 róznych poziomow trudnosci
            } else if (ekran == 2) {
                if (zdarzenie.mouse.x > okno_szerokosc/2 - 100 && zdarzenie.mouse.x < okno_szerokosc/2 + 100 && zdarzenie.mouse.y > 150 && zdarzenie.mouse.y < 190) {
                    ekran = 1;
                    moja_gra = Plansza(30, 16, 99); //trudny poziom
                    okno_szerokosc = moja_gra.getSzerokosc() * 40;
                    okno_wysokosc = moja_gra.getWysokosc() * 40;
                    al_resize_display(okno, okno_szerokosc, okno_wysokosc);
                }else if (zdarzenie.mouse.x > okno_szerokosc/2 - 100 && zdarzenie.mouse.x < okno_szerokosc/2 + 100 && zdarzenie.mouse.y > 210 && zdarzenie.mouse.y < 250) {
                    ekran = 1;
                    moja_gra = Plansza(16, 16, 40);//sredni poziom
                    okno_szerokosc = moja_gra.getSzerokosc() * 40;
                    okno_wysokosc = moja_gra.getWysokosc() * 40;
                    al_resize_display(okno, okno_szerokosc, okno_wysokosc);
                }else if (zdarzenie.mouse.x > okno_szerokosc/2 - 100 && zdarzenie.mouse.x < okno_szerokosc/2 + 100 && zdarzenie.mouse.y > 270 && zdarzenie.mouse.y < 310) {
                    ekran = 1;
                    moja_gra = Plansza(8, 8, 1); //latwy poziom
                    okno_szerokosc = moja_gra.getSzerokosc() * 40;
                    okno_wysokosc = moja_gra.getWysokosc() * 40;
                    al_resize_display(okno, okno_szerokosc, okno_wysokosc);
                } else if (zdarzenie.mouse.x > okno_szerokosc/2 - 100 && zdarzenie.mouse.x < okno_szerokosc/2 + 100 && zdarzenie.mouse.y > 330 && zdarzenie.mouse.y < 370) {
                    ekran = 0;
                }
            }
        }
        //PRZYCISK ESCAPE WYCHODZI DO MENU
        else if (zdarzenie.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ekran == 1) {
                if (zdarzenie.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    ekran = 0;
                }
            }
        }
    }

    // Zwalnianie zasobów z pamięci RAM (zapobieganie wyciekom pamięci)
    al_destroy_event_queue(kolejka);
    al_destroy_display(okno);
    al_destroy_font(czcionka);
    al_destroy_bitmap(obrazek_miny);
    al_destroy_bitmap(obrazek_flagi);
    al_destroy_font(czcionka2);
    return 0;
}