/* strutture definite per memorizza la relazione
   e l'insieme B */

typedef struct 
{
  char *elem_a; 	/* i.: elem. ins. A della rel. */
  char *elem_b;		/* i.: elem. ins. A della rel. */
} rel_t; 

typedef struct 
{
  char *elem; 		/* i.: elemento dell'insieme */
} insieme_t; 


/********************************************/
/* dichiarazione delle funzioni esportabili */
/********************************************/

int acquisizione_relazione(rel_t **pp);
void stampa_relazione(rel_t *pp, 
		      int dim);
int relazione_parziale(rel_t *pp, 
		       int dim);
int relazione_totale(rel_t *pp, 
			int dim);
int relazione_equivalenza(rel_t *pp, 
			  int dim);
int funzione_matematica(rel_t *pp, 
			int dim);

