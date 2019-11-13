
#include <stdio.h>

void prikazn (FILE *w, int prvy_text[0], int pocet_znakov, int *nacitane_nko);


int main()
{
	int vstup;
	
	int c, i, m, j = 0, pocet_znakov = 0, prikaz;
	int k = 1;
	/*deklaracia pravdivostnej hodnoty ci je n-ko nacitane - po vykonani prikazn sa zmeni na 1 */
	int nacitane_nko = 0;
	/*deklaracia pravdivostnej hodnoty ci je u-cko nacitane - po vykonani prikazu sa zmeni na 1 */
	int nacitane_ucko = 0;
	int pismeno = 0;
	
	
	FILE *fr;
	
	fr = fopen("sifra.txt", "r");
	
	/*ZISTUJE POCET ZNAKOV V SUBORE SPOLU */
	while (getc(fr) != EOF)
	{
		pocet_znakov++;		
	}
		
	/*toto je vetvenie ktore ked je pocetznakov v subore menej ako 1000 tak ho necha zapisat do suboru v takom pocte v akom ho tam realne je */
	if (pocet_znakov < 1000)
	{
		pocet_znakov = pocet_znakov;
	}
	/*toto je vetvenie aby ked je sprava dlhsia ako 1000 znakov nacitalo nasledne do pola maximalne 1000 znakov */
	else if (pocet_znakov > 1000)
	{
		pocet_znakov = 1000;
	}
	
		
	/*deklaracia pola povodnytext s poctom prvkov ktory sa rovna poctu znakov v nacitanom subore */
	int povodny_text[pocet_znakov];
	int upraveny_text[pocet_znakov];
	
	/*toto bude loop ktory bude neustale pytat vstup od pouzivatela kym k = 1. Pri stlaceni gombiku na ukoncenie programu sa tento loop porusi (napr k bude rovne nule, vide sa z neho a program sa skonci) */
	while (k == 1)
	{		
		/*tento scanf pyta vstup */
		scanf("%c", &prikaz);
		
		/*Vetvenie pre nacitanie sifrovanej spravy do pola */
		if(prikaz == 'n')
		{
			/*funkia prikazn - pyta si 4 argumenty - prvy je subor z ktoreho cita, druhym je adresa na ktoru zapise prvy znak zo subora, tretim je pocet_znakov ktore sa nachadzaju v subore, stvrtym je adresa premennej nacitane_nko 
			- kedze potrebujem zmenit v behu funkcie jej hodnotu podla toho ktora vetva sa vykona - a v deklaracii funkcie prikazn je zasa nacitane_nko spravovane ako pointer vsade*/
			prikazn(fr, &povodny_text[0], pocet_znakov, &nacitane_nko);
		}
		
		/*Toto je vetvenie pre pripad ze uzivatel stlaci na klavesnici pismeno v */
		else if(prikaz == 'v')
		{
			/*tento prikaz if zistuje ci pred stlacenim pismena v (vypisom znakov) bolo stlacene najprv tlacidlo n (nacitanie znakov). ak ano, premennej nacitane_nko nastavilo hodnotu 1. na tomto principe som vyhodnotil ze ich
			moze vypisat. ak nebolo nacitane tak prevedie else vetvu tuto - respektive vyprintuje - sprava nie je nacitana a odsadi riadok  */
			if (nacitane_nko == 1)
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
		/*vetvenie pre pripad ked sa na klavesnici stlaci pismeno u */
		else if(prikaz == 'u')
		{
			for (i = 0; i < pocet_znakov; i++)
			{
				/*vetvenie, ktore sleduje ci znak precitany z pola povodny_text je bud velke alebo male pismeno */
				if ((((povodny_text[i] >= 'A') && (povodny_text[i] <= 'Z')) || ((povodny_text[i] >= 'a') && (povodny_text[i] <= 'z'))) && nacitane_nko == 1)
				{
					/*znak ktory sa tu hore v if-e zisti ze je male/velke pismeno sa nasledne konvertuje na velke pismeno a nasledne dany znakl uklada do pola upraveny_text */
					if (povodny_text[i] >= 'a' && povodny_text[i] <= 'z')
					{
						upraveny_text[j] = povodny_text[i] - 32;
					}
					/*vetvenie pre ostatne znaky ktore nesedia do intervalu malych pismen (ale kedze cez matersky if presli len velke a male pismena, tak logicky su ako doplnok uz len tie velke pismena) */
					else
					{
						upraveny_text[j] = povodny_text[i];
					}
					/*printf("%c", upraveny_text[j]);*/
					j++;
				}
				/*toto je vetvenie ktore urobi novy riadok ked sa vlastne skonci kopirovanie posledneho dobreho znaku do noveho pola 
				else if(i == pocet_znakov - 1)
				{
					printf("\n");
				}*/
			}
			if(nacitane_nko == 0)
			{
				printf("Sprava nie je nacitana\n");	
			}
			nacitane_ucko = 1;		
		}
		/*vetvenie pre pripad ze sa na klavesnici stlaci pismeno s */
		else if(prikaz == 's')
		{
			/*pomocou premennych nacitane_ucko a nacitane_nko zistuje ci prebehlo aj zadanie nka na nacitanie prvotnej spravy a taktiez aj uprava textu - len ked su tieto veci splnene mozme vypisat upraveneho textu */
			if(nacitane_ucko == 1 && nacitane_nko == 1)
			{	
				/*vyprintuje upraveny text, a to tolko krat, kolko je ulozenych upravenych symbolov v poli upraveny_text. */
				for (m = 0; m < j; m++)
				{
					printf("%c", upraveny_text[m]);
					/*tento if skontroluje ci su vylacene uz vsetky prvky z upraveneho pola, a ak uz ano, vyprintuje znak noveho riadku */
					if(m == j - 1)
					{
						printf("\n");
					}
				}
			}
			else if (nacitane_ucko == 0 || nacitane_nko == 0)
			{
				printf("Nie je k dispozicii upravena sprava\n");
			}
		}
		
		
		/*treba premysliet ako urobit tuto cast, potrebujes si do jedneho pola ulozit vzdy dlzu daneho slova, a do druheho pola si uloz dane slovo (pridi ako na to) */
		else if (prikaz == 'd')
		{
			int k;
			scanf("%d", &k);
			
			
			printf("%d\n", k);
		}
		
		/*stlacenie pismena k ukonci while loop a skonci program (while loop sa uz viac nebude rovnat jednej, podmienka nebude splnena a opusti sa) */
		else if (prikaz == 'k')
		{
			k = 0;	
		}	
	}	

	return 0;	
}

/*toto je funkcia prikazn vykonava veci po stlaceni n-ka */
void prikazn (FILE *w, int prvy_text[0], int pocet_znakov, int *nacitane_nko)
{
	int i;
	
	/*kedze toto cele je obalene vo while k == 1 loope, moze sa stlacit nko viackrat a skusat citat viackrat zo suboru - to znaci ze druhe tretie, ... citanie by uz bol prejdeny subor - vzdy ho teda musim zavriet
	a znovu otvorit */
	/*v prvom rade zavrie predosly dokument z ktoreho sa citalo predtym na zistenie poctu znakov - a nasledne ho znovu otvoru na citanie */
	fclose(w);
	w = fopen("sifra.txt", "r");
	
	/*Vetvenie pre pripad kedy sa spravu nepodari nacitatkedze nevedelo precitat dany subor */
	if (w == NULL)
	{
		printf("Spravu sa nepodarilo nacitat\n");
		*nacitane_nko = 0;
	}
	else
	{
		/*for loop ktory mi do pola povodny_text(v tejto funkcii ako prvy_text) ulozi vsetky znaky zo suboru sifra.txt */
		for (i = 0; i < pocet_znakov; i++)
		{
			prvy_text[i] = getc(w);
		}
		*nacitane_nko = 1;
	}

}

