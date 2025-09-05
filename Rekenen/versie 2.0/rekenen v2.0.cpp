#include <stdio.h>
#include <stdlib.h> 		/* om exit   te kennen */
#include <conio.h>		/* om kbhit  te kennen */
#include <time.h>			/* voor de random generator */
#include <dos.h>

char naam[64];
char buffer[64];
int grens;
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


void main(int argc, char * argv[])
{  char ch;
	int i;
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
      case '*':
      case '/': printf("\nProgramma gemaakt door Patrick Colleman.\n");
                printf("email: Patrick.Colleman@KHK.Be.\n");
      	       printf("Programma uitgetest door Steven Colleman.\n");
      		    printf("Versie 2.0.\n");
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
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
      	tafel=random(11);
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
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
      	tafel=random(10);
         tafel++;
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
   i=getch();
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
   tafel=leesgetal();
   if (terug) return;

   fouten=0;
   klok(0);
   for (i=0; i<110;i++)
   	{  maal=volgorde[i]/10;
      	tafel=volgorde[i]%10+1;			// tafel is nooit nul!!
      	printf("%3d.   %2d x %2d = ? ",i+1, maal, tafel);
         verifieer(maal*tafel);
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
   tafel=leesgetal();
   if (terug) return;

   fouten=0;
   klok(0);
   for (i=0; i<110;i++)
   	{  maal=volgorde[i]/10;
      	tafel=volgorde[i]%10+1;			// tafel is nooit nul!!
      	printf("%3d.   %2d : %2d = ? ",i+1, maal*tafel, tafel);
         verifieer(maal);
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
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
   	{  maal=random(10)+1;
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
   i=getch();  /* deze getch() dient om de leesbuffer leeg te maken */
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
   	{  maal=random(10)+1;
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

