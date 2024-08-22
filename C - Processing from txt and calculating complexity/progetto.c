/*********************************************/
/* Progetto ASD sessione autunnale 2013/2014 */
/*********************************************/
/* sviluppato da Matteo Incicco              */
/*********************************************/


/********************************************/
/* inclusione delle librerie standard del c */
/********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/********************************/
/* dichiarazione delle funzioni */
/********************************/ 

int valida_intero(const char *intero_stringa, 	
                  int *intero_validato);
int valida_stringa(const char *str,
		   const char *dizionario,
		   const int len_str);
void divisione_stringa(char *stringa_iniziale,		
		       int inizio,			
		       int fine,			
		       char *stringa_finale);	
void report(const char *r_corrette,
	    const int *id_stud,
	    char **risp_stud,
	    int *perc_stud,
	    const int num_stud,
            int *num_errori);
void risposte(const char *risposte);
void punteggio(const char *r_corrette,
	       const int *id_stud,
	       char **risposte_stud,
	       int *percentuale_stud,
	       const int numero_stud);
int conta_carattere(const char *str1,
		    const char *str2);
void stampa_punt(const int *id_stud,
                 const int *percentuale_stud,
      	         const int numero_stud);
void errori(const char *risposte_corrette,
	    char **risposte_studenti,
	    const int numero_studenti,
	    int *numero_errori); 
void quicksort(int *a_primario,
	       int sx,
	       int dx,
	       int *a_secondario);


/***********************************/
/* definizione della funzione main */
/***********************************/

int main(void)
{
  /* dichiaro le variabili locali alla funzione */
  int n_stud = 0,				/* i.: numero studenti */
      n_dom = 0; 				/* i.: numero domande */
  
  int *id;					/* i.: id studente */
  char **risp;			               	/* i.: risposte studente */
       
  char *risp_cor;				/* i.: risposte corrette */
  int *n_err;					/* o.: numero risposte errate */
  int *perc;		   			/* o.: percentuale risposte corrette */

  const char caratteri[7] = {'a',		/* l.: caratteri consentiti */
			     'b',
			     'c',
			     'd',
			     'e',
		             'f',
			     'g'};

  FILE *file_datiesame;				/* l.: puntatore al file di input */

  int i;					/* l.: contatore */
  
  char intero_validare[6];			/* l.: intero da validare */

  int eof;					/* l.: controllo fine file */

  int len_riga;					/* l.: lunghezza riga intera */

  char *res;					/* l.: esito fgets */
  
  char *riga_intera;				/* i./l.: riga intera da suddividere */
  
  int errore_nstud = 0,				/* l.: indica se n_stud è errata */
      errore_ndom = 0,				/* l.: indica se n_dom è errata */
      errore_rispcor = 0,			/* l.: indica se risp_cor è errata */
      errore_idrisp = 0,			/* l.: acquisizione id e risp err. */
      esito_acquisizione = 0;			/* l.: esito complessivo acquisizione */

  char risposta_utente;				/* i.: risposta utente della domanda */
  char newline;					/* l.: acquisizione newline */

  float f_nstud;				/* l.: float n_stud */
  float somma_media;				/* l.: somma percentuali per la media */
  float media;					/* o.: media delle percentuali */
  
  int resto;					/* l.: resto per calcolo mediana */
  float mediana_1 = 0;				/* l.: mediana prima della metà */
  float mediana_2 = 0;				/* l.: mediana dopo la metà */
  float mediana;				/* o.: mediana delle percentuali */

  /* apre il file */
  file_datiesame = fopen ("datiesame.txt",
		      "r");
  
  /* verifica errori in apertura */
  if (file_datiesame == NULL)
  {
    perror ("Errore in apertura del file.\n");
    exit(1);
  }
  
  
  /* acquisisce il numero degli studenti dalla prima riga */
  eof = fscanf (file_datiesame,
	        "%s",
	        intero_validare);

  /* controllo che il file non sia finito per continuare */
  if (eof != 1)
    printf("\nErrore: file vuoto.\n");
  else
  {
    /* validazione n_stud */
    errore_nstud = valida_intero(intero_validare, 	
                                 &n_stud);
  
    /* stampa il messaggio di errore opportuno */
    if (errore_nstud == 1)
    {  
      printf ("\nErrore: il numero degli studenti contenuto nella\n"
              "        prima riga non è corretto.\n"
	      "        Modificare il file.\n"
	      "\n N.B. Il numero massimo accettato è 99999.\n");
    }
  
    /* acquisisce il numero delle domande dalla seconda riga */
    eof = fscanf (file_datiesame,
  	          "%s",
	          intero_validare);
   
    /* controllo che il file non sia finito per continuare */
    if (eof != 1)
      printf("\nErrore: file terminato prima dell'acquisizione\n"
             "        della seconda riga.\n");
    else if (errore_nstud != 1)
    {
      /* validazione n_dom */
      errore_ndom = valida_intero(intero_validare, 	
                                  &n_dom);

      /* stampa il messaggio di errore opportuno */
      if (errore_ndom == 1)
      {  
        printf("\nErrore: il numero delle domande contenuto nella\n"
               "        seconda riga non è corretto.\n"
 	       "        Modificare il file.\n"
 	       "\n N.B. Il numero massimo accettato è 99999.\n");
      }
    }
  }

  /* continua controllando che tutto sia corretto, 
     altrimenti non esegue le prossime operazioni */
  if (eof == 1)
  {
    if (errore_nstud != 1)
    {
      if (errore_ndom != 1)
      {   					     
        /* allocazioni */
        risp_cor = (char *) malloc((n_dom + 1) * sizeof (char));
        
	/* acquisisce la stringa delle risposte corrette */
        eof = fscanf(file_datiesame,
     	   	     "%s",
	             risp_cor);

	/* controllo che non sia terminato il file */
        if (eof != 1)
	  printf("\nErrore: file terminato prima dell'acquisizione\n"
             "        della stringa delle risposte corrette\n"
             "        nella terza riga.\n");
        else 
        {
          /* validazione risp_cor */
          errore_rispcor = valida_stringa(risp_cor,
					  caratteri,
				          n_dom);
          /* stampa il messaggio di errore opportuno */
          if (errore_rispcor == 1)
          {  
            printf("\nErrore: la stringa delle risposte esatte contenuta\n"
                   "        nella terza riga non è corretta.\n"
 		   "        Modificare il file.\n"
 	           "\n N.B. I caratteri accettati sono: a, b, c, d, e, f, g.\n"
   	           " N.B. La lunghezza deve essere quella contenuta nella\n" 
		   "      seconda riga del file.\n");
          }
        }
      }				
    }              
  }
    
  /* continua controllando che tutto sia corretto, 
     altrimenti non esegue le prossime operazioni */
  if (eof == 1)
  {
    if (errore_nstud != 1)
    {
      if (errore_ndom != 1)
      {
        if (errore_rispcor != 1)
        {
          /* allocazioni */ 
          riga_intera = (char *) malloc((6 + 1 + n_dom + 1) * sizeof (char));
          id = (int *) malloc(n_stud * sizeof (int));
 
          /* viene allocata la matrice "risp" con una malloc 
             in modo da poterla utilizzare all'interno delle 
             funzioni */
          risp = (char **) malloc(sizeof(char *) * n_stud);
          for(i = 0; 
	      i < n_stud;
	      i++)
            risp[i] = (char *) malloc(sizeof(char) * n_dom + 1);
 
          /* acquisizione riga intera */  
          for (i = 0, errore_idrisp = 0;
               i < n_stud && errore_idrisp == 0;
               i ++)
          { 
            /* salto new line rimanente da fscanf */
            if (i == 0)
            {
              res = fgets(riga_intera,
	                  2,
	                  file_datiesame);
              
    	      if (res == NULL)
	      {			
                errore_idrisp = 2;
              }
	      else 
 	      {			
                res = fgets(riga_intera,
	                    6 + 1 + n_dom +1,
	                    file_datiesame);
		
		if (res == NULL)
		{
		  errore_idrisp = 2;
		}
		else
		{			
 		  /* divisione e validazione */
                  len_riga = strlen (riga_intera);
		  
		  /* rimozione \n */
		  riga_intera[len_riga - 1] = '\0';
	          len_riga = strlen(riga_intera);
		  
		  if (len_riga < 1 + 1 + n_dom)
                  {
                    errore_idrisp = 1;
                  }
                  else 
                  { 
                    /* divide la stringa per acquisire le risposte */
                    divisione_stringa (riga_intera,
		                       len_riga - n_dom,
		                       len_riga - 1,
		                       risp[i]);

                    /* valida le risposte */
                    errore_idrisp = valida_stringa (risp[i],
		              		            caratteri,
				                    n_dom);

                    if (errore_idrisp == 0)
                    {
                      /* divide la stringa per acquisire l'id */
                      divisione_stringa (riga_intera,
		                         0,
		                         len_riga - n_dom - 1 - 1,
		                         intero_validare);

                      /* valida l'id */
                      errore_idrisp = valida_intero (intero_validare,
		             		             &id[i]);
                    }
                  }	
		}
              }
            } 
            else 
            {
              res = fgets(riga_intera,
	                  6 + 1 + n_dom + 1,
	                  file_datiesame);
	      
	      if (res == NULL)
              {
	        errore_idrisp = 2;
	      }
	      else 
	      {
		/* divisione e validazione */
                len_riga = strlen(riga_intera);
		
		/* rimozione \n */
                if (riga_intera[len_riga - 1] == '\n')
                { 
		  riga_intera[len_riga - 1] = '\0';
	          len_riga = strlen(riga_intera);
		}					

	      	if (len_riga < 1 + 1 + n_dom)
                {
                  errore_idrisp = 1;
                }
                else 
                { 
                  /* divide la stringa per acquisire le risposte */
                  divisione_stringa (riga_intera,
	                             len_riga - n_dom,
         	                     len_riga - 1,
		                     risp[i]);

                  /* valida le risposte */
                  errore_idrisp = valida_stringa (risp[i],
		            		          caratteri,
				                  n_dom);

                  if (errore_idrisp == 0)
                  {
                    /* divide la stringa per acquisire l'id */
                    divisione_stringa (riga_intera,
		                       0,
		                       len_riga - n_dom - 1 - 1,
		                       intero_validare);
    
                    /* valida l'id */
                    errore_idrisp = valida_intero (intero_validare,
		             		           &id[i]);
                  }
                }		
	      }
            }					
          }
	}
      }
    }
  }

  /* se c'è un errore nell'acquisizione degli id e delle 
     risposte stampa il messaggio di errore */
  if (errore_idrisp == 2)
  {
    printf("\nErrore: file terminato prima di acquisire\n"
	   "        tutti gli id e tutte le risposte.\n");
  }
  else if (errore_idrisp == 1)
  {
    printf("\nErrore: id e risposte degli studenti non sono corretti.\n"
           "        Modificare il file.\n"
           "\n N.B. l'id massimo accettato è 99999.\n"
 	   " N.B. I caratteri accettati sono: a, b, c, d, e, f, g.\n"
   	   " N.B. La lunghezza deve essere quella contenuta nella\n" 
           "      seconda riga del file.\n");
  }

  /* assegna esito di tutte le acquisizioni 
     a esito_acquisizione */
  if (eof == 1 &&
      errore_nstud == 0 &&
      errore_ndom == 0 &&
      errore_rispcor == 0 &&
      errore_idrisp == 0)
    esito_acquisizione = 1;
  else 
    esito_acquisizione = 0;


  /* se non si sono verificati errori durante 
     l'acquisizione fa il report d'esame e chiede 
     all'utente cosa si intende fare a questo 
     punto dell'esecuzione */
  if (esito_acquisizione == 1)
  {
    /* allocazione perc e n_err */
    perc = (int *) malloc(n_stud * sizeof (int));
    n_err = (int *) malloc(n_dom * sizeof (int));

    /* viene inizializzato l'array "n_err" */ 
    for (i = 0;
         i < n_dom;
         i ++)
    {
      n_err[i] = 0;
    }
    
    /* chiamata alla funzione report */
    report(risp_cor,
           id,
           risp,
           perc,
           n_stud,
           n_err);  
    
    /* effettua domanda all'utente */
    printf("\nDigitare 'o' se si vuole un report ordinato\n"
	   "in base all'identificativo studente.\n\nDigitare"
	   " 'm' se si vuole calcolare la media e\nla mediana"
	   " dei voti ottenuti dagli studenti.\n\nDigitare 't'"
	   " se si vuole terminare l'esecuzione\ndel programma.\n\n");
    
    /* acuisisce risposta dell'utente */
    do
    {
      scanf("%c/%c", 
	    &risposta_utente,
	    &newline);

      /* se non si è immesso un carattere di quelli indicati 
	 stampa il relativo messaggio di errore */
      if (risposta_utente != 'o' &&
	  risposta_utente != 'm' &&
	  risposta_utente != 't')
      {
        printf("Errore: non si è immesso un carattere corretto.\n\n"
	       "N.B. il software è case sensitive.\n");
      } 
    }
    while (risposta_utente != 'o' &&
	   risposta_utente != 'm' &&
	   risposta_utente != 't');
    
    /* procede in base alla risposta dell'utente */
    if (risposta_utente == 'o')
    { 
      /* chiama quicksort per ordinare in base all'id */
      quicksort(id,
	        0,
	        n_stud - 1,
	        perc); 
     
      /* stampa id e punteggio */
      stampa_punt(id,
		  perc,
		  n_stud);
    }
    else if (risposta_utente == 'm')
    {
      /* chiama quicksort per ordinare in base alla percentuale */
      quicksort(perc,
		0,
		n_stud - 1,
		id);
      
      /* calcola e stampa la media delle percentuali */
      for (i = 0, somma_media = 0;
	   i < n_stud;
	   i++)
      {
        somma_media = somma_media + perc[i];
      }

      f_nstud = n_stud;

      media = somma_media / f_nstud;

      printf("\nLa media delle percentuali è:\t%f.\n", 
	     media);

      /* calcola e stampa la mediana delle percentuali */
      resto = n_stud % 2;

      if (resto == 1)
      { 
        mediana = perc[((n_stud + 1) / 2) - 1];
      }
      else 
      { 
        mediana_1 = perc[(n_stud / 2) - 1];
        mediana_2 = perc[((n_stud / 2) + 1) - 1];
        mediana = (mediana_1 + mediana_2) / 2;
      }

      printf("\nLa mediana delle percentuali è:\t%f\n\n",
	     mediana);
    }
  }

  /* chiudo il file aperto */
  fclose(file_datiesame);
  
  return(0);
}


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
      len;					/* l.: lunghezza stringa intero */
 
  int errore = 0;				/* o.: errore che rest. la fun. */

  len = strlen(intero_stringa);

  /* controlla che len non sia più grande di 5 */
  if (len >= 6)
    errore = 1;
  else 
  {
    /* controlla che nella prima posizione non ci 
       sia uno 0 */
    if (intero_stringa[i] != '0')
    {
      /* controlla che in ogni posizione dell'array ci 
         sia una cifra da 0 a 9 */ 
      while (i < len) 
      {
        if (errore == 1)
          i = len;
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


/* definizione della funzione che valida una stringa, 
   restituirà 1 se è errata o 0 se è corretta */
int valida_stringa(const char *str,		/* i.: stringa da validare */
		   const char *dizionario,	/* i.: caratteri consentiti */
		   const int len_str)		/* i.: lunghezza corretta stringa */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i,					/* l.: indice */
      j;					/* l.: indice */
     
  int len,					/* l.: lunghezza "str" */
      dim_diz;					/* l.: dimensione dizionario */

  int errore;					/* o.: errore */

  len = strlen(str);
  dim_diz = strlen(dizionario);

  /* controlla che la lunghezza della stringa 
     acquisita sia della lunghezza giusta */
  if (len != len_str)
    errore = 1;
  else 
  {
    /* ciclo che scandisce la stringa da validare */  
    for (i = 0, errore = 0;
         i < len;
         i ++)
    {
      if (errore == 1)
        i = len;
      else 
      {
        errore = 1;

        /* ciclo che scandisce e confronta il dizionario */
        for (j = 0;
	     j < dim_diz;
	     j ++)
        { 		
          if (str[i] == dizionario[j])
          {
 	    errore = 0;
	    j = dim_diz;
          }
        }
      }  
    }
  }

  return errore;
}


/* definizione della funzione necessaria per suddividere una stringa,
   essa copia il contenuto di una stringa in un altra stringa da un 
   indice di inizio ad un indice di fine */
void divisione_stringa(char *stringa_iniziale,		/* i.: str. da cop. */
		       int inizio,			/* i.: indice inizio */
		       int fine,			/* i.: indice fine */
		       char *stringa_finale)		/* o.: str. risultante */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i;						/* l.: variabile contatore */

  /* ciclo utilizzato per copiare valori da 'stringa_iniziale' a 
     'stringa_finale' confrontando 'inizio' e 'fine' */
  for (i = 0;
       inizio <= fine;
       inizio ++, i ++)
  {
    stringa_finale[i] = stringa_iniziale[inizio];
  }
  
  /* assegno '\0' all'ultima posizione di stringa_finale */
  stringa_finale[i] = '\0'; 
}


/* definizione della funzione che si occupa di fare un 
   report dell'esame */
void report(const char *r_corrette,		/* i.: risposte correte */
	    const int *id_stud,			/* i.: id dello studente */
	    char **risp_stud,			/* i.: risposte dello studente */
	    int *perc_stud,			/* o.: perc. risp. esatte stud. */
	    const int num_stud,  		/* l.: numero degli stud. */
	    int *num_errori)			/* o.: numero errori domande */
{
  /* stampa a video dell'intestazione "Report d'esame" */
  printf("\n\n\t\t\tReport d'esame\n");

  /* stampa a video delle risposte corrette */
  risposte(r_corrette);

  /* stampa a video del punteggio di ogni studente */
  punteggio(r_corrette,
	    id_stud,
	    risp_stud,
	    perc_stud,
	    num_stud);

  /* stampa a video degli errori commessi dagli studenti
     su ogni domanda */
  errori(r_corrette,
	 risp_stud,
         num_stud,
	 num_errori); 
}


/* definizione della funzione che stampa a video il
   numero della domanda e la risposta corretta */
void risposte(const char *risposte)		/* i.: risposte correte */
{
  /* dichiarazione delle variabili locali alla funzione */
  int num_risp,					/* l.: numero risposte */
      i;					/* l.: indice */

  num_risp = strlen(risposte);


  /* stampa la riga che indica a quale domanda
     ci si riferisce */
  printf("Domanda\t\t");
  
  /* ciclo che stampa il numero della domanda 
     in colonna */
  for(i = 1;
      i <= num_risp;
      i ++)
  { 
    if (i >= 10)
    { 
      if (i != num_risp)
      {
        printf("  %d",
	       i);
      }
      else 
      {
        printf("  %d\n",
 	       i);
      }
    }
    else
    {
      if (i != num_risp)
      {
        printf("   %d",
	       i);
      }
      else 
      {
        printf("   %d\n",
 	       i);
      }
    } 
  }
  
  /* stampa la riga che indica la risposta corretta 
     per ogni domanda */
  printf("Risposta\t");
  
  /* ciclo che stampa la risposta corretta 
     incolonnata con il numero della domanda */
  for(i = 0;
      i < num_risp;
      i ++)
  {
    if(i != num_risp - 1)
    {
      printf("   %c",
	     risposte[i]);
    }
    else
    {
      printf("   %c\n",
 	     risposte[i]);
    }
  }
}


/* definizione della funzione che stampa l'id di 
   ogni studente e il suo relativo punteggio 
   espresso in percentuale */
void punteggio(const char *r_corrette,		/* i.: risposte correte */
	       const int *id_stud,		/* i.: id studente */
	       char **risposte_stud,	        /* i.: risposta studente */
	       int *percentuale_stud,		/* o.: perc. risp. cor. */
	       const int numero_stud)		/* l.: numero degli stud. */
{
  /* dichiarazione delle variabili locali alla funzione */
  int num_risp;					/* l.: numero risposte */
  num_risp = strlen(r_corrette);
  
  int i;					/* l.: contatore */

  int ricorrenza;				/* l.: num. ricor. carattere */

  /* ciclo per calcolare la percentuale di risposte
     corrette di ogni studente */
  for(i = 0;
      i < numero_stud;
      i ++)
  {
    /* chiama la funzione conta_carattere per contare 
       quanti carattere uguali sono presenti nella 
       stessa posizione */
    ricorrenza = conta_carattere(risposte_stud[i],
				 r_corrette);
    
    /* applica la formula matematica per calcolare 
       la proporzione a : b = c : d */
    percentuale_stud[i] = (ricorrenza * 100) / num_risp;
  }
  
  /* chiama la funzione che si occupa di 
     stampare il punteggio */
  stampa_punt(id_stud,
	      percentuale_stud,
	      numero_stud);
}


/* definizione della funzione che conta quanti caratteri 
   sono uguali e nella stessa posizione */
int conta_carattere(const char *str1,		/* i.: stringa 1 */
		    const char *str2)		/* i.: stringa 2 */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i,					/* l.: indice */
      len;					/* l.: lungh. stringhe */

  int c = 0;					/* o.: contatore ric. */

  len = strlen(str1);

  /* ciclo che conta le ricorrenze dei caratteri 
     uguali nella stessa posizione */
  for (i = 0;
       i < len;
       i ++)
  {
    if (str1[i] == str2[i])
      c++;
  }
  
  return c;
}


/* definizione della funzione che stampa il 
   punteggio calcolato */
void stampa_punt(const int *id_stud,		/* i.: id studenti */
                 const int *percentuale_stud,	/* i.: percentuale studenti */
		 const int numero_stud)		/* i./l.: numero studenti */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i;					/* l.: indice */

  /* stampa a video l'id di ogni studente con il 
     relativo punteggio */
  printf("\tID\t\tPunteggio (percentuale)\n");
  for(i = 0;
      i < numero_stud;
      i ++)
  {
    printf("\t%d\t\t   %d\n",
	   id_stud[i],
	   percentuale_stud[i]);
  }
}


/* definizione della funzione che conta da quanti 
   studenti è stata sbagliata ogni singola domanda */
void errori(const char *risposte_corrette,	/* i.: risposte corrette */
	    char **risposte_studenti,		/* i.: risposte studenti */
	    const int numero_studenti,		/* l.: numero degli studenti */
	    int *numero_errori)   		/* o.: numero errori commessi */
{
  /* dichiarazione delle variabili locali alla funzione */
  int i,					/* l.: indice */
      j,					/* l.: indice */
      numero_domande;				/* l.: numero delle domande */

  numero_domande = strlen(risposte_corrette); 

  /* ciclo che scandisce l'array risposte_correte 
     e lo confronta con studenti.risp */
  for(i = 0;
      i < numero_studenti;
      i ++)
  {

    /* ciclo interno che scandisce gli stundenti */
    for (j = 0;
	 j < numero_domande;
	 j ++)
    { 
       if (risposte_studenti[i][j] != risposte_corrette[j])
        numero_errori[j] ++;
    } 
  }

  /* stampo gli errori nel report d'esame */
  printf("Domanda\t\t");
  
  /* ciclo che stampa il numero della domanda 
     in colonna */
  for(i = 1;
      i <= numero_domande;
      i ++)
  { 
    if (i >= 10)
    { 
      if (i != numero_domande)
      {
        printf("  %d",
	       i);
      }
      else 
      {
        printf("  %d\n",
 	       i);
      }
    }
    else
    {
      if (i != numero_domande)
      {
        printf("   %d",
	       i);
      }
      else 
      {
        printf("   %d\n",
 	       i);
      }
    } 
  }
  
  /* stampa la riga che indica da quanti studenti 
     è stata sbagliata la risposta di ogni domanda */
  printf("Sbagliata da\t");

  /* ciclo che stampa il numero di domande sbagliate */
  for(i = 0;
      i < numero_domande;
      i ++)
  { 
    if (numero_errori[i] >= 10)
    { 
      if (i != numero_domande - 1)
      {
        printf("  %d",
	       numero_errori[i]);
      }
      else 
      {
        printf("  %d\n",
 	       numero_errori[i]);
      }
    }
    else
    {
      if (i != numero_domande - 1)
      {
        printf("   %d",
	       numero_errori[i]);
      }
      else 
      {
        printf("   %d\n",
 	       numero_errori[i]);
      }
    } 
  }
}


/* definizione della funzione necessaria al riordinamento degli
   array */
void quicksort(int *a_primario,
	       int sx,
	       int dx,
	       int *a_secondario)
{
  int pivot,
      tmp,
      i,
      j;

  /* crea la tripartizione */
  for (pivot = a_primario [(sx + dx) / 2], i = sx, j = dx;
       (i <= j);
      )
  {
    while (a_primario[i] < pivot)
      i++;
    while (a_primario[j] > pivot)
      j--;
    if (i <= j)
    {
      if (i < j)
      { 
        /* scambio valori */
        tmp = a_primario[i];
	a_primario[i] = a_primario[j];
        a_primario[j] = tmp;

        tmp = a_secondario[i];
	a_secondario[i] = a_secondario[j];
	a_secondario[j] = tmp;
      }
      i++;
      j--;      
    }
  }

  /* ordina la prima e la terza parte se contenenti più di un elemento
     chiamando ricorsivamente quicksort */
  if  (sx < j)
    quicksort(a_primario,
	      sx,
              j,
	      a_secondario);
  if  (i < dx)
    quicksort(a_primario,
	      i,
	      dx,
	      a_secondario);
}











