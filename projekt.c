
#include <stdio.h>

/*funkcia returnuje pocet znakov v subore */
int PocetZnakovSuboru (FILE *subor);

void nacitanie (FILE *w, int povodny_text[], int pocet_znakov, int *nacitane_nko);

void vypis (int povodny_text[], int pocet_znakov, int *nacitane_nko);

void uprava (int povodny_text[], int pocet_znakov, int upraveny_text[], int *nacitane_nko, int *nacitane_ucko);

int pocet_upravenych (int povodny_text[], int pocet_znakov);

void vypis_upravenych (int upraveny_text[], int pocet_upravenych, int *nacitane_nko, int *nacitane_ucko);

void danadlzka (int povodny_text[], int pocet_znakov, int *nacitane_nko);

void sifra(int upraveny_text[], int pocet_upravenych_znakov, int *nacitane_ucko);

/*funkcia returnuje pocet nacitanych slov v subore */
int PocetSlovNacitanych (FILE *Subor);


int main()
{	
	/*deklaracia pravdivostnej hodnoty ci je n-ko nacitane - po vykonani prikazn sa zmeni na 1 */
	int nacitane_nko = 0;
	/*deklaracia pravdivostnej hodnoty ci je u-cko nacitane - po vykonani prikazu sa zmeni na 1 */
	int nacitane_ucko = 0;

	int vstup;
	
	FILE *fr;
	
	/*printf("Pocet slov nacitanych: %d", PocetSlovNacitanych(fr));*/
	
	/*deklaracia pola povodnytext s poctom prvkov ktory sa rovna poctu znakov v  subore */
	int povodny_text[PocetZnakovSuboru(fr)];
	int upraveny_text[PocetZnakovSuboru(fr)];
	
	while ((vstup = getchar()) != 'k')
	{	
		switch(vstup)
		{
			/*funkia prikazn - pyta si 4 argumenty - prvy je subor z ktoreho cita, druhym je adresa na ktoru zapise prvy znak zo subora, tretim je pocet_znakov ktore sa nachadzaju v subore, stvrtym je adresa premennej nacitane_nko 
			- kedze potrebujem zmenit v behu funkcie jej hodnotu podla toho ktora vetva sa vykona - a v deklaracii funkcie prikazn je zasa nacitane_nko spravovane ako pointer vsade*/
			case 'n' : nacitanie(fr, povodny_text, PocetZnakovSuboru(fr), &nacitane_nko); break;
			
			/*tento prikaz if zistuje ci pred stlacenim pismena v (vypisom znakov) bolo stlacene najprv tlacidlo n (nacitanie znakov). ak ano, premennej nacitane_nko nastavilo hodnotu 1. na tomto principe som vyhodnotil ze ich
			moze vypisat. ak nebolo nacitane tak prevedie else vetvu tuto - respektive vyprintuje - sprava nie je nacitana a odsadi riadok  */
			case 'v' : vypis(povodny_text, PocetZnakovSuboru(fr), &nacitane_nko); break;
			
			case 'u' : uprava(povodny_text, PocetZnakovSuboru(fr), upraveny_text, &nacitane_nko, &nacitane_ucko); break;
			
			case 's' : vypis_upravenych (upraveny_text, pocet_upravenych(povodny_text, PocetZnakovSuboru(fr)), &nacitane_nko, &nacitane_ucko); break;
			
			case 'd' : danadlzka (povodny_text, PocetZnakovSuboru(fr), &nacitane_nko); break;
			
			case 'c' : sifra(upraveny_text, pocet_upravenych(povodny_text, PocetZnakovSuboru(fr)), &nacitane_ucko); break;
		}
	}	
	return 0;	
}

int PocetSlovNacitanych (FILE *Subor)
{
	int znak;
	int pocet_slov = 1;
	
	Subor = fopen("sifra.txt", "r");
	while ((znak = getc(Subor)) != EOF)
	{
		if (znak == ' ')
		{
			pocet_slov++;
		}
	}
	fclose(Subor);
	return pocet_slov;
}

int PocetZnakovSuboru (FILE *subor)
{
	int pocet_znakov = 0;
	subor = fopen("sifra.txt", "r");
	while (getc(subor) != EOF)
	{
		pocet_znakov++;		
	}
	
	if (pocet_znakov > 1000)
	{
		pocet_znakov = 1000;
	}
	else if (pocet_znakov < 1000)
	{
		pocet_znakov = pocet_znakov;
	}
	
	fclose(subor);
	return pocet_znakov;
}

void nacitanie (FILE *w, int povodny_text[], int pocet_znakov, int *nacitane_nko)
{
	int i;
	
	w = fopen("sifra.txt", "r");
	
	if (w == NULL)
	{
		printf("Spravu sa nepodarilo nacitat\n");
		*nacitane_nko = 0;
	}
	else
	{
		for (i = 0; i < pocet_znakov; i++)
		{
			povodny_text[i] = getc(w);
		}
		*nacitane_nko = 1;
	}
	fclose(w);
}

void vypis (int povodny_text[], int pocet_znakov, int *nacitane_nko)
{
	int i;
	
	if (*nacitane_nko == 1)
	{
		for (i = 0; i < pocet_znakov; i++)
		{
			printf("%c", povodny_text[i]);
		}
		printf("\n");
	}
	else
	{
		printf("Sprava nie je nacitana\n");	
	}	
}

void uprava (int povodny_text[], int pocet_znakov, int upraveny_text[], int *nacitane_nko, int *nacitane_ucko)
{
	int pocet_upravenych = 0;
	int i;
	
	if(*nacitane_nko == 0)
	{
		printf("Sprava nie je nacitana\n");	
	}
	
	else
	{
		*nacitane_ucko = 1;			
	}
	
	for (i = 0; i < pocet_znakov; i++)
	{
		/*vetvenie, ktore sleduje ci znak precitany z pola povodny_text je bud velke alebo male pismeno */
		if ((((povodny_text[i] >= 'A') && (povodny_text[i] <= 'Z')) || ((povodny_text[i] >= 'a') && (povodny_text[i] <= 'z'))) && *nacitane_nko == 1)
		{
			/*znak ktory sa tu hore v if-e zisti ze je male/velke pismeno sa nasledne konvertuje na velke pismeno a nasledne dany znakl uklada do pola upraveny_text */
			if (povodny_text[i] >= 'a' && povodny_text[i] <= 'z')
			{
				upraveny_text[pocet_upravenych] = povodny_text[i] - 32;
			}
			/*vetvenie pre ostatne znaky ktore nesedia do intervalu malych pismen (ale kedze cez matersky if presli len velke a male pismena, tak logicky su ako doplnok uz len tie velke pismena) */
			else
			{
				upraveny_text[pocet_upravenych] = povodny_text[i];
			}
			pocet_upravenych++;
		}
	}
}

int pocet_upravenych (int povodny_text[], int pocet_znakov)
{
	int pocetupravenych = 0;
	int i;
	
	for (i = 0; i < pocet_znakov; i++)
	{
		/*vetvenie, ktore sleduje ci znak precitany z pola povodny_text je bud velke alebo male pismeno */
		if (((povodny_text[i] >= 'A') && (povodny_text[i] <= 'Z')) || ((povodny_text[i] >= 'a') && (povodny_text[i] <= 'z')))
		{
			pocetupravenych++;
		}
	}
	return pocetupravenych;
}

void vypis_upravenych (int upraveny_text[], int pocet_upravenych, int *nacitane_nko, int *nacitane_ucko)
{
	int m;
	
	/*pomocou premennych nacitane_ucko a nacitane_nko zistuje ci prebehlo aj zadanie nka na nacitanie prvotnej spravy a taktiez aj uprava textu - len ked su tieto veci splnene mozme vypisat upraveneho textu */
	if(*nacitane_ucko == 1 && *nacitane_nko == 1)
	{	
		/*vyprintuje upraveny text, a to tolko krat, kolko je ulozenych upravenych symbolov v poli upraveny_text. */
		for (m = 0; m < pocet_upravenych; m++)
		{
			printf("%c", upraveny_text[m]);
			/*tento if skontroluje ci su vylacene uz vsetky prvky z upraveneho pola, a ak uz ano, vyprintuje znak noveho riadku */
			if(m == (pocet_upravenych - 1))
			{
				printf("\n");
			}
		}
	}
	else if (*nacitane_ucko == 0 || *nacitane_nko == 0)
	{
		printf("Nie je k dispozicii upravena sprava\n");
	}
}


void danadlzka (int povodny_text[], int pocet_znakov, int *nacitane_nko)
{
	int pismeno = 0;
	int i;
	int j;
	int k;
	
	if (*nacitane_nko == 0)
	{
		printf("Sprava nie je nacitana\n");
	}
	
	else if (*nacitane_nko == 1)
	{
		scanf("%d", &k);
		
		if (k >= 1 && k <= 100)
		{
			for (i = 0; i < pocet_znakov; i++)
			{
				if (povodny_text[i] != ' ')
				{
					pismeno++;
				}
				else if (povodny_text[i] == ' ')
				{
					if (pismeno == k)
					{
						for (j = i - k; j < i; j++)
						{
							printf("%c", povodny_text[j]);
						}
						printf("\n");
						pismeno = 0;
					}
					else
					{
						pismeno = 0;
					}
				}
			}
		}
		else
		{
			printf("Kcko nie je v intervale <0,100>\n");
		}
	}
}

void sifra(int upraveny_text[], int pocet_upravenych_znakov, int *nacitane_ucko)
{
	int i, n;
	
	if (*nacitane_ucko != 1)
	{
		printf("Nie je k dispozicii upravena sprava\n");
	}
	else
	{
		scanf("%d", &n);
		
		if (n >= 1 && n <= 25)
		{
			for (i = 0; i < pocet_upravenych_znakov; i++)
			{
				/*Toto je vetva kedy pri minuse neprechadza na koniec abecedy */
				if (((upraveny_text[i]) - n) >= 65)
				{
					printf("%c", upraveny_text[i] - n);
				}	
				/*Toto je vetvenie kedy prechadza na zaciatok abecedy */
				else if (((upraveny_text[i]) - n) < 65)
				{
					printf("%c", ('Z' - 'A') + upraveny_text[i] - n + 1);
				}
			}
			printf("\n");
		}
		else
		{
			printf("Zadane n-ko nie je z intervalu <1,25>\n");
		}
	}
}
