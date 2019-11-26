#pragma once

//Maksymalny rozmiar planszy to 18
#define maxRozmiar 30
//Rozmiar startowy planszy
#define rozmiarS 12

//Pozycja planszy
#define planszaX 70			// nie mniej ni¿ 2 (ramka)
#define planszaY 5			// nie mniej ni¿ 2 (ramka)

//Pozycja legendy
#define legendaX 6
#define legendaY 5

//Losowe wypelnianie
#define minProcent 20
#define maxProcent 40
#define maxProb 5				// maxProb * rozmiar planszy

struct POLE {
	bool mod;					// mo¿liwoœæ modyfikacji
	char wartosc;				// wartoœæ pola : 0 - '0', 1 - '1', 2 - '.'
	int kolor;					// kolor pustego pola
	int tlo;
};

//tryby
#define niewypelnialne 0
#define jednoznaczne 1
#define automatyczny 2


#define wartoscNieuzywana 0