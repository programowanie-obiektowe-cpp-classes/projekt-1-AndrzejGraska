#pragma once

#include <iostream>
#include <string>

#include "RandomNameGenerator.hpp"

class Pracownik
{
public:
    Pracownik() {}
    std::string imie;
    // int pensja;
    virtual int  wyplata() { return 1000; }
    virtual void print() const {}
    virtual int  wsp_efekt() { return 1; }

    ~Pracownik() {}
};

// TODO dodac randomowy wydzial

class Inz : public Pracownik
{
public:
    std::string      wydzial;
    static const int CI     = 1;
    static const int pensja = 15000;
    int              wsp_efekt() override { return CI; }
    int              wyplata() override { return pensja; }

    Inz()
    {
        imie = getRandomName();
        // wydzial = getRandomName1();
        wydzial = "MEiL";
    }

    void print() const override
    {
        std::cout << "Imie pracownika to: " << imie << ", a jego pensja wynosi: " << pensja;
        std::cout << "Skonczony wydzial to: " << wydzial << "\n";
    }

    ~Inz() {}
};

// TODO dodac randomowa liczbe followersow

class Mkt : public Pracownik
{
public:
    int              followers;
    static const int CMkt   = 1;
    static const int pensja = 7500;

    int wyplata() override { return pensja; }
    int wsp_efekt() override { return CMkt; }

    Mkt()
    {
        imie      = getRandomName();
        followers = 420;
    }

    void print() const override
    {
        std::cout << "Imie pracownika to: " << imie << ", a jego pensja wynosi: " << pensja;
        std::cout << "Liczba followersow to: : " << followers << "\n";
    }

    ~Mkt() {}
};

// TODO dodac randomowa liczbe buta

class Rob : public Pracownik
{
public:
    double           but;
    static const int CR     = 1;
    static const int pensja = 5000;

    int wyplata() override { return pensja; }
    int wsp_efekt() override { return CR; }

    Rob()
    {
        imie = getRandomName();
        but  = 39.4;
    }

    void print() const override
    {
        std::cout << "Imie pracownika to: " << imie << ", a jego pensja wynosi: " << pensja;
        std::cout << "Rozmiar buta to: " << but << "\n";
    }

    ~Rob() {}
};

// TODO dodac randomowe prawo jazdy

class Mag : public Pracownik
{
public:
    bool             prawo_jazdy;
    static const int CMag   = 1;
    static const int pensja = 6000;

    int wyplata() override { return pensja; }
    int wsp_efekt() override { return CMag; }

    Mag()
    {
        imie        = getRandomName();
        prawo_jazdy = true;
    }

    void print() const override
    {
        std::cout << "Imie pracownika to: " << imie << ", a jego pensja wynosi: " << pensja;
        if (prawo_jazdy == true)
        {
            std::cout << "Obsluguje wozek widlowy" << "\n";
        }
        else
        {
            std::cout << "Nie obsluguje wozka widlowego" << "\n";
        }
    }

    ~Mag() {}
};