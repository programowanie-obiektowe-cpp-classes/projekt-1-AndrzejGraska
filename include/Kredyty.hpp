#pragma once

#include <iostream>

#define Max_wartosc 1000000

class Kredyt
{
public:
    double dlug;
    int    pozostale_raty;
    double procent;

    Kredyt() {}

    Kredyt(double kwota, int czas_splaty)
    {
        dlug           = kwota;
        pozostale_raty = czas_splaty;
        procent        = 0.05;
    }

    double splac_rate()
    {
        double rata = 0;
        rata        = dlug / pozostale_raty;
        dlug        = dlug - rata;
        rata        = rata * (1 + procent);

        return (rata);
    }

    double kwota_do_splaty() { return dlug; }
};