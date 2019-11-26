#include <stdio.h>
#include"conio2.h"
#include"stale.h"
#include"sprawdz.h"
#include"plansza.h"
#include<Windows.h>
#include<time.h>



int wybierzRozmiar(int rozmiar0)
{
	int rozmiar = 0;
	char znak = 0;
	int x = 0;
	while (true)
	{
		gotoxy(legendaX, legendaY + 10);
		puts("Podaj rozmiar planszy: ");

		znak = getch();
		if (znak == 27)
		{
			return rozmiar0;
		}
		if (znak == 0x0d && rozmiar > 1)
		{
			if (rozmiar % 2 == 1) rozmiar++;
			return rozmiar;
		}
		znak -= '0';
		if (znak >= 0 && znak < 10)
		{
			rozmiar = rozmiar * 10 + znak;
		}
		if (rozmiar >= maxRozmiar)
		{
			return maxRozmiar;
		}

		gotoxy(legendaX + x, legendaY + 11);
		putch(znak + '0');
		x++;
	}
}


void wczytaj(int rozmiar, POLE **pole)
{

	char nazwa[32];

	sprintf_s(nazwa, "%i.txt\0", rozmiar);


	FILE *f;
	if ((f = fopen(nazwa, "r")) == NULL)
	{
		losujPlansze(rozmiar, pole);
	}
	else
	{
		fseek(f, 0, 0);
		for (int x = 0; x < rozmiar; x++)
		{
			char *linia = (char*)malloc((size_t)rozmiar + 1);
			fscanf(f, "%s\n", linia);

			for (int y = 0; y < rozmiar; y++)
			{
				pole[x][y].wartosc = linia[y];
				pole[x][y].tlo = LIGHTCYAN;

				if (pole[x][y].wartosc == '.')
				{
					pole[x][y].mod = true;
					pole[x][y].kolor = GREEN;
				}
				else
				{
					pole[x][y].mod = false;
					pole[x][y].kolor = RED;
				}

			}
			free(linia);
		}
		
		fclose(f);
	}

}





void pustaPlansza(int rozmiar, POLE(**pole))
{
	for (int y = 0; y < rozmiar; y++)
	{
		for (int x = 0; x < rozmiar; x++)
		{
			pole[y][x].wartosc = '.';
			pole[y][x].mod = true;
			pole[y][x].kolor = GREEN;
			pole[y][x].tlo = LIGHTCYAN;
		}
	}
}

void kopiaPlanszy(int rozmiar, POLE(**pole), POLE(**kopia))
{
	for (int y = 0; y < rozmiar; y++)
	{
		for (int x = 0; x < rozmiar; x++)
		{
			kopia[y][x].wartosc = pole[y][x].wartosc;
			kopia[y][x].mod = pole[y][x].mod;
			kopia[y][x].kolor = pole[y][x].kolor;
			kopia[y][x].tlo = pole[y][x].tlo;
		}
	}
}


void losujPlansze(int rozmiar, POLE(**pole))
{
	pustaPlansza(rozmiar, pole);
	srand(time(NULL));
	int doWypelnienia = rozmiar*rozmiar*minProcent / 100 + rand() % (maxProcent*rozmiar*rozmiar / 100);
	int wypelnione = 0;
	int p = 0;
	do
	{
		//losowanie pola
		int poleI = rand() % (rozmiar * rozmiar);

		//losowanie wartosci
		char poleC = rand() % 2 + '0';


		if (zmienWartosc(pole, poleC, rozmiar, poleI % rozmiar, poleI / rozmiar, false) == true)
		{
			pole[poleI / rozmiar][poleI % rozmiar].mod = false;
			pole[poleI / rozmiar][poleI % rozmiar].kolor = RED;
			pole[poleI / rozmiar][poleI % rozmiar].tlo = LIGHTCYAN;
			wypelnione++;
		}



		if (p >= maxProb*rozmiar)
		{
			break;
		}
		p++;
	} while (wypelnione < doWypelnienia);
}


void rysuj(int rozmiar, struct POLE(**pole), char zn, int automatyczneSprawdzanie)
{
	textbackground(BLACK);
	textattr(WHITE);
	char txt[32];


	int x = wherex();
	int y = wherey();

	//legenda
	gotoxy(legendaX, legendaY);
	cputs("Krzysztof Orlowski 172149");

	gotoxy(legendaX, legendaY + 2);
	cputs("ESC = wyjscie");
	gotoxy(legendaX, legendaY + 3);
	cputs("strzalki = poruszanie");
	gotoxy(legendaX, legendaY + 4);
	cputs("0, 1 = wpisanie wartosci");
	gotoxy(legendaX, legendaY + 5);
	cputs("o, O = losowa plansza");
	gotoxy(legendaX, legendaY + 6);
	cputs("p, P = prosta podpowiedz");
	gotoxy(legendaX, legendaY + 7);
	cputs("r, R = zmiana rozmiaru planszy");
	gotoxy(legendaX, legendaY + 8);
	cputs("k, K = proste sprawdzenie mozliwosci konca");
	gotoxy(legendaX, legendaY + 9);
	cputs("j, J = pokaz pola jednoznaczne");
	gotoxy(legendaX, legendaY + 10);
	cputs("w, W = wypelnij zaznaczone pola");
	gotoxy(legendaX, legendaY + 11);
	cputs("a, A = tryb automatycznej detekcji konca");
	if (automatyczneSprawdzanie % 2 == 1)
	{
		gotoxy(legendaX + 50, legendaY + 10);
		cputs("wlaczony");
	}
	gotoxy(legendaX, legendaY + 12);
	cputs("d, D = dodatkowa podpowiedz");
	gotoxy(legendaX, legendaY + 13);
	cputs("dzialajace punkty:");
	gotoxy(legendaX, legendaY + 14);
	cputs("a, b, c, d, e, f, g, h, i, j, k, l, m");
	gotoxy(legendaX, legendaY + 15);
	if (zn == 'k' || zn == 'j' || zn == 'J')
	{
		sprintf_s(txt, "pozycja kursora: %d %d", x - planszaX, y - planszaY + 1);
	}
	else
	{
		sprintf_s(txt, "pozycja kursora: %d %d", x - planszaX + 1, y - planszaY + 1);
	}
	cputs(txt);


	//ramka
	for (int y = 0; y < rozmiar + 6; y++)
	{
		if (y == 0 || y == rozmiar + 1 || y == rozmiar + 3 || y == rozmiar + 5)
		{
			for (int x = 0; x < rozmiar + 6; x++)
			{
				gotoxy(planszaX - 1 + x, planszaY + y - 1);
				textattr(RED);
				textbackground(BLUE);
				putch('#');
			}
		}
		else
		{
			gotoxy(planszaX - 1, planszaY + y - 1);
			putch('#');
			gotoxy(planszaX + rozmiar, planszaY + y - 1);
			putch('#');
			gotoxy(planszaX + rozmiar + 2, planszaY + y - 1);
			putch('#');
			gotoxy(planszaX + rozmiar + 4, planszaY + y - 1);
			putch('#');
		}
	}

	//plansza
	for (int y = 0; y < rozmiar; y++)
	{
		for (int x = 0; x < rozmiar; x++)
		{
			gotoxy(planszaX + x, planszaY + y);

			textattr(pole[y][x].kolor);
			textbackground(pole[y][x].tlo);

			putch(pole[y][x].wartosc);
		}
	}
}


