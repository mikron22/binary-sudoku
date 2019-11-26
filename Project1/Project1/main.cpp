#include<stdio.h>
#include"conio2.h"
#include"plansza.h"
#include"stale.h"
#include"sprawdz.h"
#include<Windows.h>
#include<time.h>





/* Uwaga: w docelowym programie nale�y zadeklarowa� odpowiednie
   sta�e, na przyk�ad po to, aby wyeliminowa� z programu
   warto�ci numeryczne umieszczajac w ich miejsce 
   dobrze dobrane identyfikatory */



int main() {
	char zn = 0;
	int x = planszaX, y = planszaY, zero = 0;
	int automatyczneSprawdzanie = 0;
	_setcursortype(_NOCURSOR);

	// aktualny rozmiar planszy
	int rozmiar = rozmiarS;
	
	// plansza gotowa do rysowania


	
	struct POLE **pole = (struct POLE**) malloc((rozmiar) * sizeof(struct POLE*));

	for (int i = 0; i < rozmiar; i++)
	{
		pole[i] = (struct POLE*) malloc((rozmiar) * sizeof(struct POLE));
	}



	pustaPlansza(rozmiar, pole);


	// je�eli program jest kompilowany w czystym j�zyku C
	// nale�y wywo�a� poni�sz� lini�

#ifndef __cplusplus
	Conio2_Init();
#endif

	// settitle ustawia tytu� okienka
	settitle("Krzysztof Orlowski 172149");
	do {
		gotoxy(x, y);
		rysuj(rozmiar, pole, zn, automatyczneSprawdzanie);



		textattr(WHITE);
		gotoxy(x, y);
		textbackground(RED);

		putch(pole[y - planszaY][x - planszaX].wartosc);
		

		textbackground(BLACK);
		// czekamy na naci�ni�cie klawisza i odczytujemy jego kod,
		// wi�kszo�� kod�w klawiszy odpowiada ich znakom, np.
		// a to 'a', 2 to '2', + to '+', ale niekt�re klawisze
		// specjalne, np. strza�ki s� zg�aszane jako dwa kolejne znaki,
		// z kt�rych pierwszy jest zerem, np. strza�ka w g�r�
		// to zero i 'H'
		zero = 0;
		zn = getch();
		clrscr();
		// nie chcemy, aby klawisz 'H' dzia�a� jako strza�ka w g�r�
		// wi�c sprawdzamy, czy pierwszym znakiem by�o zero
		if(zn == 0) {
			zero = 1;
			zn = getch();
			if (zn == 0x48)
			{
				if (y > planszaY) y--;
			}
			else if (zn == 0x50)
			{
				if (y < planszaY + rozmiar - 1) y++;
			}
			else if (zn == 0x4b)
			{
				if (x > planszaX) x--;
			}
			else if(zn == 0x4d)
			{
				if (x < planszaX + rozmiar -1) x++;
			}
		}// else if(zn == ' ') attr = (attr + 1) % 16;
//		else if(zn == 0x0d) back = (back + 1) % 16;
		else if (zn == '0')
		{
			zmienWartosc(pole, '0', rozmiar, wherex() - 1 - planszaX, wherey() - planszaY, false);
			if (automatyczneSprawdzanie % 2 == 1)
			{
				prosteSprawdzenie(pole, rozmiar, automatyczny, zn);
				regula_2(pole, rozmiar, false, wartoscNieuzywana, true);
			}
			zn = 0;
		}
		else if (zn == '1')
		{
			zmienWartosc(pole, '1', rozmiar, wherex() - 1 - planszaX, wherey() - planszaY, false);
			if (automatyczneSprawdzanie % 2 == 1)
			{
				prosteSprawdzenie(pole, rozmiar, automatyczny, zn);
				regula_2(pole, rozmiar, false, wartoscNieuzywana, true);
			}
			zn = 0;

		}
		else if (zn == 'o' || zn == 'O') 
		{
			losujPlansze(rozmiar, pole);
			zn = 0;
		}
		else if (zn == 'p' || zn == 'P')
		{
			sprawdzPole(pole, rozmiar, true, wherex() - 1 - planszaX, wherey() - planszaY);
			zn = 0;
		}
		else if (zn == 'n' || zn == 'N')
		{
			rozmiar = 12;

			pole = (struct POLE**)realloc(pole, (size_t)rozmiar * sizeof(*pole));

			for (int i = 0; i < rozmiar; i++)
			{
				pole[i] = (struct POLE*)malloc((size_t)rozmiar * sizeof(struct POLE));
			}

			wczytaj(rozmiar, pole);

			y = planszaY;
			x = planszaX;
			zn = 0;
		}
		else if (zn == 'r' || zn == 'R')
		{
			rozmiar = wybierzRozmiar(rozmiar);

			pole = (struct POLE**)realloc(pole, (size_t)rozmiar * sizeof(*pole));

			for (int i = 0; i < rozmiar; i++)
			{
				pole[i] = (struct POLE*)malloc((size_t)rozmiar * sizeof(struct POLE));
			}

			wczytaj(rozmiar, pole);

			y = planszaY;
			x = planszaX;
			zn = 0;

		}
		else if (zn == 'k' || zn == 'K')
		{
			prosteSprawdzenie(pole, rozmiar, niewypelnialne, zn);
			zn = 0;

		}
		else if (zn == 'j' || zn == 'J')
		{
			prosteSprawdzenie(pole, rozmiar, jednoznaczne, zn);
			zn = 0;

		}
		else if (zn == 'a' || zn == 'K')
		{
			automatyczneSprawdzanie++;
			zn = 0;

		}
		else if (zn == 'd' || zn == 'D')
		{
			regula_2(pole, rozmiar, false, wartoscNieuzywana, true);
			zn = 0;

		}
	} while (zn != 27);


	for (int i = 0; i < rozmiar; i++)
	{
		free(pole[i]);
	}

	free(pole);



	return 0;
	}
