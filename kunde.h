#ifndef KUNDE_H
#define KUNDE_H


#define KUNDE_STINI_OK              0
#define KUNDE_STINI_FEHL            1

#define KUNDE_STEIN_OK              0
#define KUNDE_STEIN_FEHL_ALLG       1
#define KUNDE_STEIN_FEHL_EXISTIERT  2
#define KUNDE_STEIN_FEHL_VOLL       3

#define KUNDE_STLOE_OK              0
#define KUNDE_STLOE_FEHL_ALLG       1
#define KUNDE_STLOE_FEHL_EXNICHT    2


typedef struct
  {
   char strasse[41];
   int  hausNr;
   char ort[41];
  }
Anschrift_t;

typedef struct
  {
   char        name[41];
   Anschrift_t anschrift;
   char        telNr[21];
  }
Kunde_t;

int KundeStammInit(void);
void KundeStammExit(void);

void KundeAusgeben(const Kunde_t *kunde);
void KundeStammAusgeben(void);
int KundeStammEintragen(const Kunde_t *kunde);
int KundeStammLoeschen(const char *name);

#endif
