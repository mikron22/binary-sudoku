#include <stdio.h>
#include"conio2.h"
#include"stale.h"
#include"sprawdz.h"
#include"plansza.h"
#include<Windows.h>
#include<time.h>




bool zmienWartosc(POLE(**pole), char wartosc, int rozmiar, int x, int y, bool komunikat)
{
	bool zmiana = true;
	POLE cPole = pole[y][x];

	if (pole[y][x].mod == true)
	{
		pole[y][x].wartosc = wartosc;
		pole[y][x].kolor = 2;
		bool reg1 = regula_1(pole, rozmiar, komunikat, wartosc);
		bool reg2 = regula_2(pole, rozmiar, komunikat, wartosc, false);
		bool reg3 = regula_3(pole, rozmiar, komunikat, wartosc);
		if (reg1 == false|| reg2 == false || reg3 == false)
		{
			pole[y][x].wartosc = cPole.wartosc;
			pole[y][x].kolor = cPole.kolor;
			zmiana = false;
		}
	}
	return zmiana;
}


bool regula_1(POLE(**pole), int rozmiar, bool komunikat, char wartosc)
{
	bool spelniona = true;



	for (int y = 0; y < rozmiar; y++)
	{
		int x0 = 0;
		int x1 = 0;
		int y0 = 0;
		int y1 = 0;

		for (int x = 0; x < rozmiar; x++)
		{


			//wiersze

			if (pole[y][x].wartosc == '0')
			{
				x0++;
			}
			else
			{
				x0 = 0;
			}
			if (pole[y][x].wartosc == '1')
			{
				x1++;
			}
			else
			{
				x1 = 0;
			}

			if (x0 == 3 || x1 == 3)
			{
				spelniona = false;

				if (komunikat == true)
				{
					if (wartosc == '0')
					{
						gotoxy(legendaX, legendaY + 24);
					}
					if (wartosc == '1')
					{
						gotoxy(legendaX, legendaY + 25);
					}
					textcolor(WHITE);
					char komunikat[100];
					sprintf(komunikat, "Wpisanie wartosci %c spowoduje, ze w wierszu %d beda trzy takie same pola obok siebie", wartosc, y + 1);
					cputs(komunikat);
				}
			}

			//kolumny
			if (pole[x][y].wartosc == '0')
			{
				y0++;
			}
			else
			{
				y0 = 0;
			}
			if (pole[x][y].wartosc == '1')
			{
				y1++;
			}
			else
			{
				y1 = 0;
			}

			if (y0 == 3 || y1 == 3)
			{
				spelniona = false;

				if (komunikat == true)
				{
					if (wartosc == '0')
					{
						gotoxy(legendaX, legendaY + 26);
					}
					if (wartosc == '1')
					{
						gotoxy(legendaX, legendaY + 27);
					}
					textcolor(WHITE);
					char komunikat[100];
					sprintf(komunikat, "Wpisanie wartosci %c spowoduje, ze w kolumnie %d beda trzy takie same pola obok siebie", wartosc, y + 1);
					cputs(komunikat);
				}
			}
		}

	}
	return spelniona;
}


bool regula_2(POLE(**pole), int rozmiar, bool komunikat, char wartosc, bool dodatkowe)
{
	bool spelniona = true;

	//wiersze

	int zeroW = 0;
	int jedenW = 0;
	for (int y = 0; y < rozmiar; y++)
	{
		for (int x = 0; x < rozmiar; x++)
		{
			if (pole[y][x].wartosc == '0')
			{
				zeroW++;
			}
			if (pole[y][x].wartosc == '1')
			{
				jedenW++;
			}
		}


		if (dodatkowe == true)
		{
			gotoxy(planszaX + rozmiar + 1, planszaY + y);
			putch(zeroW + '0');
			gotoxy(planszaX + rozmiar + 3, planszaY + y);
			putch(jedenW + '0');
		}

		if (zeroW > rozmiar / 2 || jedenW > rozmiar / 2)
		{
			spelniona = false;

			if (komunikat == true)
			{
				gotoxy(legendaX, legendaY + 22);
				textcolor(WHITE);
				char komunikat[100];
				sprintf(komunikat, "Wpisanie wartosci %c spowoduje, ze w wierszu %d bedzie ponad polowa pol z taka wartoscia", wartosc, y + 1);
				cputs(komunikat);
			}

		}

		zeroW = 0;
		jedenW = 0;
	}



	//kolumny

	int zeroK = 0;
	int jedenK = 0;
	for (int x = 0; x < rozmiar; x++)
	{
		for (int y = 0; y < rozmiar; y++)
		{
			if (pole[y][x].wartosc == '0')
			{
				zeroK++;
			}
			if (pole[y][x].wartosc == '1')
			{
				jedenK++;
			}
		}

		if (dodatkowe == true)
		{
			gotoxy(planszaX + x, planszaY + rozmiar + 1);
			putch(zeroK + '0');
			gotoxy(planszaX + x, planszaY + rozmiar + 3);
			putch(jedenK + '0');
		}

		if (zeroK > rozmiar / 2 || jedenK > rozmiar / 2)
		{
			spelniona = false;

			if (komunikat == true)
			{
				gotoxy(legendaX, legendaY + 23);
				textcolor(WHITE);
				char komunikat[100];
				sprintf(komunikat, "Wpisanie wartosci %c spowoduje, ze w kolumnie %d bedzie ponad polowa pol z taka wartoscia", wartosc, x + 1);
				cputs(komunikat);
			}
		}


		jedenK = 0;
		zeroK = 0;

	}

	return spelniona;
}



bool regula_3(POLE(**pole), int rozmiar, bool komunikat, char wartosc)
{
	bool spelniona = true;

	//wiersze
	for (int y = 0; y < rozmiar; y++)
	{
		for (int y1 = y + 1; y1 < rozmiar; y1++)
		{
			int teSame = 0;
			for (int x = 0; x < rozmiar; x++)
			{
				if (pole[y][x].wartosc == pole[y1][x].wartosc && pole[y][x].wartosc != '.')
				{
					teSame++;
				}
				else
				{
					break;
				}
			}
			if (teSame == rozmiar)
			{
				spelniona = false;
				if (komunikat == true)
				{
					gotoxy(legendaX, legendaY + 20);
					textcolor(WHITE);
					char komunikat[100];
					sprintf(komunikat, "Wpisanie wartosci %c spowoduje, ze wiersze %d i %d beda takie same", wartosc, y + 1, y1 + 1);
					cputs(komunikat);
				}
			}
		}

		//kolumny
		for (int x = 0; x < rozmiar; x++)
		{
			for (int x1 = x + 1; x1 < rozmiar; x1++)
			{
				int teSame = 0;
				for (int y = 0; y < rozmiar; y++)
				{
					if (pole[y][x].wartosc == pole[y][x1].wartosc && pole[y][x].wartosc != '.')
					{
						teSame++;
					}
					else
					{
						break;
					}
				}
				if (teSame == rozmiar)
				{
					spelniona = false;
					if (komunikat == true)
					{
						gotoxy(legendaX, legendaY + 21);
						textcolor(WHITE);
						char komunikat[100];
						sprintf(komunikat, "Wpisanie wartosci %c spowoduje, ze kolumny %d i %d beda takie same", wartosc, x + 1, x1 + 1);
						cputs(komunikat);
					}
				}
			}

		}
	}
	return spelniona;
}




int sprawdzPole(POLE(**pole), int rozmiar, bool komunikat, int x, int y)
{
	if (pole[y][x].mod == false)
	{
		if (komunikat == true)
		{
			gotoxy(legendaX, legendaY + 19);
			cputs("Pole jest niemodyfikowalne");
			return 0;
		}
	}




	struct POLE **kopia = (struct POLE**) malloc((rozmiar) * sizeof(struct POLE*));

	for (int i = 0; i < rozmiar; i++)
	{
		kopia[i] = (struct POLE*) malloc((rozmiar) * sizeof(struct POLE));
	}

	kopiaPlanszy(rozmiar, pole, kopia);

	int mozliwosci = 0;
	if (zmienWartosc(kopia, '0', rozmiar, x, y, komunikat) == true)
	{
		mozliwosci++;
		if (komunikat == true)
		{
			gotoxy(legendaX + 50, legendaY + 6);
			textcolor(WHITE);
			putch('0');
		}
	}
	if (zmienWartosc(kopia, '1', rozmiar, x, y, komunikat) == true)
	{
		mozliwosci++;
		if (komunikat == true)
		{
			gotoxy(legendaX + 52, legendaY + 6);
			textcolor(WHITE);
			putch('1');
		}
	}

	for (int i = 0; i < rozmiar; i++)
	{
		free(kopia[i]);
	}
	free(kopia);

	return mozliwosci;
}


bool prosteSprawdzenie(POLE(**pole), int rozmiar, int tryb, char zn)
{
	bool koniec = true;
	for (int y = 0; y < rozmiar; y++)
	{
		for (int x = 0; x < rozmiar; x++)
		{
			if (pole[y][x].wartosc == '.')
			{
				int mozliwosci = sprawdzPole(pole, rozmiar, false, x, y);
				if (mozliwosci == 1 && tryb == jednoznaczne)
				{
					pole[y][x].tlo = BROWN;
				}
				if (mozliwosci == 0 && tryb == niewypelnialne)
				{
					pole[y][x].tlo = MAGENTA;
					koniec = false;
				}
				if (mozliwosci == 0 && tryb == automatyczny)
				{
					koniec = false;
				}
			}
		}
		
	}

	rysuj(rozmiar, pole, zn, 0);

	if (tryb == automatyczny || tryb == niewypelnialne)
	{
		if (koniec == true)
		{
			gotoxy(legendaX + 50, legendaY + 8);
			textattr(WHITE);
			textbackground(BLACK);
			cputs("mozliwe");
		}
		else
		{
			gotoxy(legendaX + 50, legendaY + 8);
			textattr(WHITE);
			cputs("nie mozliwe");
		}
	}

	if (tryb == niewypelnialne)
	{
		char znak = getch();
		if (znak == 0)
		{
			getch();
		}
		{
			for (int y = 0; y < rozmiar; y++)
			{
				for (int x = 0; x < rozmiar; x++)
				{
					if (pole[y][x].tlo == MAGENTA)
					{
						pole[y][x].tlo = LIGHTCYAN;
					}
				}

			}
		}
	}
	

	if (tryb == jednoznaczne)
	{
		char znak = getch();
		if (znak == 0)
		{
			getch();
		}
		{
			for (int y = 0; y < rozmiar; y++)
			{
				for (int x = 0; x < rozmiar; x++)
				{
					if (pole[y][x].tlo == BROWN)
					{
						if (znak == 'w' || znak == 'W')
						{
							zmienWartosc(pole, '0', rozmiar, x, y, false);
							zmienWartosc(pole, '1', rozmiar, x, y, false);
						}
						pole[y][x].tlo = LIGHTCYAN;
					}
				}
			}
		}
	}
	return koniec;
}