#include <stdio.h>
#include "kunde.h"


static void bestaetigen(void);
static void einfuegen(const Kunde_t *kunde);
static void loeschen(const char *name);


void main(void)
  {
   Kunde_t neuerKunde={"Duck Trax",
                       {"Vogelweg", 3, "Entenhausen"},
                       "09999/991"};

   if (KundeStammInit()!=KUNDE_STINI_OK)
     {
      printf("Initialisierung des Kundenstamms fehlgeschlagen!\n");
      return;
     }

   KundeStammAusgeben();
   bestaetigen();

   einfuegen(&neuerKunde);
   einfuegen(&neuerKunde);
   loeschen("Duck Dagobert");
   loeschen("Duck Dagobert");

   KundeStammExit();
  }

static void bestaetigen(void)
  {
   printf("Druecken Sie Return, um fortzufahren...");
   getchar();
   printf("\n");
  }

static void einfuegen(const Kunde_t *kunde)
  {
   printf("Kunden \"%s\" einfuegen...\n\n", kunde->name);
   if (KundeStammEintragen(kunde)==KUNDE_STEIN_OK)
     {
      KundeStammAusgeben();
     }
   else
     {
      printf("Fehler!\n\n");
     }
   bestaetigen();
  }

static void loeschen(const char *name)
  {
   printf("Kunden \"%s\" loeschen...\n\n", name);
   if (KundeStammLoeschen(name)==KUNDE_STLOE_OK)
     {
      KundeStammAusgeben();
     }
   else
     {
      printf("Fehler!\n\n");
     }
   bestaetigen();
  }


