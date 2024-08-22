/*******************************************/
/* programma che si occupa di calcolare la */ 
/* complessità degli algoritmi di calcolo  */
/* e output del report, di calcolo del     */
/* report ordinato e di calcolo di media e */
/* mediana.				   */
/*******************************************/
/* sviluppato da Matteo Incicco            */
/*******************************************/

/*****************************/
/* inclusione delle librerie */
/*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/********************************/
/* dichiarazione delle funzioni */
/********************************/
void quicksort(int *a_primario,
	       int sx,
	       int dx,
	       int *a_secondario,
	       int *passi);



/***********************************/
/* definizione della funzione main */
/***********************************/

int main(void)
{
  /* dichiarazione delle variabili locali alla funzione */
  int passi = 0;				/* o. contatore passi base */
  int id[30];					/* l. id */
  int perc[30];					/* l. percentuali */
  int i;					/* l. contatore */
  int resto;					/* l. resto */

  /******* calcolo complessità quicksort *******/
  /* generazione casuale id e perc */
  for (i = 0;
       i < 30;
       i ++)
  {

    id[i] = rand() % 10000 + 1;
    
    perc[i] = rand() % 100 + 1;
  }

  /* calcolo passi base quicksort 1 id */
  quicksort(id,
	    0,
	    0,
	    perc,
	    &passi);

  printf("I passi effettuati dal quicksort per 1 id sono : %d.\n",
         passi);

  /* generazione casuale id e perc */
  for (i = 0;
       i < 30;
       i ++)
  {

    id[i] = rand() % 10000 + 1;
    
    perc[i] = rand() % 100 + 1;
  }

  /* calcolo passi base quicksort 10 id */
  quicksort(id,
	    0,
	    9,
	    perc,
	    &passi);

  printf("I passi effettuati dal quicksort per 10 id sono : %d.\n",
         passi);
  
  /* reinizializzo passi */
  passi = 0;

  /* generazione casuale id e perc */
  for (i = 0;
       i < 30;
       i ++)
  {

    id[i] = rand() % 10000 + 1;
    
    perc[i] = rand() % 100 + 1;
  }


  /* calcolo passi base quicksort 20 id */
  quicksort(id,
	    0,
	    19,
	    perc,
	    &passi);

  printf("I passi effettuati dal quicksort per 20 id sono : %d.\n",
         passi);

   /* reinizializzo passi */
  passi = 0;

  /* generazione casuale id e perc */
  for (i = 0;
       i < 30;
       i ++)
  {

    id[i] = rand() % 10000 + 1;
    
    perc[i] = rand() % 100 + 1;
  }


  /* calcolo passi base quicksort 30 id */
  quicksort(id,
	    0,
	    29,
	    perc,
	    &passi);

  printf("I passi effettuati dal quicksort per 30 id sono : %d.\n",
         passi);
  
  /* reinizializzo passi */
  passi = 0;



  /******* calcolo complessità media e mediana *******/
  /* generazione casuale id e perc */
  for (i = 0;
       i < 30;
       i ++)
  {

    id[i] = rand() % 10000 + 1;
    
    perc[i] = rand() % 100 + 1;
  }

  /* calcolo passi base quicksort 1 id */
  quicksort(perc,
	    0,
	    0,
	    id,
	    &passi);
 
  /* calcolo passi base per la media */
  for (i = 0;
       i < 1;
       i++)
      {
        /* calcolo passi per controllo */
        passi = passi + 1;
 
        /* calcolo passi per la somma delle percentuali */ 
        passi = passi + 1;       

        /* calcolo passi per incremento */
        passi = passi + 1;

      }

  /* calcolo passi inizializzazione e ultimo confronto */      
  passi = (passi + 1 + 1) + 1;

  /* calcolo passi trasformazione numero_studenti in float */
  passi = passi + 1;

  /* calcolo passi operazione media */
  passi = passi + 1;
 

  /* calcolo passi base per la mediana */
  /* calcolo passi assegnazione resto */
  passi = passi + 1;
  resto = 1 % 2;

  if (resto == 1)
  {
    /* calcolo passi mediana */
    passi = passi + 1;
  }
  else
  {
    /* calcolo passi mediana */
    passi = passi + 1;
    passi = passi + 1;
    passi = passi + 1;
  }
  
  /* calcolo passi confronto */
  passi = passi + 1;

  
  printf("I passi effettuati per la media e la mediana di 1 id sono : %d.\n",
         passi);

  /* reinizializzo passi */
  passi = 0;



  /* generazione casuale id e perc */
  for (i = 0;
       i < 30;
       i ++)
  {

    id[i] = rand() % 10000 + 1;
    
    perc[i] = rand() % 100 + 1;
  }

  /* calcolo passi base quicksort 1 id */
  quicksort(perc,
	    0,
	    9,
	    id,
	    &passi);
 
  /* calcolo passi base per la media */
  for (i = 0;
       i < 10;
       i++)
      {
        /* calcolo passi per controllo */
        passi = passi + 1;
 
        /* calcolo passi per la somma delle percentuali */ 
        passi = passi + 1;       

        /* calcolo passi per incremento */
        passi = passi + 1;

      }

  /* calcolo passi inizializzazione e ultimo confronto */      
  passi = (passi + 1 + 1) + 1;

  /* calcolo passi trasformazione numero_studenti in float */
  passi = passi + 1;

  /* calcolo passi operazione media */
  passi = passi + 1;
 

  /* calcolo passi base per la mediana */
  /* calcolo passi assegnazione resto */
  passi = passi + 1;
  resto = 10 % 2;

  if (resto == 1)
  {
    /* calcolo passi mediana */
    passi = passi + 1;
  }
  else
  {
    /* calcolo passi mediana */
    passi = passi + 1;
    passi = passi + 1;
    passi = passi + 1;
  }
  
  /* calcolo passi confronto */
  passi = passi + 1;

 
  printf("I passi effettuati per la media e la mediana di 10 id sono : %d.\n",
         passi);
  
   /* reinizializzo passi */
  passi = 0;

  
  /* generazione casuale id e perc */
  for (i = 0;
       i < 30;
       i ++)
  {

    id[i] = rand() % 10000 + 1;
    
    perc[i] = rand() % 100 + 1;
  }

  /* calcolo passi base quicksort 1 id */
  quicksort(perc,
	    0,
	    19,
	    id,
	    &passi);
 
  /* calcolo passi base per la media */
  for (i = 0;
       i < 20;
       i++)
      {
        /* calcolo passi per controllo */
        passi = passi + 1;
 
        /* calcolo passi per la somma delle percentuali */ 
        passi = passi + 1;       

        /* calcolo passi per incremento */
        passi = passi + 1;

      }

  /* calcolo passi inizializzazione e ultimo confronto */      
  passi = (passi + 1 + 1) + 1;

  /* calcolo passi trasformazione numero_studenti in float */
  passi = passi + 1;

  /* calcolo passi operazione media */
  passi = passi + 1;
 

  /* calcolo passi base per la mediana */
  /* calcolo passi assegnazione resto */
  passi = passi + 1;
  resto = 20 % 2;

  if (resto == 1)
  {
    /* calcolo passi mediana */
    passi = passi + 1;
  }
  else
  {
    /* calcolo passi mediana */
    passi = passi + 1;
    passi = passi + 1;
    passi = passi + 1;
  }
  
  /* calcolo passi confronto */
  passi = passi + 1;

  printf("I passi effettuati per la media e la mediana di 20 id sono : %d.\n",
         passi);

  /* reinizializzo passi */
  passi = 0;
  
  
  /* generazione casuale id e perc */
  for (i = 0;
       i < 30;
       i ++)
  {

    id[i] = rand() % 10000 + 1;
    
    perc[i] = rand() % 100 + 1;
  }

  /* calcolo passi base quicksort 1 id */
  quicksort(perc,
	    0,
	    29,
	    id,
	    &passi);
 
  /* calcolo passi base per la media */
  for (i = 0;
       i < 30;
       i++)
      {
        /* calcolo passi per controllo */
        passi = passi + 1;
 
        /* calcolo passi per la somma delle percentuali */ 
        passi = passi + 1;       

        /* calcolo passi per incremento */
        passi = passi + 1;

      }

  /* calcolo passi inizializzazione e ultimo confronto */      
  passi = (passi + 1 + 1) + 1;

  /* calcolo passi trasformazione numero_studenti in float */
  passi = passi + 1;

  /* calcolo passi operazione media */
  passi = passi + 1;
 

  /* calcolo passi base per la mediana */
  /* calcolo passi assegnazione resto */
  passi = passi + 1;
  resto = 30 % 2;

  if (resto == 1)
  {
    /* calcolo passi mediana */
    passi = passi + 1;
  }
  else
  {
    /* calcolo passi mediana */
    passi = passi + 1;
    passi = passi + 1;
    passi = passi + 1;
  }
  
  /* calcolo passi confronto */
  passi = passi + 1;
  
  printf("I passi effettuati per la media e la mediana di 30 id sono : %d.\n",
         passi);

  /* reinizializzo passi */
  passi = 0;
  
  

}


/******************************/
/* definizione delle funzioni */
/******************************/


/* definizione della funzione necessaria al riordinamento degli
   array */
void quicksort(int *a_primario,
	       int sx,
	       int dx,
	       int *a_secondario,
	       int *passi)
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
    /* conto passi controllo */
    *passi = *passi + 1;

    while (a_primario[i] < pivot)
    {
      /* calcolo passi confronto */
      *passi = *passi + 1;

      i++;

      /* calcolo passi incremento i */
      *passi = *passi + 1;

    }
      
    /* calcolo passi ultimo controllo */
    *passi = *passi + 1;

      
    while (a_primario[j] > pivot)
    {
      /* calcolo passi confronto */
      *passi = *passi + 1;

      j--;
      
      /* calcolo passi decremento j */
      *passi = *passi + 1;

    }

    /* calcolo passi ultimo controllo */
    *passi = *passi + 1;

    if (i <= j)
    {

     
      if (i < j)
      { 
        /* scambio valori */
        tmp = a_primario[i];
	a_primario[i] = a_primario[j];
        a_primario[j] = tmp;
        
        /* calcolo passi scambio valori */
        *passi = *passi + 3;


        tmp = a_secondario[i];
	a_secondario[i] = a_secondario[j];
	a_secondario[j] = tmp;

        /* calcolo passi scambio valori */
        *passi = *passi + 3;

      }
      i++;
      j--;    
      
      /* calcolo passi incr. decr. i e j */
      *passi = *passi + 2;  
    }
     
    /* calcolo passi confronto 2 if */
    *passi = *passi + 2;


  }
  
  /* calcolo passi per inizializzazione + ultimo controllo */
  *passi = (*passi + 1 + 1 + 1) + 1; 

  /* ordina la prima e la terza parte se contenenti più di un elemento
     chiamando ricorsivamente quicksort */
  if  (sx < j)
  {
    quicksort(a_primario,
	      sx,
              j,
	      a_secondario,
	      passi);

    /* calcolo passi chiamata */
    *passi = *passi + 1;
  }

  if  (i < dx)
  {
    quicksort(a_primario,
 	      i,
	      dx,
	      a_secondario,
	      passi);

    /* calcolo passi chiamata */
    *passi = *passi + 1;
  }

  /* calcolo passi confronto 2 if */
    *passi = *passi + 2;
}

