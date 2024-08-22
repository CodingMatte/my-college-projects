using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace GiocoScaleSerpenti
{
   class Gioco
   {
       //creazione mappa di gioco Random,
       //ad ogni esecuzione del programma verrà creata una nuova mappa
       static Mappa mappa = new Mappa();
	   
       //variabili globali
       static int n_giocatori;
       const int GIOC_MAX = 4;
       
       //creo l'array giocatori dove verranno inserite tutte le informazioni riguardanti i giocatori
       static Giocatore[] giocatori = new Giocatore[GIOC_MAX];

	   //costruttore
       public Gioco(int n_g, Giocatore[] gio)
       {   
           //inserisco i parametri passati nelle variabili create 
           n_giocatori = n_g;
           for (int i = 0; i < n_giocatori; i++)
           {
               giocatori[i]=gio[i];


           }

			 //chiamo metodo per iniziare turno di gioco
             ControlloCaselleGioco();

           }

       //metodo iniziare con i turni di gioco
       static void ControlloCaselleGioco()
       {
           int destinazione;
           int posizione_attuale;
           int tiro_dado;
           Dado dado_partita = new Dado();



			//ogni giocatore tira il dado, e avanza di posizione a seconda del punteggio totalizzato
           for (int i = 0; i < n_giocatori; i++)
           {

               //prendo la posizione attuale
               //inizialmente sarà settata a 0
               posizione_attuale = giocatori[i].getPosizione();

               tiro_dado = 0;

               //giocatore i lancia il dado
               tiro_dado = dado_partita.Lancio();
               Console.WriteLine(giocatori[i].getNome() + " ha lanciato:  " + tiro_dado);

               //destinazione raggiunta
               destinazione = posizione_attuale + tiro_dado;
			
			   //creo istanza Giocatore per usarla come appoggio
               Giocatore attuale = new Giocatore();
               attuale = giocatori[i];


               //caselle <0 e >49 non esistono
               if (destinazione < 0)
               {
                   destinazione = -destinazione;
               }

               if (destinazione >= 50)
               {
                   destinazione = 49 - (destinazione - 49);
               }

               //una volta raggiunta la destinazione devo controllore dove il giocatore è capitato
               ControlloDestinazione(destinazione, attuale);

               if (destinazione == 49)
               {
                   //se c'è un vincitore, usciamo dal for
                   i = n_giocatori;
               }


               //facciamo ripartire il turno se nessuno ha vinto
               //quindi se non c'è vincitore, settiamo i a -1
               if (i == (n_giocatori - 1))
               {
                   i = -1;
                   for (int j = 0; j < n_giocatori; j++)
                   {
                       if (j == 0)
                       {
                           Console.WriteLine("\n\r");
                           Console.WriteLine("_______________________________________________________");
                       }
                       Console.WriteLine(giocatori[j].getNome() + " è in posizione:  " + giocatori[j].getPosizione());
                       if (j == n_giocatori - 1)
                           Console.WriteLine("_______________________________________________________");
                   }
               }

               Console.ReadLine();

           }
       }


	   //metodo per controllare la casella destinazione
       static void ControlloDestinazione(int destinazione, Giocatore attuale)
       {
           //metto la cassella su una variabile di controllo
           Dado dado_partita = new Dado();
           Casella controllo;

		   //richiamo il metodo ControlloCaselle per scoprire su quale casella 
			//il giocatore è capitato
           controllo = mappa.ControlloCaselle(destinazione);


           //inizio fase dei controlli
           if (controllo.GetType().FullName == ("GiocoScaleSerpenti.Vuota"))
           {
               Console.WriteLine("Destinazione--> " + destinazione + ": --> Casella Vuota");
			   //se la casella è vuota, setto la posizione destinazione come attuale ed esco dal ciclo
               attuale.setPosizione(destinazione);


           }
           else if (controllo.GetType().FullName == ("GiocoScaleSerpenti.Serpente"))
           {
               Console.WriteLine("Destinazione--> " + destinazione + ": --> Casella Serpente\n\r " + attuale.getNome() + " deve rilanciare il dado");
			   //se la casella è un serpente, rilancio il dado e ritorno indietro
               int ripiego;
               ripiego = dado_partita.Lancio();
               Console.WriteLine(attuale.getNome() + " ha lanciato:  " + ripiego);

			   //destinazione dopo il lancio
               destinazione = destinazione - ripiego;

			   //validazione destinazione
               destinazione = mappa.validazione_destinazione(destinazione);

	           //setto la destinazione modificata come posizione attuale
               attuale.setPosizione(destinazione);
               //ricontrollo la posizione
               //ricorsione di funzione
               ControlloDestinazione(destinazione, attuale);

           }
	       else if (controllo.GetType().FullName == ("GiocoScaleSerpenti.Scala"))
           {
               Console.WriteLine("Destinazione--> " + destinazione + ": --> Casella Scala\n\r " + attuale.getNome() + " deve lanciare il dado:");
				//se è una Scala, ritiro il dado
               int aumento;
               aumento = dado_partita.Lancio();
               Console.WriteLine(attuale.getNome() + " ha lanciato:  " + aumento);

				//lpa destinazione viene aumentata del risultato del lancio
               destinazione = destinazione + aumento;

				//validazione destinazione
               destinazione = mappa.validazione_destinazione(destinazione);

			   //ricontrollo la posizione
			   //ricorsione di funzione
		       ControlloDestinazione(destinazione, attuale);
           }
           else if (controllo.GetType().FullName == ("GiocoScaleSerpenti.Vittoria"))
           {
               Console.WriteLine(attuale.getNome() + " ha VINTO!!!!");
               Console.WriteLine("FINE GIOCO");

           }
           else if (controllo.GetType().FullName == ("GiocoScaleSerpenti.Partenza"))
           {
               Console.WriteLine("Destinazione--> " + destinazione + ": --> Casella Partenza");

               attuale.setPosizione(destinazione);
           }
       }

     }
}
