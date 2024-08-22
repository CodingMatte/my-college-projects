
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


/********************************/
/* dichiarazione delle funzioni */
/********************************/

int valida_intero(const char *intero_stringa, 	
                  int *intero_validato);     
int controlla_carattere(const char carattere);
int controlla_punteggiatura(const char *relazione,
			    int lunghezza,
		    	    int *conta_coppie);
int cerca_coppia(rel_t *pp, 
		 int dim, 
		 char* a, 
		 char* b);
int riflessiva(rel_t *pp, 
	       int dim);
int antisimmetrica(rel_t *pp, 
		   int dim);
int simmetrica(rel_t *pp, 
	       int dim);
int transitiva(rel_t *pp, 
	       int dim);
int verifica_transitiva(rel_t *pp, 
			int dim, 
			char* a, 
			char* b,
			int* coppie_b);
int totale(rel_t *pp, 
	   int dim);
int confrontabile(rel_t *pp, 
		  int dim, 
	    	  char* x, 
		  char* y);
int carica_insieme(insieme_t **insieme);
int conta_accoppiamenti_a(rel_t *pp, 
			  int dim, 
			  char* a);
int conta_accoppiamenti_b(rel_t *pp, 
			  int dim, 
			  char* b);


/******************************/
/* definizione delle funzioni */
/******************************/

/* definizione della funzione che valida 
   un intero, restituirà 1 se è errato o 
   0 se è corretto */
int valida_intero(const char *intero_stringa, 	/* i.: stringa intero da validare */
                  int *intero_validato)		/* o.: intero validato */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i = 0,					/* l.: indice */
      lun;					/* l.: lunghezza stringa intero */
 
  int errore = 0;				/* o.: errore che rest. la fun. */

  lun = strlen(intero_stringa);

  /* controlla che lun non sia più grande di 5 */
  if (lun >= 6)
    errore = 1;
  else 
  {
    /* controlla che nella prima posizione non ci 
       sia uno 0 */
    if (intero_stringa[i] != '0')
    {
      /* controlla che in ogni posizione dell'array ci 
         sia una cifra da 0 a 9 */ 
      while (i < lun) 
      {
        if (errore == 1)
          i = lun;
        else
        {  
          /* se l'elemento nella posizione i è diverso da un 
             numero da 0 a 9 assegna 1 a "errore" */
          if (intero_stringa[i] != '0' &&
              intero_stringa[i] != '1' &&
  	      intero_stringa[i] != '2' &&
              intero_stringa[i] != '3' &&
	      intero_stringa[i] != '4' &&
              intero_stringa[i] != '5' &&
	      intero_stringa[i] != '6' &&
              intero_stringa[i] != '7' &&
	      intero_stringa[i] != '8' &&
              intero_stringa[i] != '9')
            errore = 1;
        }

        i ++;
      }
    }
    else 
      errore = 1;
  }

  /* se non ha trovato nessun errore usa la funzione atoi 
     per convertire la stringa in intero e assegnarlo a 
     "intero_validato" */
  if (errore != 1)
    *intero_validato = atoi(intero_stringa);
  
  return errore;
}

/* definizione della funzione che controlla se il carattere 
   è corretto, restituisce '1' se c'è un errore altrimenti '0' */
int controlla_carattere(const char carattere)   /* i.: carattere da controllare */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i;					/* l.: indice array */

  char dizionario[] = {'a', 'b', 'c',		/* l.: dizion. car. consentiti */
		       'd', 'e', 'f',
		       'g', 'h', 'i',
		       'j', 'k', 'l',
		       'm', 'n', 'o',
		       'p', 'q', 'r',
		       's', 't', 'u',
		       'v', 'w', 'x',
		       'y', 'z', '0',
		       '1', '2', '3',
		       '4', '5', '6',
		       '7', '8', '9'};	
		
  int lun = 36;					/* l.: car. dizionario */
  int errore = 1;				/* l.: esito funzione */
  
  /* ciclo che confronta il carattere con l'array dizionario 
     e se trova una ricorrenza assegna 0 a errore */	
  for (i = 0; 
       i < lun && errore != 0;
       i++)	
  {
    if (carattere == dizionario[i])	   
      errore = 0;
  }

  /* ritorna l'esito della funzione */	  
  return errore;
}


/* definizione della funzione che valida la 
   punteggiatura della relazione, ritorna 1 
   se c'è un errore, altrimenti 0; tornerà,
   di conseguenza anche il numero delle coppie
   di elementi prensenti nella relazione */
int controlla_punteggiatura(const char *relazione,  /* i.: relazione da validare */
		            int lunghezza, 	    /* l.: lunghezza relazione */
			    int *dim)		    /* l./o: dim. per array */
{
  /* dichiarazione delle variabili locali alla funzione */
  int errore = 0,				/* l.: errore */
      i = 0,					/* l.: indice */
      j = 0,					/* l.: indice */
      k = 0,					/* l.: indice */
      numero_virgole = 0,			/* l.: num. virg. nella rel. */
      numero_chiuse = 0,			/* l.: num. par. chiuse nella rel. */
      conta_coppie = 0;				/* l./o: num. coppie rel. */
   		
  /* controlla che nella prima posizione 
     e nell'ultima ci siano le parentesi
     '{' '}'*/
  if (relazione[lunghezza - 1] != '}' ||
      relazione[0] != '{') 
     errore = 1;

  /* controlla il contenuto della relazione usando come 
     punti di riferimento la punteggiatura: '(', ',' ')' */
  if (errore != 1)
  {
    for (i = 1;
	 i < lunghezza - 3 && errore == 0;
	 i = k + 1)
    {
      /* controlla la '(' */
      if (relazione[i] != '(')
         errore = 1;
      else 
      { 
        /* trova la prossima ',' */
        for (j = i + 2, errore = 1;
	     j < lunghezza - 3 && errore == 1;
	     j++)
        {
          if (relazione[j] == ',')
             errore = 0;           
        }

        /* trova la prossima ')' e controlla la ','
	   successiva o la terminazione della relazione */
        if (errore != 1) 
        {
          for (k = j + 1, errore = 1;
	       k < lunghezza - 1 && errore == 1;
	       k++)
          {
            if (relazione[k] == ')')
            {
              if ((lunghezza - 2) == k ||
		  relazione[k + 1] == ',')
              {
                conta_coppie++;
                errore = 0;
              }           						
	    }
          }
        }
      }    
    }
  }

  /* conta le ',', se non ci sono il giusto numero di ',' c'è un errore */
  for (i = 2;
       i < lunghezza - 1;
       i++)
  {
    if (relazione[i] == ',')
       numero_virgole++;
  } 
  if (numero_virgole != (conta_coppie * 2 - 1))
     errore = 1;
    
  /* esegue la stessa operazione con le parentesi tonde chiuse */
  if (errore != 1)
  {
    for (i = 2;
	 i < lunghezza - 1;
         i++)
    {
      if (relazione[i] == ')')
	 numero_chiuse++;
    }
	
    if (numero_chiuse != conta_coppie)
       errore = 1;
  }

  /* assegna a 'dim' il numero di coppie presenti 
     nella relazione */  
  *dim = conta_coppie;

  return errore;
}

/* definizione delle funzione che acquisisce una relazione,
   la valida, e la memorizza in una struttura apposita */
int acquisizione_relazione(rel_t **puntatore)	/* i.: relazione da validare */
{
  /* dichiarazioni delle variabili locali alla funzione */
  int i,				/* l.: indice */
      j,				/* l.: indice */
      k;				/* l.: indice */

  char intero_validare[6];		/* l.: intero da validare */

  int l_relazione;			/* i.: lunghezza relazione */
  char *relazione;			/* i.: relazione */
  
  int errore = 0,			/* l.: controllo errore */
      virgole,				/* l.: contatore virgole */
      inizio,				/* l.: indice inizio controllo */
      fine;				/* l.: indice fine controllo */
      
  int *a,				/* l.: indici elem. insieme A */
      *b; 				/* l.: indici elem. insieme B */
  int dim,				/* l.: dim. array 'a' e 'b' */
      l_mas_a,				/* l.: lungh. massima elem. a */
      l_mas_b = 0;			/* l.: lungh. massima elem. b */
      
  rel_t *pp; /* puntatore a rel_t di appoggio (poi verrà copiato
	        dentro *puntatore) */
  
  char *temp,  				/* l.: stringa temporanea */
       *temp_confr;  			/* l.: stringa temporanea */
  
  int ris = 0;				/* l.: esito confronto */

   
  /* acquisizione */
  do
  {
    do
    {
      printf("\n\nQuanto è lunga la relazione?\n"
             "Si consideri anche la punteggiatura:\n"
             "Es. la relazione R = {(ab,b),(2b,a)} è lunga 15 caratteri.\n\n"
	     "N.B. il numero da inserire deve essere maggiore di 7,\n"
	     "     in quanto, la relazione più corta è lunga 7 caratteri.\n"
	     "N.B. la relazione, per semplicità, va inserita senza spazi.\n");
      scanf("%s",
  	    intero_validare);
      /* controlla che sia stato inserito un intero e,
         se necessario, stampa il relativo errore */
      errore = valida_intero(intero_validare,
			     &l_relazione);
      /* controlla che il numero inserito sia maggiore
         di 7, in quanto, la relazione più piccola è 
         lunga 7 caratteri */
      if (l_relazione < 7)
         errore = 1;

      if (errore != 0)
      {
        printf("\nErrore: è stato inserito un numero non valido.\n\n");
      }
    } while (errore != 0);

    /* allocazione relazione */
    relazione = (char *) calloc(l_relazione + 1, 
			        sizeof(char));

  
    printf("\n\nInserire la relazione lunga %d caratteri.\n"
           "Una relazione tra l'insieme A e l'insieme B\n"
	   "è un sottoinsieme di A x B.\n"
	   "Es. {(a1,b1),(a2,b2),(a3,b3)}\n\n"
           "N.B. Gli elementi delle coppie possono essere\n"
           "     numeri interi positivi e/o lettere minuscole.\n"
	   "N.B. La relazione, per semplicità, va inserita senza spazi.\n"
	   "N.B. Non sono ammesse coppie uguali.\n",
           l_relazione);

    /* acquisizione relazione */    
    scanf("%s",
   	  relazione);

    /* scrive '\0' alla fine dell'array */
    relazione[l_relazione] = '\0'; 
  						
    /* validazione punteggiatura relazione */
    errore = controlla_punteggiatura (relazione,
				      l_relazione,
				      &dim);
		
    /* "creazione" array 'a' e 'b' */
    if (errore != 1)
    { 
      /* allocazione a in base al numero delle coppie */
      a = (int *) calloc(dim, 
		         sizeof(int)); 
      /* allocazione b in base al numero delle coppie - 1 */
      b = (int *) calloc(dim, 
		         sizeof(int)); 
   
      /* scansiona l'array segnando le posizioni delle ',' 
         e delle ')' */
      for (i = 2, j = 0, virgole = 0;
	   i < l_relazione - 1;
           i++)
      {      
        if (relazione[i] == ',')
        {
          virgole++;
	  /* segna solo le virgole tra 
             due parentesi (occorrenze dispari) */
          if (virgole % 2 == 1)
          {
            a[j] = i;
 	    j++;
          }
        }
        /* segna le parentesi chiuse nell'array B, 
  	   nella stessa posizione in cui ha salvato 
	   la virgola interna nell'array A */
        else if (relazione [i] == ')')
           b[j - 1] = i;     
      }
    }

    if (errore != 1)
    {  
      /* controlla che gli elementi della relazione siano giusti */
      for (i = 0;
           i < dim && errore != 1;
           i++)
      {
        /* controlla gli elementi A */
        if (i == 0)
        {
          inizio = 2;
          fine = a[i];
          do
          {
            /* controlla ogni singolo carattere */
            errore = controlla_carattere(relazione[inizio]);
	    inizio++;
          } while (inizio < fine && errore != 1);
        }
        else 
        {				
          inizio = b[i - 1] + 3;
          fine = a[i];
          do
          {		
            /* controlla ogni singolo carattere */
            errore = controlla_carattere(relazione[inizio]);
	    inizio++;
          } while (inizio < fine && errore != 1);
        }

        /* controlla gli elementi B */
        if (errore != 1)
        {				
          inizio = a[i] + 1;
	  fine = b[i];
	  do
          {
	    /* controlla ogni singolo carattere */
            errore = controlla_carattere(relazione[inizio]);
	    inizio++;
	  } while (inizio < fine && errore != 1);
        }
      }
    }

    /* stampa messaggio di errore */
    if (errore == 1)
    {
      printf("\nErrore: la relazione inserita non è corretta.\n\n");
    }
 
    /* creazione struttura */
    if (errore != 1)
    {
      /* conta la lunghezza massima degli elem. ins. A */
      for (l_mas_a = a[0] - 2, i = 1;
	   i < dim;
	   i++)
      {
        if (l_mas_a < (a[i] - b[i - 1] - 3))
           l_mas_a = a[i] - b[i - 1] - 3;
      }

      /* conta la lunghezza massima degli elem. ins. B */
      for (i = 0;
	   i < dim;
	   i++)
      {
        if (l_mas_b < b[i] - a[i] - 1)
           l_mas_b = b[i] - a[i] - 1;
      }
    
      /* dichiarazione della struttura che 
         conterrà la relazione */
      /* alloca dim strutture (dim contiene 
         il numero di coppie da gestire) */
      pp = (rel_t *) malloc(dim * sizeof(rel_t)); 

      /* deve allocare due puntatori a char interni 
         per ogni struttura che ha allocato 
         nell'istruzione precedente (ovvero "dim" strutture) */
      for (i = 0; 
           i < dim; 
           i++)
      {
        /* alloca un array di caratteri sufficiente 
           per il più grande elemento di A */	
        pp[i].elem_a = (char *) malloc(l_mas_a * sizeof(char));

        /* alloca un array di caratteri sufficiente
           per il più grande elemento di B */
        pp[i].elem_b = (char *) malloc(l_mas_b * sizeof(char));
      }	

      /* caricamento struttura */

      /* il primo for "posiziona" l'indice per gli 
         array 'a' e 'b' e per la struttura 'rel' */
      for (j = 0;
	   j < dim;
	   j++)
      {
        /* copia elem. A */
        if (j == 0)
        {
          /* copia carattere per carattere gli elem.
	     della relazione nella struttura */
	  for (inizio = 2, fine = a[j], k = 0; 
	       inizio < fine;	
	       inizio++, k++)
	  {
	    pp[j].elem_a[k] = relazione[inizio];
	  }	
	  /* inserimento carattere di terminazione stringa */
          pp[j].elem_a[k] = '\0';		
        } 
        else 
        {		
          /* copia carattere per carattere gli elem.
	     della relazione nella struttura */	
          for (inizio = b[j - 1] + 3, fine = a[j], k = 0;
	       inizio < fine;
	       inizio++, k++)
	  {
	    pp[j].elem_a[k] = relazione[inizio];
	  }
	  /* inserimento carattere di terminazione stringa */		
	  pp[j].elem_a[k] = '\0';
        }  

        /* copia elem. B */
        for (inizio = a[j] + 1, fine = b[j], k = 0;
   	     inizio < fine;
	     inizio++, k++)
        {
          pp[j].elem_b[k] = relazione[inizio];
        }		
        /* inserimento carattere di terminazione stringa */
        pp[j].elem_b[k] = '\0'; 
      }
      
      /* allocazione stringhe temporanee */
      temp = (char *) malloc((l_mas_a + l_mas_b + 1) * sizeof(char));
      temp_confr = (char *) malloc((l_mas_a + l_mas_b + 1) * sizeof(char));   

      /* controlla che nessuna coppia di 
          valori sia uguale ad un altra */ 
      for(i = 0;
	  i < dim && errore == 0;
          i++)
      {
        /* concatena la stringa */
        strcpy(temp,
	       pp[i].elem_a);
        strcat(temp,
               pp[i].elem_b);

        for(j = i + 1;
	    j < dim && errore == 0;
	    j++)
        {
          /* concatena la stringa da 
             confrontare */
          strcpy(temp_confr,
                 pp[j].elem_a);
          strcat(temp_confr,
                 pp[j].elem_b);
        
          /* confronta le due stringhe per 
	     vedere se sono coppie uguali */
          ris = strcmp(temp,
	   	       temp_confr);
          if (ris == 0)
          {
            errore = 1;
            printf("\nErrore: non sono ammesse coppie uguali\n"
		   "        nella relazione.\n");
 	  }
        }
      } 
    }    
  } while (errore != 0);


  /* assegnamento 'pp' a '*puntatore'
     per ritornare la struttura */
  *puntatore = pp;
  
  return dim;
}

/* definizione della funzione che stampa 
   una relazione binaria passata come parametro */
void stampa_relazione(rel_t *pp, 	/* i.: relazione da stampare */
  		      int dim)		/* l.: dimensione struttura */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i;				/* l.: indice */
	
  /* messaggio di stampa della
     relazione binaria */
  printf("\nStampa relazione binaria: {");	
  
  /* ciclo che stampa tutte le coppie
     della relazione */
  for (i = 0; 
       i < dim; 
       i++)
  {
    /* se non sta per stampare la prima
       coppia aggiunge la ',' per separare
       dalla coppia precedente */
    if (i > 0)
    {
      printf(", ");
    }	

    /* stampa elemento A ed elemento B */
    printf("(%s, %s)", pp[i].elem_a, pp[i].elem_b);
  }
  
  /* una volta terminato stampa la parentesi
     graffa di chiusura */	
  printf("}\n");
}


/* funzione che restituisce 1 se la coppia (a, b) 
   data in input è presente nella relazione, 0 altrimenti */
int cerca_coppia(rel_t *pp, 		/* l.: relazione */
	         int dim, 		/* l.: dimensione struttura */
		 char* a, 		/* i.: elem. a da cercare */
		 char* b)		/* i.: elem. b da cercare */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i, 				/* l.: indice */			
      trovata = 0;			/* o.: esito ricerca */

  /* ciclo che scandisce la struttura
     per cercare la coppia data in input */	
  for (i = 0; 
       i < dim && !trovata; 
       i++)
  {
    /* se l'elemento 'a' della coppia da cercare
       è uguale all'elemento 'a' della struttura e
       l'elemento 'b' della coppia da cercare è uguale
       all'elemento 'b' della struttura allora assegna 
       1 a trovata */
    if ((strcmp(a, 
                pp[i].elem_a) == 0) && 
        (strcmp(b, 
 	        pp[i].elem_b) == 0))
    {
      trovata = 1;
    }
  }
	
  return trovata;
}


/* definizione della funzione che restituisce 1 
   se la relazione è riflessiva, 0 se non lo è */
int riflessiva(rel_t *pp, 		/* i.: relazione */
	       int dim)			/* l.: dimensione struttura */
{
  /* dichiarazioni delle variabili locali 
     alla funzione */
  int i, 				/* l.: indice */
      riflessiva = 1;			/* o.: esito funzione */
	
  for (i = 0; 
       i < dim && riflessiva; 
       i++)
  {
    /* verifica che le due 
       coppie non siano uguali */
    if (strcmp(pp[i].elem_a, 
	       pp[i].elem_b) != 0)
    {
      /* per ogni coppia (a, b), lancia 
         cerca_coppia su (a, a) e (b, b), 
         così confronta ogni elemento 
         dell'insieme con se stesso */
      if ((!cerca_coppia(pp, 
			 dim, 
			 pp[i].elem_a, 
			 pp[i].elem_a)) || 
          (!cerca_coppia(pp, 
			 dim, 
			 pp[i].elem_b, 
			 pp[i].elem_b)))
      {
        /* una delle due ricerche è fallita,
           quindi la relazione non è sicuramente 
           riflessiva (per ogni elemento a devo 
           trovare una coppia (a, a)) */
	riflessiva = 0;
      }
    }
  }

  return riflessiva;
}


/* definizione della funzione che restituisce 1 
   se la relazione è antisimmetrica, altrimenti 0 */
int antisimmetrica(rel_t *pp, 		/* i.: relazione */
		   int dim)		/* l.: dimensione struttura */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i, 			/* l.: indice */
      antisimmetrica = 1,	/* o.: esito funzione */
      c = 0;			/* l.: controllo */

  for (i = 0; 
       i < dim && antisimmetrica; 
       i++)
  {
    /* verifica che le due 
       coppie non siano uguali */
    if (strcmp(pp[i].elem_a, 
	       pp[i].elem_b) != 0)
    { 
      /* se trova almeno una coppia non
	 uguale vuol dire che sono state 
 	 effettuate le verifiche successive */
      c++;

      /* per ogni coppia (a, b), cerca
         una coppia (b, a), se ne trova una,
         non c'è antisimmetria */
      if (cerca_coppia(pp, 
                       dim, 
		       pp[i].elem_b, 
		       pp[i].elem_a))
      {        
	antisimmetrica = 0;      			
      }
    }
  }
	
  /* se ci sono solo coppie uguali
     non c'è antisimmetria */	
  if (c == 0)
   antisimmetrica = 0;

  
  return antisimmetrica;
}

/* definizione della funzione che restituisce 1 
   se la relazione è Simmetrica, altrimenti 0 */
int simmetrica(rel_t *pp, 		/* i.: relazione */
   	       int dim)			/* l.: dimensione struttura */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i, 			/* l.: indice */
      simmetrica = 1;		/* o.: esito funzione */
	
  for (i = 0; 
       i < dim && simmetrica; 
       i++)
  {
    /* verifica che le due 
       coppie non siano uguali */
    if (strcmp(pp[i].elem_a, 
	       pp[i].elem_b) != 0)
    {
      /* per ogni coppia (a, b), cerca 
         una coppia (b, a); se non ne 
         trova una, non c'è proprietà 
         simmetrica */
      if (!cerca_coppia(pp, 
			dim, 
			pp[i].elem_b, 
			pp[i].elem_a))
      {
        /* non c'è (b, a), 
           assegna 0 a simmetrica */
        simmetrica = 0;			
      }
    } 
  }
	
  return simmetrica;
}


/* definizione della funzione che verifica 
   se una relazione è transitiva */
int transitiva(rel_t *pp, 		/* i.: relazione */
	       int dim)			/* l.: dimensione struttura */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i, 			/* l.: indice */
      transitiva = 1,		/* o.: esito funzione */
      c_uguali = 0,		/* l.: cont. coppie uguali */		
      c_b = 0;			/* l.: coppie che iniziano con b */		

  for (i = 0; 
       i < dim && transitiva; 
       i++)
  {
    /* verifica che le due 
       coppie non siano uguali */
    if (strcmp(pp[i].elem_a, 
	       pp[i].elem_b) != 0)
    {
      
      /* per ogni coppia (a, b) 
         chiama la verifica transitiva 
         su quei valori */
      if (!verifica_transitiva(pp, 
			       dim, 
			       pp[i].elem_a, 
			       pp[i].elem_b,
			       &c_b))
      {
        /* la verifica transitiva su (a,b) 
	   è fallita, possiamo già dire 
	   che la relazione non è transitiva */
        transitiva = 0;
      }
    }
    else 
     c_uguali ++;
  }
	
  /* se non ci sono coppie uguali e non è 
     entrato nel controllo interno della funzione
     "verifica_transitiva" allora non è verificata la
     transitività */
  if (c_uguali == 0 &&
      c_b == 0)
    transitiva = 0;
  
  
  return transitiva;
}


/* definizione della funzione ausiliaria 
   che verifica che la relazione tra l'elemento
   a e b valga anche per ogni c per cui c'è una 
   coppia (b, c) */
int verifica_transitiva(rel_t *pp, 	/* i.: relazione */
  			int dim, 	/* l.: dimensione struttura */ 
			char* a,        /* i.: elem. a da cercare */
			char* b,        /* i.: elem. b da cercare */
			int* coppie_b)	/* l.: coppie che iniz. b */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i, 				/* l.: indice */
      transitiva = 1;			/* o.: esito funzione */
	
  for (i = 0; 
       i < dim && transitiva; 
       i++)
  {
    /* cerchiamo tutte le coppie che 
       iniziano con l'elemento "b" */
    if ((strcmp(b, 
  		pp[i].elem_a) == 0))
    {
      /* è stata trovata una coppia che inizia con b */
      *coppie_b = *coppie_b + 1;
       
      /* ha trovato una coppia (b, c), vediamo 
         se trova nella relazione anche una 
         coppia (a, c) */						
      if (!cerca_coppia(pp, 
		        dim, 
			a, 
			pp[i].elem_b))
      {
        /* non ha trovato nessuna coppia, la 
	   relazione non è sicuramente transitiva */
	transitiva = 0;
      }
			
      /* se arriva qui ha trovato una 
	 coppia (a, c), va avanti con 
	 le prossime fino alla fine 
	 della verifica */
     }
   }
	
  return transitiva;
}


/* definizione della funzione che verifica 
   se una relazione ha proprietà di totalità */
int totale(rel_t *pp, 			/* i.: relazione */
	   int dim)			/* l.: dimensione struttura */
{
  /* dichiarazione delle varaibili locali alla funzione */
  int i = 0, 			/* l.: indice */
      j = 0, 			/* l.: indice */
      totale = 1;		/* l.o.: esito funzione */

  /* per ogni elemento a e b di ogni 
     coppia (a, b), verifica che siano 
     confrontabili tra loro e con tutti 
     gli elementi x e y delle successive 
     coppie (x, y); alla prima verifica 
     fallita possiamo dire che la relazione 
     è parziale */ 
  for (i = 0; 
       i < dim && totale; 
       i++)
  {
    /* controlla a con a */
    if (!confrontabile(pp, dim, pp[i].elem_a, pp[i].elem_a))
    {
      totale = 0;
    }
	
    /* controlla b con b */
    if (!confrontabile(pp, dim, pp[i].elem_b, pp[i].elem_b))
    {
      totale = 0;
    }
		
    /* controlla se a, b sono confrontabili tra loro */
    if (!confrontabile(pp, dim, pp[i].elem_a, pp[i].elem_b))
    {
      totale = 0;
    }
		
    /* confronto a e b con tutti gli x e y delle coppie successive */
    for (j = i; 
         j < dim; 
         j++)
    {
      if (!confrontabile(pp, 
			 dim, 
			 pp[i].elem_a, 
			 pp[j].elem_a) ||
	  !confrontabile(pp, 
			 dim, 
			 pp[i].elem_a, 
			 pp[j].elem_b) ||
	  !confrontabile(pp, 
			 dim, 
			 pp[i].elem_b, 
			 pp[j].elem_a) ||
	  !confrontabile(pp, 
			 dim, 
			 pp[i].elem_b, 
			 pp[j].elem_b))
      {
        totale = 0;
      }
    }			
  }
	
  return totale;
}


/* definizione della funzione ausiliaria che 
   per una coppia di valori x e y cerca se 
   sono confrontabili nella relazione (ovvero 
   se esiste una coppia (x, y) o (y, x)) */
int confrontabile(rel_t *pp, 		/* i.: relazione */
		     int dim, 		/* l.: dimensione struttura */
		     char* x, 		/* i.: elem. x da confrontare */
		     char* y)	        /* i.: elem. y da confrontare */
{
  /* dichiarazione delle variabili locali alla funzione */
  int confrontabile = 0;	/* o.: esito funzione */
	
  if ((!cerca_coppia(pp, 
		     dim, 
		     x, 
		     y)) && (!cerca_coppia(pp, 
					   dim, 
					   y, 
					   x)))
  {
    /* non ha trovato nessuna coppia (x, y) 
       o (y, x), i due valori non sono 
       quindi confrontabili nella relazione */
    confrontabile = 0;	
  } 
  else 
  {
    /* se arriva qui, almeno una delle due 
       coppie è stata trovata, quindi i 
       valori sono confrontabili nella relazione */
    confrontabile = 1;
  }
	
  return confrontabile;
}


/* definizione della funzione che verifica 
   se una relazione binaria è una relazione 
   d'ordine parziale e stampa a video le proprietà 
   che falliscono nel caso in cui non sia tale */
int relazione_parziale(rel_t *pp, 	/* i.: relazione */
		       int dim)		/* l.: dimensione struttura */
{
  /* dichirazione delle variabili locali alla funzione */
  int esito = 0;		/* o.: esito funzione */
  int proprieta[4];		/* l.o.: proprietà non sodd. */



  /* controlla riflessività */
  proprieta[0] = riflessiva(pp,
			    dim);

  /* controlla antisimmetria */
  proprieta[1] = antisimmetrica(pp,
		 	        dim);

  /* controlla transitività */
  proprieta[2] = transitiva(pp,
		 	    dim);
  
  /* controlla totalità */
  proprieta[3] = totale(pp,
		 	dim);
  
  /* verifica se la relazione è di tipo
     d'ordine parziale */
  if (proprieta[0] == 1 && 
      proprieta[1] == 1 &&
      proprieta[2] == 1 &&
      proprieta[3] == 0) 
  {
    printf("\nSi tratta di una relazione d'ordine parziale\n"
           "in quanto soddisfa le seguenti proprietà:\n"
	   "- Riflessività\n- Antisimmetria\n- Transitività\n");
    esito = 1;
  }

  /* se non è una relazione di tipo
     d'ordine parziale stampa le relative
     proprietà non soddisfatte */
  if (esito == 0)
  {
    if (proprieta[0] == 1 && 
        proprieta[1] == 1 &&
        proprieta[2] == 1 &&
        proprieta[3] == 1)
    {
      printf("\nNon si tratta di una relazione d'ordine parziale\n"
       	     "perchè è verificata anche la dicotomia.\n");
    }
    else
    {  
      printf("\nNon si tratta di una relazione d'ordine parziale\n"
             "in quanto non soddisfa le seguenti proprietà:\n");
    
      if (proprieta[0] != 1)
        printf("- Riflessività\n");
   
      if (proprieta[1] != 1)
        printf("- Antisimmetria\n");
   
      if (proprieta[2] != 1)
        printf("- Transitività\n");
    }
  }
 
  return esito;
}


/* definizione della funzione che verifica se 
   una relazione binaria è una relazione d'ordine 
   totale e stampa a video la proprietà che 
   falliscono nel caso in cui non sia tale */
int relazione_totale(rel_t *pp, 	/* i.: relazione */
		     int dim)		/* l.: dimensione struttura */
{
  /* dichiarazione delle variabili locali alla funzione */
  int esito = 0,		/* o.: esito funzione */
      proprieta[4];		/* l.o.: proprietà non sodd. */


  /* controlla riflessività */
  proprieta[0] = riflessiva(pp,
			    dim);

  /* controlla antisimmetria */
  proprieta[1] = antisimmetrica(pp,
		 	        dim);

  /* controlla transitività */
  proprieta[2] = transitiva(pp,
		 	    dim);
  
  /* controlla totalità */
  proprieta[3] = totale(pp,
		 	dim);
  

  /* verifica se la relazione è di tipo
     d'ordine totale */
  if (proprieta[0] == 1 && 
      proprieta[1] == 1 &&
      proprieta[2] == 1 &&
      proprieta[3] == 1) 
  {
    printf("\nSi tratta di una relazione d'ordine totale\n"
           "in quanto soddisfa le seguenti proprietà:\n"
	   "- Riflessività\n- Antisimmetria\n- Transitività\n"
	   "- Dicotomia\n");
    esito = 1;
  }


  /* se non è una relazione di tipo
     d'ordine totale stampa le relative
     proprietà non soddisfatte */
  if (esito == 0)
  {      
    printf("\nNon si tratta di una relazione d'ordine totale\n"
           "in quanto non soddisfa le seguenti proprietà:\n");
    
    if (proprieta[0] != 1)
      printf("- Riflessività\n");
   
    if (proprieta[1] != 1)
      printf("- Antisimmetria\n");
   
    if (proprieta[2] != 1)
      printf("- Transitività\n");

    if (proprieta[3] != 1)
      printf("- Dicotomia\n");
  }
	
  return esito;
}


/* definizione della funzione che verifica
   se una relazione binaria è una relazione 
   di equivalenza e stampa a video la proprietà
   che falliscono nel caso in cui non sia tale */
int relazione_equivalenza(rel_t *pp, 	/* i.: relazione */
			  int dim)	/* l.: dimensione struttura */
{
  /* dichiarazione delle variabili locali alla funzione */
  int esito = 0,		/* o.: esito funzione */
      proprieta[3];		/* l.o.: proprietà non sodd. */


  /* controlla riflessività */
  proprieta[0] = riflessiva(pp,
			    dim);

  /* controlla simmetria */
  proprieta[1] = simmetrica(pp,
		 	    dim);

  /* controlla transitività */
  proprieta[2] = transitiva(pp,
		 	    dim);

  /* verifica se la relazione è di tipo
     d'equivalenza */
  if (proprieta[0] == 1 && 
      proprieta[1] == 1 &&
      proprieta[2] == 1) 
  {
    printf("\nSi tratta di una relazione d'equivalenza\n"
           "in quanto soddisfa le seguenti proprietà:\n"
	   "- Riflessività\n- Simmetria\n- Transitività\n");
    esito = 1;
  }


  /* se non è una relazione di tipo
     d'equivalenza stampa le relative
     proprietà non soddisfatte */
  if (esito == 0)
  {      
    printf("\nNon si tratta di una relazione d'equivalenza\n"
           "in quanto non soddisfa le seguenti proprietà:\n");
    
    if (proprieta[0] != 1)
      printf("- Riflessività\n");
   
    if (proprieta[1] != 1)
      printf("- Simmetria\n");
   
    if (proprieta[2] != 1)
      printf("- Transitività\n");
  }

  return esito;
}


/* definizione della funzione che restituisce
   il numero di coppie che iniziano per "a" 
   (es. (a,b) (a,c)...) */
int conta_accoppiamenti_a(rel_t *pp, 	/* i.: relazione */
			  int dim, 	/* l.: dimensione struttura */
			  char* a)	/* i.: elem. da confrontare */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i, 			/* l.: indice */
      conta = 0;		/* o.: contatore */
	
  for (i = 0; 
       i < dim; 
       i++)
  {
    if ((strcmp(a, 
		pp[i].elem_a) == 0))
    {
      /* coppia (a, y) trovata, 
	 si incrementa il contatore */
      conta++;
    }
  }
	
  return conta;
}

/* definizione della funzione che restituisce 
   il numero di coppie che hanno come secondo elemento
   'b' (es. (a,b) (c,b)...) */
int conta_accoppiamenti_b(rel_t *pp, 	/* i.: relazione */
			  int dim, 	/* l.: dimensione struttura */
			  char* b)	/* i.: elem. da confrontare */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i, 			/* l.: indice */
      conta = 0;		/* o.: contatore */	
  
  for (i = 0; 
       i < dim; 
       i++)
  {
    if ((strcmp(b, 
		pp[i].elem_b) == 0))
    {
      /* coppia (x, b) trovata, 
	 si incrementa il contatore */
      conta++;
    }
  }
	
  return conta;
}

/* definizione della funzione che chiede 
   all'utente di inserire una serie di valori 
   di un insieme */
int carica_insieme(insieme_t **insieme)	/* i.: insieme B */
{
  /* dichiarazione delle variabili locali alla funzione */
  int elem_agg = 0, 		/* i.: numero elementi */
      i = 0,			/* l.: indice */
      j = 0,			/* l.: indice */
      l_temp;			/* l.: lungh. temp. */
		
  char risposta,		/* i.: risp. utente */
       intero_validare[3];	/* l.: intero da validare */

  int errore = 0;		/* l.: esito controllo */

  /* puntatore a insieme_t di appoggio 
     (poi lo copieremo dentro *insieme) */
  insieme_t *nuovo_insieme;
  
  /* variabile di appoggio per i dati 
     inseriti: accettia elementi di, 
     massimo, 100 caratteri */
  char temp_elem[100];
  
  /* stampa messaggio direttiva */
  printf("\nPer verificare se la funzione è iniettiva,\n"
	 "suriettiva o biiettiva è necessario conoscere\n"
	 "l'insieme B.\n\nN.B. Gli elementi dell'insieme B avranno"
	 " le stesse\nregole grammaticali degli elementi della"
	 " relazione.\n");
  
  /* domanda per insieme B */ 
  do
  {
    printf("\nL'insieme B è composto da altri elementi oltre\n"
	   "quelli elencati nella relazione?\n\n(s/n)\n");
    
    /* acquisizione risposta saltando newline */ 
    scanf("%c%c",
	  &risposta,
	  &risposta);
    
    /* messaggio di errore */
    if (risposta != 's' &&
	risposta != 'n')
    {
      printf("\nErrore: carattere non accettato.\n"
	     "\nInserire 's' se la risposta è affermativa,\n"
	     "'n' se la rispsota è negativa.\n");
    }

  } while (risposta != 's' &&
	   risposta != 'n');

  /* se la rispsota è affermativa si procede con 
     l'acquisizione dei valori aggiuntivi */
  if (risposta == 's')
  {
    /* acquisizione numero elem. aggiuntivi */
    do
    {
      printf("\nDa quanti altri elementi è composto l'insieme B?\n");

      /* acquisizione intero sotto forma di stringa */
      scanf("%s",
  	    intero_validare);
 
      /* controlla che sia stato inserito un intero e,
         se necessario, stampa il relativo errore */
      errore = valida_intero(intero_validare,
			     &elem_agg);

      /* stampa messaggio di errore */
      if (errore != 0)
      {
        printf("\nErrore: è stato inserito un numero non valido.\n\n");
      }

    } while (errore != 0);

    /* allocazione insieme */
    nuovo_insieme = (insieme_t *) malloc(elem_agg * 
     				         sizeof(insieme_t));
    
    printf("Caricare %d elementi dell'insieme B"
	   " che non\nsono già inclusi nelle coppie"
	   " della relazione\n", 
	   elem_agg);
    
    /* caricamento elementi nell'insieme B */
    for(i = 0; 
        i < elem_agg; 
        i++)
    {
      do
      {
        printf("Inserire elemento numero %d:\n", 
  	       i + 1);
        /* acquisizione elemento */
        scanf("%s",
	      temp_elem);	
	
        /* acquisizione lunghezza elem. inserito */
        l_temp = strlen(temp_elem);

        for(j = 0, errore = 0;
	    j < l_temp && errore == 0;
	    j ++)
        {
          /* controlla carattere per carattere */
          errore = controlla_carattere(temp_elem[j]);

          /* stampa messaggio di errore */
          if (errore == 1)
          {
            printf("\nErrore: l'elemento inserito non è corretto.\n\n");
          }
        }
      } while (errore != 0);

      /* allocazione un nuovo elemento */			
      nuovo_insieme[i].elem = (char *) malloc((int)l_temp 
					      * sizeof(char));
		
      /* copio l'elemento inserito nel nuovo 
         elemento allocato */
      strcpy(nuovo_insieme[i].elem, 
             temp_elem);
    }
  }  
		
  /* assegnamento 'nuovo_insieme' a '*insieme'
     per ritornare la struttura */
  *insieme = nuovo_insieme;
	
  return elem_agg;
}


/* definizione della funzione che verifica se 
   la relazione è una funzione matematica. 
   Se non lo è, stampa la proprietà che fallisce. 
   Se lo è, indica se è iniettiva, suriettiva o biettiva */
int funzione_matematica(rel_t *pp, 	/* i.: relazione */
			int dim)	/* l.: dimensione struttura */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i = 0;			/* l.: indice */

  int no_funzione = 0, 		/* l.: esito ver. */
      iniettiva = 1, 		/* l.: esito inie. */
      suriettiva = 1; 		/* l.: esito suri. */
	
  int num_elementi_a;		/* l.: numero elem. a*/
	
  /* controlla se è una funzione */
  for (i = 0; 
       i < dim && !no_funzione; 
       i++)
  {
    /* per ogni a che trova nelle coppie 
       (a, b), verifica se ci sono più 
       coppie (a, x). Se ci sono, la relazione 
       non è sicuramente una funzione matematica */
    if (conta_accoppiamenti_a(pp, 
			      dim, 
			      pp[i].elem_a) > 1)
    {
      /* una funzione non può avere più risultati 
	 per ogni X del dominio */
      no_funzione = 1;
      printf("\nLa relazione non è una funzione matematica:\n"
	     "ci sono più valori del codominio in relazione \n"
  	     "con l'elemento %s del dominio.\n", 
	     pp[i].elem_a);
    }
		
    /* con questa funzione si conta quante coppie (x, b)
       ci sono con l'elemento "b" a destra */
    num_elementi_a = conta_accoppiamenti_b(pp, 
					   dim, 
					   pp[i].elem_b);

    /* controllo iniettività */	
    if (num_elementi_a > 1)
    {
      /* se ci sono più coppie con l'elemento "b" 
	 di cui sopra, la funzione non è iniettiva
	 (perché associa più elementi del dominio 
	  a un particolare elemento "b" del codominio) */
      iniettiva = 0;
    }
  }

  if (!no_funzione)
  {
    /* caricamento insieme B */
    int dim_b = 0; /* dimensione dell'insieme B */
    insieme_t *insieme_b = NULL; /* puntatore all'insieme B */
	
    dim_b = carica_insieme(&insieme_b);

    /* controllo suriettività */
    for (i = 0;
         i < dim_b && suriettiva; 
         i++)
    {
      /* per ogni elemento "b" dell'insieme B, 
         cerca se esistono coppie (x, b). Se 
         non esistono, la funzione non è suriettiva 
         perché il cod(f) non comprende tutto 
         l'insieme B */		 
      if (conta_accoppiamenti_b(pp, 
			        dim, 
			        insieme_b[i].elem) <= 0)
      {
        suriettiva = 0;
      } 
    }
	
    
    /* procede con la verifica delle proprietà */
    if (!iniettiva && !suriettiva)
    {
      printf("\nLa relazione è una funzione matematica.\n");
    }
    else
    {
      printf("\nLa relazione è una funzione matematica\n"
	     "ed è");

      if (iniettiva && suriettiva)
      {
        printf(" biiettiva.\n");
      } 		
      else if (iniettiva)
      {
        printf(" iniettiva.\n");
      }
      else if (suriettiva)
      {
        printf(" suriettiva.\n");
      }
    }
  }
			
  return 1;
}






