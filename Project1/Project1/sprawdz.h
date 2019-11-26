#pragma once
#include"stale.h"

bool zmienWartosc(POLE(**pole), char wartosc, int rozmiar, int x, int y, bool komunikat);

bool regula_1(POLE(**pole), int rozmiar, bool komunikat, char wartosc);
bool regula_2(POLE(**pole), int rozmiar, bool komunikat, char wartosc, bool dodatkowe);
bool regula_3(POLE(**pole), int rozmiar, bool komunikat, char wartosc);

int sprawdzPole(POLE(**pole), int rozmiar, bool komunikat, int x, int y);
bool prosteSprawdzenie(POLE(**pole), int rozmiar, int tryb, char zn);