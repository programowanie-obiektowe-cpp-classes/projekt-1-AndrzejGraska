#include <iostream>

#include "Gra.hpp"
#include "Firma.hpp"
#include "Pracownicy.hpp"

int main()
{
    Gra gra1{};

    gra1.wylistuj_polecenia();
    
    while(gra1.get_stan()==true)
    {
        gra1.akcja_gracza();
    }
}
