#include <iostream>
#include <vector>
#include <cstdlib>

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
    
private:
    int szerokosc;
    int wysokosc;
    int ilosc_min;
    bool koniec_gry;
    vector<vector<Pole>> siatka;

    void rozstawMiny()
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

    void obliczLiczby() 
    {
        for(int y = 0; y < wysokosc; y++) 
        {
            for(int x = 0; x < szerokosc; x++) 
            {
                if(siatka[y][x].mina == true) continue;
                
                short licznik_min = 0;

                for(int przesuniecie_y = -1; przesuniecie_y <= 1; przesuniecie_y++) {
                    for(int przesuniecie_x = -1; przesuniecie_x <= 1; przesuniecie_x++) {
                        
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

public:
    Plansza(int temp_szerokosc, int temp_wysokosc, int temp_ilosc_min)
    {
        koniec_gry = false;
        szerokosc = temp_szerokosc;
        wysokosc = temp_wysokosc;
        ilosc_min = temp_ilosc_min;
        siatka.resize(wysokosc, vector<Pole>(szerokosc));
        rozstawMiny();
        obliczLiczby();
    }

    void prawyKlik(int x, int y)
    {
        if(siatka[y][x].odkryte == false && siatka[y][x].flaga == false)
        {
            siatka[y][x].flaga = true;
        }
        else if(siatka[y][x].odkryte == false && siatka[y][x].flaga == true)
        {
            siatka[y][x].flaga = false;
        }
    }

    void lewyKlik(int x, int y)
    {
        if(siatka[y][x].odkryte == false && siatka[y][x].flaga == false)
        {
            siatka[y][x].odkryte = true;
            if(siatka[y][x].mina == true)
            {
                koniec_gry = true;
            }
        }

    }

    void debugWyswietl()
    {
        for(int i = 0; i < wysokosc; i++)
        {
            for(int j = 0; j < szerokosc; j++)
            {
                if(siatka[i][j].mina == true)
                {
                    cout << "*" ;
                }
                else
                {
                    cout << siatka[i][j].liczba;
                }
            }
            cout << endl;
        }
    }

};



int main() {
    
    Plansza moja_gra(10,10,15);
    moja_gra.debugWyswietl();
    return 0;
}