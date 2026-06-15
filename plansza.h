#pragma once
#include <vector>

using namespace std;

class Plansza 
{
public:
    struct Pole
    {
        bool mina;
        bool flaga;
        bool odkryte;
        short liczba;
    };
    Pole getPole(int x, int y);//dodałem getter żebym mogl wziac go do main
private:
    int szerokosc;
    int wysokosc;
    int ilosc_min;
    bool koniec_gry;
    int ile_pol_zostalo;
    vector<vector<Pole>> siatka;

    void rozstawMiny();

    void obliczLiczby();

public:
    Plansza(int temp_szerokosc, int temp_wysokosc, int temp_ilosc_min);

    void prawyKlik(int x, int y);

    void lewyKlik(int x, int y);

    void odkryjPola(int x, int y);

    void debugWyswietl();

    void wyswietlPlansze();

    bool czyKoniecGry();

    int getSzerokosc();

    int getWysokosc();
};