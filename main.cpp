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

public:
    Plansza(int temp_szerokosc, int temp_wysokosc, int temp_ilosc_min)
    {
        szerokosc = temp_szerokosc;
        wysokosc = temp_wysokosc;
        ilosc_min = temp_ilosc_min;
        siatka.resize(wysokosc, vector<Pole>(szerokosc));
        rozstawMiny();
    }

private:
    void obliczLiczby() {
    for(int y = 0; y < wysokosc; y++) {
        for(int x = 0; x < szerokosc; x++) {
            
        }
    }
}

};



int main() {

    std::cout << "Test logiki Sapera" << std::endl;
    
    return 0;
}