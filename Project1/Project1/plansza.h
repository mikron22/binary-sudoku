#pragma once
#include <stdio.h>
#include"stale.h"

int wybierzRozmiar(int rozmiar0);
void kopiaPlanszy(int rozmiar, POLE(**pole), POLE(**kopia));
void wczytaj(int rozmiar, POLE **pole);
void pustaPlansza(int rozmiar, POLE(**pole));
void losujPlansze(int rozmiar, POLE(**pole));
void rysuj(int rozmiar, POLE(**pole), char zn, int automatyczneSprawdzanie);