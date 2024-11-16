#pragma once

#include <iostream>
#include <string>

#include "Firma.hpp"

#define M 3
#define kwota_wygranej 1000000

class Gra
{
public:
    bool  stan;
    Firma firma;

    Gra()
    {
        stan  = true;
        firma = Firma{};
    }

    void tick()
    {
        firma.oblicz_dochod();
        std::cout << "Stan konta: " << firma.get_stan_konta() << "\n";
    }

    void akcja_gracza()
    {
        std::cout << "Wprowadz polecenie: \n";
        std::string input;
        std::cin >> input;

        if (input == "lp")
        {
            firma.drukuj_pracownikow();
        }
        else if (input == "zinz")
        {
            firma.zatrudnij(new Inz());
        }
        else if (input == "zrob")
        {
            firma.zatrudnij(new Rob());
        }
        else if (input == "zmkt")
        {
            firma.zatrudnij(new Mkt());
        }
        else if (input == "zmag")
        {
            firma.zatrudnij(new Mag());
        }
        else if (input == "kred")
        {
            std::cout << "Podaj kwote kredytu: " << "\n";
            double kw;
            std::cin >> kw;

            std::cout << "Podaj czas splaty: " << "\n";
            int rat;
            std::cin >> rat;

            firma.wez_kredyt(kw, rat);
        }
        else if (input == "kt")
        {
            tick();
        }
    }

    bool get_stan()
    {
        double wartosc_firmy = firma.wartosc_firmy();
        double stan_konta    = 0;
        stan_konta           = firma.get_stan_konta();

        double wartosc_zadluzenia = 0;
        wartosc_zadluzenia        = firma.oblicz_zadluzenie();

        double czy_wygrana = 0;
        czy_wygrana        = firma.wartosc_firmy();

        if (stan_konta <= 0 || wartosc_zadluzenia > (M * wartosc_firmy))
        {
            std::cout << "Porazka" << "\n";
            stan = false;
        }
        if (czy_wygrana >= kwota_wygranej)
        {
            std::cout << "Zwyciestwo" << "\n";
            stan = false;
        }

        return stan;
    }

    void wylistuj_polecenia()
    {
        std::cout << " Podaj jedno z ponizszych polecen: \n lp - wylistuj pracownikow (imiona i wynagrodzenia) \n zinz "
                     "- zatrudnij inz. \n zmag - zatrudnij mag. \n zmkt - zatrudnij mark. \n zrob - zatrudnij rob. \n "
                     "kred - wez kredyt(w nastepnym kroku podaj kwote i czas splaty) \n kt - zakoncz ture i wyswietl "
                     "stan firmy na poczatku nastepnego miesiaca "
                  << "\n ";
    }
};