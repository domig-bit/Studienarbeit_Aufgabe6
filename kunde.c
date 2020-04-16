#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "kunde.h"
#include <unistd.h>

//Eintragen des Dateiortes der Kundendatenbank                  *BITTE VOR KOMPILIEREN AENDERN*

static char Dateiort[99] = "//Users//dominikgreiner//Desktop//test.txt";

FILE * kundendatenbank;

static Kunde_t StammInit[] =
                 {
                    {"Duck Donald",
                     {"Vogelweg", 3, "Entenhausen"},
                     "09999/991"},
                    {"Duck Daisy",
                     {"Vogelweg", 4, "Entenhausen"},
                     "09999/992"},
                    {"Duck Dagobert",
                     {"Kroesusstrasse", 1, "Dagoberts Palast"},
                     "09998/3"}
                 };


static void anschriftAusgeben(const Anschrift_t *anschrift);


void KundeAusgeben(const Kunde_t *kunde)
  {
   printf(" Name:    %s\n", kunde->name);
   anschriftAusgeben(&kunde->anschrift);
   printf(" Tel.Nr:  %s\n\n", kunde->telNr);
      

  }

static void anschriftAusgeben(const Anschrift_t *anschrift)
  {
   printf(" Strasse: %s %d\n", anschrift->strasse, anschrift->hausNr);
   printf(" Ort:     %s\n", anschrift->ort);
    
      
  }

void KundeStammAusgeben(void)
  {
   
      printf("\nKundenstamm: \n\n");
      
      long counter;
      long pos_end;
      long pos_start;
      
      fseek(kundendatenbank, 0, 0);
      pos_start = ftell(kundendatenbank);
        
      fseek(kundendatenbank, 0, 2);
      pos_end = ftell(kundendatenbank);
       
      counter = (pos_end - pos_start)/sizeof(Kunde_t);
      
      // Die Einträge in die Datei symbolisiert counter_input
      
      Kunde_t ausgabe_kundeninfo;
      
      for(int i = 0; i < counter;i++){
          
          fseek(kundendatenbank, i*sizeof(Kunde_t), SEEK_SET);
          fread(&ausgabe_kundeninfo, sizeof(Kunde_t), 1, kundendatenbank);
          KundeAusgeben(&ausgabe_kundeninfo);
      }
      
      
  }


int KundeStammInit(void)
  {
      
      if((kundendatenbank = fopen(Dateiort, "rb+")) == NULL){
          
          // Die Kundendatei muss erst erstellt werden und der Kundenstamm StammInit eingetragen werden
          kundendatenbank = fopen(Dateiort,"wb+");
          
          // Eintragen der StammInit Struktur
          
          for(int counter_init = 0; counter_init < sizeof(StammInit)/sizeof(Kunde_t); counter_init++){
              if(KundeStammEintragen(&StammInit[counter_init]) != KUNDE_STEIN_OK){
                  return (KUNDE_STINI_FEHL);
              }
          }
      }
      
      return(KUNDE_STINI_OK);
  }

void KundeStammExit(void)
  {
      fclose(kundendatenbank);
  }

int KundeStammEintragen(const Kunde_t *kunde)
  {
      // Zu ergänzen: Wenn die Datei voll ist, dann soll eine Fehlermeldung erfolgen!
      // Neuer Code:
      
      // Zunächst muss überprüft werden, wie viele Kunden bereits in der Datei stehen!!!
      
      
      long counter;
      long pos_end;
      long pos_begin;
      
      fseek(kundendatenbank, 0, 0);
      pos_begin = ftell(kundendatenbank);
        
      fseek(kundendatenbank, 0, 2);
      pos_end = ftell(kundendatenbank);
       
      counter = (pos_end - pos_begin)/sizeof(Kunde_t);
      
      // Die Anzahl der Kunden in der Datenbank sind als counter_input gespeichert
      
      //Im Folgenden wird überprüft, ob der Kunde bereits in der Datei enthalten ist
      
      Kunde_t check_valid;
      
      for(int i = 0; i <= counter;i++){
          fseek(kundendatenbank, i*sizeof(Kunde_t), SEEK_SET);
          fread(&check_valid, sizeof(Kunde_t), 1, kundendatenbank);
          
          if(strcmp(check_valid.name, kunde->name) == 0){
              return (KUNDE_STEIN_FEHL_EXISTIERT);
          }
          else{
              continue;
          }

      }
      
      // Der Eintrag ist also neu und kann in die Datei geschrieben werden
      
      fseek(kundendatenbank,counter*sizeof(Kunde_t),SEEK_SET);
      
      if (fwrite(kunde, sizeof(Kunde_t), 1, kundendatenbank) == 1){
          return(KUNDE_STEIN_OK);
      }
      else{
          return(KUNDE_STEIN_FEHL_ALLG);
      }
  }

int KundeStammLoeschen(const char *name)
  {
    long counter;
    long pos_end;
    long pos_begin;
    
    fseek(kundendatenbank, 0, 0);
    pos_begin = ftell(kundendatenbank);
      
    fseek(kundendatenbank, 0, 2);
    pos_end = ftell(kundendatenbank);
     
    counter = (pos_end - pos_begin)/sizeof(Kunde_t);
      
    // Im Folgenden wird die Stelle des zu löschenden Kunden initialisiert
      
      Kunde_t check_valid;
      int point_of_client = 0;
    
    for(int i = 0; i <= counter;i++){
        fseek(kundendatenbank, i*sizeof(Kunde_t), SEEK_SET);
        fread(&check_valid, sizeof(Kunde_t), 1, kundendatenbank);
        
        if((strcmp(check_valid.name, name)) == 0){
            point_of_client = i;
        }
        else{
            continue;
        }

    }
      if(point_of_client == 0){
          return(KUNDE_STLOE_FEHL_EXNICHT);
      }
      
      
      
      // 1. Im Folgenden wird die Strukturvariable von der darunterliegenden Strukturvariablen ersetzt
      // 2... Nun "rutschen" die nachfolgenden Strukturvariablen nach oben
      
      Kunde_t change_sequence;
      
      for (int i = point_of_client; i <= counter; i++){
      
      fseek(kundendatenbank, (i+1)*sizeof(Kunde_t), SEEK_SET);
      fread(&change_sequence, sizeof(Kunde_t), 1, kundendatenbank);
      
      fseek(kundendatenbank, i*sizeof(Kunde_t), SEEK_SET);
      fwrite(&change_sequence, sizeof(Kunde_t), 1, kundendatenbank);
      
      }
      
      
      //Zuletzt wird die unterste Strukturvariable, die doppelt steht, gelöscht
      
      rewind(kundendatenbank);
      
      if ((truncate(Dateiort,(counter-1)*sizeof(Kunde_t))) == 0){
          return (KUNDE_STLOE_OK);
      }
      else{
          return (KUNDE_STLOE_FEHL_ALLG);
      }
      
    }
