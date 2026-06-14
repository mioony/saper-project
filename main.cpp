#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Plansza.h"

int main() {
    srand(time(NULL));
    
    Plansza moja_gra(10,10,15);
    int x,y;
    while(moja_gra.czyKoniecGry() == false)
    {
        moja_gra.wyswietlPlansze();
        cin >> x >> y;
        moja_gra.lewyKlik(x,y);
    }
    cout << "Koniec gry" << endl;
    moja_gra.debugWyswietl();
    return 0;
}