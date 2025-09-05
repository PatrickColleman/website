#include <stdio.h>
#include <stdlib.h> 		/* om exit   te kennen */
#include <conio.h>		/* om kbhit  te kennen */
#include <time.h>			/* voor de random generator */
#include <string.h>		/* om stringfuncties te kennen: */
								/* strcpy, strcmp, strcat, strlen, strstr, enz..  */
#include <dos.h>

// # define win9x 1
// zet bovenstaande lijn in commentaar voor winnt
// gebruik: #if defined(win9x)
//          ........
//          #endif


char naam[64];
char buffer[64];
int grens;
int kentafel[11]={1,1,1,1,1,1,1,1,1,1,1};
time_t starttijd;
int toontijd;
int fouten;
int terug;
int telallefouten;

void hoofding(void);
void klok(int);
int leesgetal(void);
void verifieer(int);
void leertafel(void);
void vraagxtafel(void);
void vermtafel(void);
void vraagdeeltafel(void);
void deeltafel(void);
void allemaaltafels(void);
void alledeeltafels(void);
void puntinmaal(void);
void puntindeel(void);
void telop(void);
void trekaf(void);
void invuloefening(void);
void welketafels(void);


void main(int argc, char * argv[])
{  char ch;
	int i, j, tekens;
   if (argc>4)
   	{  ch = 'a';
      	tekens = strlen(argv[4]);
      	for (i=0; i<11; i++) kentafel[i]=0;
      	for (i=0; i<tekens; i++)
         	{	j=argv[4][i]-'0';
            	if ((j>-1)&&(j<10)) { kentafel[j]=1; ch = 'b';}
            }
         kentafel[10]=kentafel[0];
         if (ch == 'a') for (i=0; i<11; i++) kentafel[i]=1;
      }
   if (argc>3) telallefouten=atoi(argv[3]);
   		else telallefouten=0;
   if (argc>2) grens=atoi(argv[2]);
   		else grens=100;
   if (grens < 10) grens=10;
   if (argc>1) toontijd=atoi(argv[1]);
   		else toontijd=0;
   /* standaard:
   		rekenen tot 100
         geen rekentijd laten zien na de oefeningen
         niet te streng zijn in het fouten tellen
         maal- en deeltafels tot 10
   */

	printf("Geef je naam in en druk op de <enter> toets: ");
   i=0;
   while (((ch=getchar())!='\n')&& (i<62)) naam[i++]=ch;
   naam[i]='\0';
   while (ch != '\n') ch=getchar();
   /* flush buffer als nog meer tekens zijn ingegeven */
   randomize();
   /* naam is gekend -- geef menu*/
   loop:
	hoofding();
   printf("menu:\n\n");
   printf("        0: verlaat programma\n\n");
   printf("        1: tafels van vermenigvuldigen en delen leren\n");
   printf("        2: opvragen van een vermenigvuldigingstafel\n");
   printf("        3: opvragen van willekeurige vermenigvuldigingstafels\n");
   printf("        4: opvragen volledige tafels van vermenigvuldigen\n");
   printf("        5: opvragen van een deeltafel\n");
   printf("        6: opvragen van willekeurige deeltafels\n");
   printf("        7: opvragen volledige deeltafels\n");
   printf("        8: invullen in vermenigvuldigingen\n");
   printf("        9: invullen in delingen\n");
   printf("        +: optellen tot %d\n",grens);
   printf("        -: aftrekken tot %d\n",grens);
   printf("        .: invullen van het ontbrekende cijfer (+ en -) tot %d\n",
   										grens);
   printf("\n\n");
   i=1;
   printf("Maak uw keuze (druk op gewenste toets) : ");
   do
    {	ch = getch();
      if ((ch>='0')&&(ch<='9')) i=0;
      if (ch == '/'+14) { i=0; ch = '/';}         // op keypad
      if (ch == '/') i=0;
      if (ch == '*') i=0;
      if (ch == '+') i=0;
      if (ch == '-') i=0;
      if (ch == '.'- 46) { i=0; ch = '.';}        // op keypad
      if (ch == '.') i=0;
      if (ch == 27) {ch = '#'; i=0; }
    }
   while (i);
   /* en verwerk dit menu */

   switch(ch)
   {	case '0': exit (0); break;
      case '1': leertafel(); break;
      case '2': vraagxtafel(); break;
      case '3': vermtafel(); break;
      case '4': allemaaltafels(); break;
      case '5': vraagdeeltafel(); break;
      case '6': deeltafel(); break;
      case '7': alledeeltafels(); break;
      case '8': puntinmaal(); break;
      case '9': puntindeel(); break;
      case '+': telop(); break;
      case '-': trekaf(); break;
      case '.': invuloefening();break;
      case '#': welketafels(); break;
      case '*':
      case '/': printf("\nProgramma gemaakt door Patrick Colleman.\n");
                printf("email: Patrick.Colleman@KHK.Be.\n");
      	       printf("Programma uitgetest door Steven Colleman.\n");
      		    printf("Versie 2.2.\n");
                printf("Druk op een toets om verder te gaan.\n");
                i=getch();
                break;
   }

   goto loop;
}

void hoofding(void)
{  clrscr();
   printf("Je bent: %s \n",naam);
   printf("\n\n");
}

void klok(int oefeningen)
{	//time_t tijd;
	int verschil;
   int minuten, seconden,
	tijd=time(NULL);
   if (oefeningen==0) starttijd=tijd;
   if (toontijd && (oefeningen>0))
   {	verschil=tijd-starttijd;
   	minuten=verschil/60;
      seconden=verschil-minuten*60;
   	printf("%s, je gebruikte voor deze %d oefeningen: %d minuten en %d seconden.\n",
      			naam, oefeningen, minuten, seconden);
      printf("Dit is gemiddeld %6.2f seconden per oefening.\n",
      			((float)verschil/(float)oefeningen));
   }
}

int leesgetal(void)
{  int i, ch;
	terug=0;
	i=0;
   while (((ch=getchar())!='\n')&& (i<62))
   		{	buffer[i++]=ch;
         	if (ch == '/') terug=1;
         }
   buffer[i]='\0';
   while (ch != '\n') ch=getchar();
   ch=atoi(buffer);
   return ch;
}

void verifieer(int juist)
{  int antw;
	// scanf("%d",&antw);
	antw=leesgetal();
   if (antw != juist)
   	{ printf("    fout! tweede poging: ");
        fouten++;
        // scanf("%d",&antw);
        antw=leesgetal();
        if (antw != juist)
        		{	printf("    fout! derde poging : ");
               if (telallefouten) fouten++;
               // scanf("%d",&antw);
               antw=leesgetal();
               if (antw != juist)
                 { if (telallefouten) fouten++;
                   printf("    Het juiste antwoord was: %3d\n",juist);
                 }
            }
        }
}


void leertafel(void)
{	int i, tafel;
   hoofding();
   tafel=-1;
   printf("Welke tafel wil je leren of bekijken? (0..11) ");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   while ((tafel<0)||(tafel>11))
   	{ 	// scanf("%d",&tafel);
      	tafel=leesgetal();
         if (terug) return;
         if ((tafel<0)||(tafel>11))
         	{	printf("Foutieve waarde.  Geef een juiste!\n");
         		printf("Welke tafel wil je leren of bekijken? (0..11) ");
            }
      }
   printf("Je koos voor de tafel van: %2d \n",tafel);
   if (tafel == 0)
      for (i=0;i<11;i++) printf("%2d x %2d = %3d \n",i, tafel, i*tafel);
		else
   		for (i=0;i<11;i++)
   		{	printf("%2d x %2d = %3d",i, tafel, i*tafel);
         	printf("    en %3d : %2d = %2d \n", i*tafel, tafel, i);
   		}
   printf("Druk op een toets om verder te gaan");
   i=getch();
}

void vraagxtafel(void)
{  int i, tafel, used[11], volgorde[11];
   hoofding();
   tafel=-1;
   printf("Welke vermenigvuldigingstafel wil je overhoren? (0..11) ");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   while ((tafel<0)||(tafel>11))
   	{ 	// scanf("%d",&tafel);
      	tafel=leesgetal();
         if (terug) return;
         if ((tafel<0)||(tafel>11))
         	{	printf("Foutieve waarde.  Geef een juiste!\n");
         		printf("Welke vermenigvuldigingstafel wil je overhoren? (0..11) ");
            }
      }
   printf("Je koos voor de tafel van: %2d \n",tafel);
   for (i=0;i<11;i++) used[i]=0;
   for (i=0;i<11;i++)
   	{  nieuw:
      	fouten=random(11);
         if (used[fouten]) goto nieuw;
         used[fouten]=1;
         volgorde[i]=fouten;
      }
   fouten=0;
   klok(0);
   for (i=0; i<11;i++)
   	{	printf("%2d.   %2d x %2d = ? ",i+1, volgorde[i], tafel);
         verifieer(volgorde[i]*tafel);
      }
   klok(11);
	if (fouten == 0) printf("Uitstekend %s, je maakte geen fouten!\n", naam);
   if (fouten == 1) printf("Zeer goed %s, je maakte slechts 1 fout!\n",naam);
   if (fouten == 2) printf("Goed %s, je maakte 2 foutjes.\n",naam);
   if (fouten == 3) printf("%s, je maakte 3 fouten.  Beter opletten!\n",naam);
   if (fouten >3) printf("%s, je maakte %d fouten.  Studeer de tafel opnieuw.\n",naam, fouten);
   printf("Druk op een toets om verder te gaan");
   i=getch();
}

void vermtafel(void)
{  int i, tafel, maal, oef;
   hoofding();
   tafel=-1;
	printf("Hoeveel vermenigvuldigingen wil je overhoren? (5..50) ");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   while ((tafel<5)||(tafel>50))
   	{ 	// scanf("%d",&tafel);
      	tafel=leesgetal();
         if (terug) return;
         if ((tafel<5)||(tafel>50))
         	{	printf("Foutieve waarde.  Geef een juiste!\n");
         		printf("Hoeveel vermenigvuldigingen wil je overhoren? (5..50) ");
            }
      }
   printf("Je koos voor %2d oefeningen.\n",tafel);

   oef=tafel;
   fouten=0;
   klok(0);
   for (i=0; i<oef;i++)
   	{  maal=random(11);
      	terug:
      	tafel=random(11);
         if (!kentafel[tafel]) goto terug;
      	printf("%2d.   %2d x %2d = ? ", i+1, maal, tafel);
         verifieer(maal*tafel);
      }
   klok(oef);
	if (fouten == 0) printf("Uitstekend %s, je maakte geen fouten!\n", naam);
   else if (fouten == 1) printf("Zeer goed %s, je maakte slechts 1 fout!\n",naam);
   else if (fouten == 2) printf("Goed %s, je maakte 2 foutjes.\n",naam);
   else printf("%s, je maakte %d fouten op %d oefeningen.\n",naam, fouten, oef);
   printf("Druk op een toets om verder te gaan");
   i=getch();
}

void vraagdeeltafel(void)
{  int i, tafel, used[11], volgorde[11];
   hoofding();
   tafel=-1;
   printf("Welke deeltafel wil je overhoren? (1..11) ");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   while ((tafel<1)||(tafel>11))
   	{ 	// scanf("%d",&tafel);
      	tafel=leesgetal();
         if (terug) return;
         if ((tafel<1)||(tafel>11))
         	{	printf("Foutieve waarde.  Geef een juiste!\n");
         		printf("Welke deeltafel wil je overhoren? (1..11) ");
            }
      }
   printf("Je koos voor de tafel van: %2d \n",tafel);
   for (i=0;i<11;i++) used[i]=0;
   for (i=0;i<11;i++)
   	{  nieuw:
      	fouten=random(11);
         if (used[fouten]) goto nieuw;
         used[fouten]=1;
         volgorde[i]=fouten;
      }
   fouten=0;
   klok(0);
   for (i=0; i<11;i++)
   	{	printf("%2d.   %2d : %2d = ? ", i+1, tafel*volgorde[i], tafel);
      	verifieer(volgorde[i]);
      }
   klok(11);
	if (fouten == 0) printf("Uitstekend %s, je maakte geen fouten!\n", naam);
   if (fouten == 1) printf("Zeer goed %s, je maakte slechts 1 fout!\n",naam);
   if (fouten == 2) printf("Goed %s, je maakte 2 foutjes.\n",naam);
   if (fouten == 3) printf("%s, je maakte 3 fouten.  Beter opletten!\n",naam);
   if (fouten >3) printf("%s, je maakte %d fouten.  Studeer de tafel opnieuw.\n",naam, fouten);
   printf("Druk op een toets om verder te gaan");
   i=getch();
}

void deeltafel(void)
{  int i, tafel, maal, oef;
   hoofding();
	tafel=-1;
	printf("Hoeveel delingen wil je overhoren? (5..50) ");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   while ((tafel<5)||(tafel>50))
   	{ 	// scanf("%d",&tafel);
      	tafel=leesgetal();
         if (terug) return;
         if ((tafel<5)||(tafel>50))
         	{	printf("Foutieve waarde.  Geef een juiste!\n");
         		printf("Hoeveel delingen wil je overhoren? (5..50) ");
            }
      }
   printf("Je koos voor %2d oefeningen.\n",tafel);

   oef=tafel;
   fouten=0;
   klok(0);
   for (i=0; i<oef;i++)
   	{  maal=random(11);
      	terug:
         tafel=random(10);
         tafel++;
         if (!kentafel[tafel]) goto terug;
			printf("%2d.   %2d : %2d = ? ", i+1, tafel*maal, tafel);
         verifieer(maal);
      }
   klok(oef);
	if (fouten == 0) printf("Uitstekend %s, je maakte geen fouten!\n", naam);
   else if (fouten == 1) printf("Zeer goed %s, je maakte slechts 1 fout!\n",naam);
   else if (fouten == 2) printf("Goed %s, je maakte 2 foutjes.\n",naam);
   else printf("%s, je maakte %d fouten op %d oefeningen.\n",naam, fouten, oef);
   printf("Druk op een toets om verder te gaan");
   i=getch();
}

void telop(void)
{	int i, tafel, maal, oef;
   hoofding();
   tafel=-1;
	printf("Hoeveel sommen wil je overhoren? (5..50) ");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   while ((tafel<5)||(tafel>50))
   	{ 	// scanf("%d",&tafel);
      	tafel=leesgetal();
         if (terug) return;
         if ((tafel<5)||(tafel>50))
         	{	printf("Foutieve waarde.  Geef een juiste!\n");
         		printf("Hoeveel sommen wil je overhoren? (5..50) ");
            }
      }
   printf("Je koos voor %2d oefeningen.\n",tafel);

   oef=tafel;
   fouten=0;
   klok(0);
   for (i=0; i<oef;i++)
   	{  maal=random(grens+1);
      	tafel=random(grens-maal+1);
      	printf("%2d.   %3d + %3d = ? ", i+1, maal, tafel);
         verifieer(tafel+maal);
      }
   klok(oef);
	if (fouten == 0) printf("Uitstekend %s, je maakte geen fouten!\n", naam);
   else if (fouten == 1) printf("Zeer goed %s, je maakte slechts 1 fout!\n",naam);
   else if (fouten == 2) printf("Goed %s, je maakte 2 foutjes.\n",naam);
   else printf("%s, je maakte %d fouten op %d oefeningen.\n",naam, fouten, oef);
   printf("Druk op een toets om verder te gaan");
   i=getch();
}

void trekaf(void)
{	int i, tafel, maal, oef;
   hoofding();
   tafel=-1;
	printf("Hoeveel verschillen wil je overhoren? (5..50) ");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   while ((tafel<5)||(tafel>50))
   	{ 	// scanf("%d",&tafel);
      	tafel=leesgetal();
         if (terug) return;
         if ((tafel<5)||(tafel>50))
         	{	printf("Foutieve waarde.  Geef een juiste!\n");
         		printf("Hoeveel verschillen wil je overhoren? (5..50) ");
            }
      }
   printf("Je koos voor %2d oefeningen.\n",tafel);

   oef=tafel;
   fouten=0;
   klok(0);
   for (i=0; i<oef;i++)
   	{  maal=random(grens+1);
      	tafel=random(maal+1);
      	printf("%2d.   %3d - %3d = ? ", i+1, maal, tafel);
         verifieer(maal-tafel);
      }
   klok(oef);
	if (fouten == 0) printf("Uitstekend %s, je maakte geen fouten!\n", naam);
   else if (fouten == 1) printf("Zeer goed %s, je maakte slechts 1 fout!\n",naam);
   else if (fouten == 2) printf("Goed %s, je maakte 2 foutjes.\n",naam);
   else printf("%s, je maakte %d fouten op %d oefeningen.\n",naam, fouten, oef);
   printf("Druk op een toets om verder te gaan");
   i=getch();
}


void invuloefening(void)
{	int i, tafel, maal, oef, keuze;
   hoofding();
   tafel=-1;
	printf("Hoeveel invuloefeningen wil je oplossen? (5..50) ");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
   i=getch();
#endif
   while ((tafel<5)||(tafel>50))
   	{ 	// scanf("%d",&tafel);
      	tafel=leesgetal();
         if (terug) return;
         if ((tafel<5)||(tafel>50))
         	{	printf("Foutieve waarde.  Geef een juiste!\n");
         		printf("Hoeveel invuloefeningen wil je oplossen? (5..50) ");
            }
      }
   printf("Je koos voor %2d oefeningen.\n",tafel);
   printf("Vul na het ? het cijfer in dat het . teken vervangt.\n");

   oef=tafel;
   fouten=0;
   klok(0);
   for (i=0; i<oef;i++)
   	{  maal=random(grens+1);
      	tafel=random(grens+1);
         if ( maal> tafel)
         {	keuze=tafel;
         	tafel=maal;
            maal=keuze;
         }
         keuze=random(4);
         switch(keuze)
         {	case 0:  printf("%2d.    .  + %3d = %3d  ? ", i+1, maal, tafel);
                     verifieer (tafel-maal);
                     break;
         	case 1:  printf("%2d.   %3d +  .  = %3d  ? ", i+1, maal, tafel);
                     verifieer (tafel-maal);
                     break;
            case 2:  printf("%2d.   %3d -  .  = %3d  ? ", i+1, tafel, maal);
                     verifieer (tafel-maal);
                     break;
            case 3:  tafel=random(grens+1-maal);
            			printf("%2d.    .  - %3d = %3d  ? ", i+1, maal, tafel);
                     verifieer (tafel+maal);
                     break;
         }
      }
   klok(oef);
	if (fouten == 0) printf("Uitstekend %s, je maakte geen fouten!\n", naam);
   else if (fouten == 1) printf("Zeer goed %s, je maakte slechts 1 fout!\n",naam);
   else if (fouten == 2) printf("Goed %s, je maakte 2 foutjes.\n",naam);
   else printf("%s, je maakte %d fouten op %d oefeningen.\n",naam, fouten, oef);
   printf("Druk op een toets om verder te gaan");
   i=getch();
}


void allemaaltafels(void)
{  int i, maal, tafel, used[110], volgorde[110];
   hoofding();
   // printf("Start opstellen volgorde van de vragen.\n");
   for (i=0;i<110;i++) used[i]=0;
   for (i=0;i<110;i++)
   	{  nieuw:
      	maal=random(110);
         if (used[maal]) goto nieuw;
         used[maal]=1;
         volgorde[i]=maal;
      }
   // printf("Volgorde is gekozen.\n");

   printf("Opvragen van alle vermenigvuldigingtafels in willekeurige volgorde.\n");
   printf("Geef een willekeurig getal om te starten.  / om nog te stoppen. \n");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   tafel=leesgetal();
   if (terug) return;

   fouten=0;
   klok(0);
   for (i=0; i<110;i++)
   	{  maal=volgorde[i]/10;
      	tafel=volgorde[i]%10+1;			// tafel is nooit nul!!
         if (!kentafel[tafel])
         	printf("%3d.   %2d x %2d = %d\n",i+1, maal, tafel,maal*tafel);
      	 else
          	{ 	printf("%3d.   %2d x %2d = ? ",i+1, maal, tafel);
         		verifieer(maal*tafel);
            }
      }
   klok(110);
	if (fouten == 0) printf("Uitstekend %s, je maakte geen fouten!\n", naam);
   if (fouten == 1) printf("Zeer goed %s, je maakte slechts 1 fout!\n",naam);
   if (fouten == 2) printf("Goed %s, je maakte 2 foutjes.\n",naam);
   if (fouten >2) printf("%s, je maakte %d fouten.\n",naam, fouten);
   printf("Druk op een toets om verder te gaan");
   i=getch();
}


void alledeeltafels(void)
{  int i, maal, tafel, used[110], volgorde[110];
   hoofding();
   // printf("Start opstellen volgorde van de vragen.\n");
   for (i=0;i<110;i++) used[i]=0;
   for (i=0;i<110;i++)
   	{  nieuw:
      	maal=random(110);
         if (used[maal]) goto nieuw;
         used[maal]=1;
         volgorde[i]=maal;
      }
   // printf("Volgorde is gekozen.\n");

   printf("Opvragen van alle deeltafels in willekeurige volgorde.\n");
   printf("Geef een willekeurig getal om te starten.  / om nog te stoppen. \n");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   tafel=leesgetal();
   if (terug) return;

   fouten=0;
   klok(0);
   for (i=0; i<110;i++)
   	{  maal=volgorde[i]/10;
      	tafel=volgorde[i]%10+1;			// tafel is nooit nul!!
         if (!kentafel[tafel])
         	printf("%3d.   %2d : %2d = %d\n",i+1, maal*tafel, tafel, maal);
           else
      			{	printf("%3d.   %2d : %2d = ? ",i+1, maal*tafel, tafel);
         			verifieer(maal);
               }
      }
   klok(110);
	if (fouten == 0) printf("Uitstekend %s, je maakte geen fouten!\n", naam);
   if (fouten == 1) printf("Zeer goed %s, je maakte slechts 1 fout!\n",naam);
   if (fouten == 2) printf("Goed %s, je maakte 2 foutjes.\n",naam);
   if (fouten >2) printf("%s, je maakte %d fouten.\n",naam, fouten);
   printf("Druk op een toets om verder te gaan");
   i=getch();
}


void puntinmaal(void)
{	int i, tafel, maal, oef, keuze;
   hoofding();
   tafel=-1;
	printf("Hoeveel x invuloefeningen wil je oplossen? (5..50) ");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   while ((tafel<5)||(tafel>50))
   	{ 	// scanf("%d",&tafel);
      	tafel=leesgetal();
         if (terug) return;
         if ((tafel<5)||(tafel>50))
         	{	printf("Foutieve waarde.  Geef een juiste!\n");
         		printf("Hoeveel x invuloefeningen wil je oplossen? (5..50) ");
            }
      }
   printf("Je koos voor %2d oefeningen.\n",tafel);
   printf("Vul na het ? het cijfer in dat het . teken vervangt.\n");

   oef=tafel;
   fouten=0;
   klok(0);
   for (i=0; i<oef;i++)
   	{  terug:
      	maal=random(10)+1;
         if (!kentafel[maal]) goto terug;
      	tafel=random(10)+1;
         if (maal%2)
         	printf("%2d.    .  * %3d = %3d  ? ", i+1, maal, tafel*maal);
         else
         	printf("%2d.   %3d *  .  = %3d  ? ", i+1, maal, tafel*maal);
         verifieer (tafel);
      }
   klok(oef);
	if (fouten == 0) printf("Uitstekend %s, je maakte geen fouten!\n", naam);
   else if (fouten == 1) printf("Zeer goed %s, je maakte slechts 1 fout!\n",naam);
   else if (fouten == 2) printf("Goed %s, je maakte 2 foutjes.\n",naam);
   else printf("%s, je maakte %d fouten op %d oefeningen.\n",naam, fouten, oef);
   printf("Druk op een toets om verder te gaan");
   i=getch();
}


void puntindeel(void)
{	int i, tafel, maal, oef, keuze;
   hoofding();
   tafel=-1;
	printf("Hoeveel : invuloefeningen wil je oplossen? (5..50) ");
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   while ((tafel<5)||(tafel>50))
   	{ 	// scanf("%d",&tafel);
      	tafel=leesgetal();
         if (terug) return;
         if ((tafel<5)||(tafel>50))
         	{	printf("Foutieve waarde.  Geef een juiste!\n");
         		printf("Hoeveel : invuloefeningen wil je oplossen? (5..50) ");
            }
      }
   printf("Je koos voor %2d oefeningen.\n",tafel);
   printf("Vul na het ? het cijfer in dat het . teken vervangt.\n");

   oef=tafel;
   fouten=0;
   klok(0);
   for (i=0; i<oef;i++)
   	{  terug:
      	maal=random(10)+1;
         if (!kentafel[maal]) goto terug;
      	tafel=random(10)+1;
         if (maal%2)
         	{	printf("%2d.    .  : %3d = %3d  ? ", i+1, maal, tafel);
            	verifieer(tafel*maal);
            }
         else
         	{	printf("%2d.   %3d :  .  = %3d  ? ", i+1, tafel*maal, maal);
         		verifieer (tafel);
            }
      }
   klok(oef);
	if (fouten == 0) printf("Uitstekend %s, je maakte geen fouten!\n", naam);
   else if (fouten == 1) printf("Zeer goed %s, je maakte slechts 1 fout!\n",naam);
   else if (fouten == 2) printf("Goed %s, je maakte 2 foutjes.\n",naam);
   else printf("%s, je maakte %d fouten op %d oefeningen.\n",naam, fouten, oef);
   printf("Druk op een toets om verder te gaan");
   i=getch();
}


void welketafels(void)
{  int i;
	char ch;
   hoofding();
#if defined(win9x)
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
#endif
   ch = 'a';
	printf("Vul voor elke tafel in of deze gekend is of niet:\n");
	printf("0     voor een niet gekende tafel\n");
   printf("1     voor een gekende tafel\n");
   for (i=1; i<11; i++)
   	{ 	printf ("is tafel %2d gekend? (%1d)  : ", i, kentafel[i]);
         kentafel[i]=leesgetal();
         if (kentafel[i]) ch = 'b';
      }
   if (ch == 'a') for (i=0; i<11; i++) kentafel[i]=1;
}

