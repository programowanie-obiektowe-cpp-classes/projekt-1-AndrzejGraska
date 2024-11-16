#pragma once

#include <iostream>

#include "Kredyty.hpp"
#include "Pracownicy.hpp"

#define max_pracownicy 200
#define max_kredytow 20
#define pocz_stan_konta 100000
#define max_tur 500
#define N 12

class Firma
{
public:
    double stan_konta;
    int    liczba_kredytow;
    int    liczba_pracownikow;
    int    licznik_tur;
    double suma_przychodow;

    int liczba_produktow_do_sprzedazy;
    int n_mag;
    int n_inz;
    int n_mkt;
    int n_rob;

    Pracownik* lista_prac[max_pracownicy];
    Kredyt*    lista_kredytow[max_kredytow];
    double     lista_przychodow[max_tur];

    Firma()
    {
        liczba_pracownikow            = 0;
        liczba_kredytow               = 0;
        liczba_produktow_do_sprzedazy = 0;
        licznik_tur                   = 0;
        suma_przychodow               = 0;

        n_mag = 0;
        n_inz = 0;
        n_rob = 0;
        n_mkt = 0;

        zatrudnij(new Inz());
        zatrudnij(new Mkt());
        zatrudnij(new Rob());
        zatrudnij(new Mag());

        stan_konta = pocz_stan_konta;
    }

    // PRACOWNICY, PENSJE, LISTOWANIE, ZATRUDNIANIE

    void zatrudnij(Pracownik* nowy)
    {
        lista_prac[liczba_pracownikow] = nowy;
        liczba_pracownikow++;

        if (dynamic_cast< Inz* >(nowy) != nullptr)
        {
            n_inz++;
        }
        else if (dynamic_cast< Mag* >(nowy) != nullptr)
        {
            n_mag++;
        }
        else if (dynamic_cast< Rob* >(nowy) != nullptr)
        {
            n_rob++;
        }
        else if (dynamic_cast< Mkt* >(nowy) != nullptr)
        {
            n_mkt++;
        }
    }

    void drukuj_pracownikow()
    {
        for (int i = 0; i < liczba_pracownikow; i++)
        {
            lista_prac[i]->print();
        }
    }

    double zaplac_wynagrodzenie()
    {
        double suma_wyplat = 0;
        for (int i = 0; i < liczba_pracownikow; i++)
        {
            suma_wyplat = suma_wyplat + lista_prac[i]->wyplata();
        }
        return suma_wyplat;
    }

    // KREDYTY

    void wez_kredyt(double kwota, int czas_splaty)
    {
        if (liczba_kredytow < max_kredytow)
        {
            lista_kredytow[liczba_kredytow] = new Kredyt(kwota, czas_splaty);
            stan_konta                      = stan_konta + kwota;
            liczba_kredytow++;
        }
        else
        {
            std::cout << "Za duzo kredytow";
        }
    }

    double splac_raty()
    {
        double suma_rat = 0;
        for (int i = 0; i < liczba_kredytow; i++)
        {
            suma_rat = suma_rat + lista_kredytow[i]->splac_rate();
        }
        return suma_rat;
    }

    int liczba_obecnych_kred()
    {
        return liczba_kredytow;
    }

    // LICZBA TOWAROW DO WYPRODUKOWANIA
    int liczba_towarow()
    {
        int sprzedane_towary = 0;
        int pojemnosc_mag    = 0;
        int popyt_mkt        = 0;
        int produkcja        = 0;

        Mag* mag1 = new Mag();
        Mkt* Mk1  = new Mkt();
        Rob* Rob1 = new Rob();

        pojemnosc_mag = n_mag * mag1->wsp_efekt();
        popyt_mkt     = n_mkt * Mk1->wsp_efekt();
        produkcja     = n_rob * Rob1->wsp_efekt();

        if (pojemnosc_mag < produkcja)
        {
            sprzedane_towary = pojemnosc_mag;
        }
        else
        {
            sprzedane_towary = produkcja;
        }

        if (sprzedane_towary < popyt_mkt) {}
        else
        {
            sprzedane_towary = popyt_mkt;
        }

        return sprzedane_towary;
    }

    // PRZYCHODY

    void oblicz_dochod()
    {
        double przychod = otrzymaj_przychod();
        double wyplata  = zaplac_wynagrodzenie();
        double rata     = splac_raty();

        double dochod;
        dochod = przychod - wyplata - rata;

        stan_konta = stan_konta + dochod;
    }

    double get_stan_konta() { return stan_konta; }

    double wartosc_firmy()
    {
        if (licznik_tur == 0)
        {
            suma_przychodow = pocz_stan_konta;
        }
        else if (licznik_tur < N)
        {
            for (int i = 0; i < licznik_tur; i++)
            {
                suma_przychodow = suma_przychodow + lista_przychodow[i];
            }
            suma_przychodow = suma_przychodow / licznik_tur;
        }
        else
        {
            for (int i = 0; i < N; i++)
            {
                suma_przychodow = suma_przychodow + lista_przychodow[licznik_tur - i];
            }
            suma_przychodow = suma_przychodow / N;
        }

        return suma_przychodow;
    }

    double otrzymaj_przychod()
    {
        double przychod      = 0;
        int    ilosc_towarow = liczba_towarow();
        Inz*   inz1          = new Inz();

        przychod = ilosc_towarow * n_inz * inz1->wsp_efekt();

        lista_przychodow[licznik_tur] = przychod;
        licznik_tur++;

        return przychod;
    }

    double oblicz_zadluzenie()
    {
        double zadluzenie = 0;
        for (int i = 0; i < liczba_kredytow; i++)
        {
            zadluzenie = zadluzenie + lista_kredytow[i]->kwota_do_splaty();
        }
        return zadluzenie;
    }

    // Statystyki, dane itp
    void wyciag_firmy()
    {
        std::cout << "Ilosc zatrudnionych inzynierow: " << n_inz << "\n";
        std::cout << "Ilosc zatrudnionych marketerow: " << n_mkt << "\n";
        std::cout << "Ilosc zatrudnionych robotnikow: " << n_rob << "\n";
        std::cout << "Ilosc zatrudnionych magazynierow: " << n_mag << "\n";

        std::cout << "Ilosc wyprodukowamych i sprzedanych produktow: " << liczba_towarow() << "\n";
        std::cout << "Obecna wartosc firmy: " << wartosc_firmy() << "\n";
        std::cout << "Obecna zadluzenie firmy: " << oblicz_zadluzenie() << "\n";
        
    }
};
