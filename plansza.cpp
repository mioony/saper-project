#include "Plansza.h"
#include <iostream>
#include <cstdlib>

    void Plansza::rozstawMiny()
    {
        int i = 0;
        while(i < ilosc_min)
        {
            int kolumny = rand() % szerokosc;
            int wiersze = rand() % wysokosc;

            if(siatka[wiersze][kolumny].mina == false)
            {
                siatka[wiersze][kolumny].mina = true;
                i++;
            }
        }
    }

    void Plansza::obliczLiczby() 
    {
        for(int y = 0; y < wysokosc; y++) 
        {
            for(int x = 0; x < szerokosc; x++) 
            {
                if(siatka[y][x].mina == true) continue;
                
                short licznik_min = 0;

                for(int przesuniecie_y = -1; przesuniecie_y <= 1; przesuniecie_y++) 
                {
                    for(int przesuniecie_x = -1; przesuniecie_x <= 1; przesuniecie_x++) 
                    {
                        
                        int sprawdz_y = y + przesuniecie_y;
                        int sprawdz_x = x + przesuniecie_x;

                        if(sprawdz_x >= 0 && sprawdz_x < szerokosc && sprawdz_y >= 0 && sprawdz_y < wysokosc)
                            if(siatka[sprawdz_y][sprawdz_x].mina == true)
                                licznik_min++;
                    }
                }
                siatka[y][x].liczba = licznik_min;
            }
        }
    }

    Plansza::Plansza(int temp_szerokosc, int temp_wysokosc, int temp_ilosc_min)
    {
        koniec_gry = false;
        szerokosc = temp_szerokosc;
        wysokosc = temp_wysokosc;
        ilosc_min = temp_ilosc_min;
        //postawione_flagi = 0; //dodalem zerownie licznika
        siatka.resize(wysokosc, vector<Pole>(szerokosc));
        ile_pol_zostalo = szerokosc * wysokosc - ilosc_min;
        rozstawMiny();
        obliczLiczby();
    }

    void Plansza::prawyKlik(int x, int y)
    {
        if(x < 0 || x >= szerokosc || y < 0 || y >= wysokosc)
        {
            return;
        }
        if(siatka[y][x].odkryte == false && siatka[y][x].flaga == false)
        {
            siatka[y][x].flaga = true;
        }
        else if(siatka[y][x].odkryte == false && siatka[y][x].flaga == true)
        {
            siatka[y][x].flaga = false;
        }
    }

    void Plansza::lewyKlik(int x, int y)
    {
        if(x < 0 || x >= szerokosc || y < 0 || y >= wysokosc)
        {
            return;
        }
        if(siatka[y][x].odkryte == false && siatka[y][x].flaga == false)
        {
            odkryjPola(x, y);

            if(ile_pol_zostalo == 0)
            {
                //wygrana
                koniec_gry = true;
            }
        }

    }

    void Plansza::odkryjPola(int x, int y)
    {
        if(x < 0 || x >= szerokosc || y < 0 || y >= wysokosc || siatka[y][x].odkryte == true || siatka[y][x].flaga == true)
        {
            return;
        }
        else
        {
            siatka[y][x].odkryte = true;
            if(siatka[y][x].mina == true)
            {
                //przegrana
                koniec_gry = true;
            }
            else
            {
            ile_pol_zostalo--;
                if(siatka[y][x].liczba > 0)
                {
                    return;
                }
                for(int przesuniecie_y = -1; przesuniecie_y <= 1; przesuniecie_y++) 
                {
                    for(int przesuniecie_x = -1; przesuniecie_x <= 1; przesuniecie_x++) 
                    {
                        odkryjPola(x + przesuniecie_x, y + przesuniecie_y);
                    }
                }
            }
        }
    }

    void Plansza::debugWyswietl()
    {
        for(int i = 0; i < wysokosc; i++)
        {
            for(int j = 0; j < szerokosc; j++)
            {
                if(siatka[i][j].mina == true)
                {
                    cout << "*";
                }
                else
                {
                    cout << siatka[i][j].liczba;
                }
            }
            cout << endl;
        }
    }

    void Plansza::wyswietlPlansze()
    {
        for(int i = 0; i < wysokosc; i++)
        {
            for(int j = 0; j < szerokosc; j++)
            {
                if(siatka[i][j].flaga == true)
                {
                    cout << "F";
                }
                else if(siatka[i][j].odkryte == false)
                {
                    cout << "#";
                }
                else if(siatka[i][j].odkryte == true && siatka[i][j].mina == true)
                {
                    cout << "*";
                }
                else
                {
                    cout << siatka[i][j].liczba;
                }
            }
             cout << endl;
        }
    }

    bool Plansza::czyKoniecGry()
    {
        return koniec_gry;
    }

Plansza::Pole Plansza::getPole(int x, int y)//tutaj też getter
    {
        return siatka[y][x];
    }
int Plansza::getSzerokosc()
    {
        return szerokosc;
    }

int Plansza::getWysokosc()
    {
        return wysokosc;
    }

int Plansza::getIloscMin() //dodalem funkcje do ilosci min
    {
        return ilosc_min;
    }
bool Plansza::czyWygrana(){
    // Gra jest wygrana tylko wtedy, gdy się skończyła i nie ma już bezpiecznych pól do odkrycia
    if (koniec_gry == true && ile_pol_zostalo == 0) {
        return true;
    } else {
        return false;
    }
}
