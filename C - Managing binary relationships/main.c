/********************************************/
/* inclusione delle librerie standard del c */
/********************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/************************************/
/* inclusione della libreria creata */
/************************************/

#include "libreria.h"


/***********************************/
/* definizione della funzione main */
/***********************************/

int main(void)
{
  /* dichiarazione delle variabili locali alla funzione */
  int dim = 0;			/* i.: dimensione struttura */

  /* inizializzazione struttura */	
  rel_t *pp = NULL;
  
  /* chiamata alla funzione che si occupa
     di acquisire e validare la relazione */
  dim = acquisizione_relazione(&pp);
	
  /* chiamata alla funzione che stampa 
     a video la relazione */
  stampa_relazione(pp, 
		   dim);
  
  /* chiamata alla funzione che controlla
     se la relazione è di tipo parziale */
  relazione_parziale(pp, 
		     dim); 

  /* chiamata alla funzione che controlla
     se la relazione è di tipo totale */	
  relazione_totale(pp, 
		   dim);
	  
  /* chiamata alla funzione che controlla
     se la relazione è di tipo d'equivalenza */
  relazione_equivalenza(pp, 
			dim); 
	
  /* chiamata alla funzione che controlla
     se la relazione è una funzione matematica */
  funzione_matematica(pp, 
		      dim); 

  return (0);
}
