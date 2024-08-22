using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GiocoScaleSerpenti
{
    class Interfaccia
    {
        //inizializzazione variabili globali
        static int n_giocatori;
        const int GIOC_MAX = 4;
        public bool boolvittoria = false;

        //variabile di controllo per fase test
        static int t = 0;

        //creo l'array giocatori dove verranno inserite tutte le informazioni riguardanti i giocatori
        static Giocatore[] giocatori = new Giocatore[GIOC_MAX];

        //main
        static void Main(string[] args)
        {
            //stampa a video istruzioni iniziali 
            Console.WriteLine("Progetto Ingegneria del Software");
            Console.WriteLine("Manoni Leonardo & Incicco Matteo");
            Console.WriteLine("Gioco delle Scale e dei Serpenti");
            Console.ReadLine();


            //Scelta numero giocatori, l'utente inserirà a video il numero dei giocatori
            //con validazione dati di input.
			//la variabile booleana serve per validare l'input
            bool validazione = true;

            while (validazione)
            {
                n_giocatori = ImmettiNumeroGiocatori();
                if (n_giocatori >= 2 && n_giocatori <= 4)
                {
                    validazione = false;
                }
            }

            //l'utente inserirà tutti i nomi dei giocatori
            //non c'è validazione, utilizziamo stringhe, è possibile inserire qualunque carattere
            t = ImmettiNomi(n_giocatori);

			//istruzioni per Test
            if (t == 1)
            {
                WhiteBox wb = new WhiteBox();
                wb.test_destinazione();
			}
            else
            {
                //ordine di tiro
                //tutti i giocatori tirano il dado,
                //a seconda dei punteggi si stabilisce l'ordine di gioco
                OrdineTiro();

                //inizio del gioco e dei turni di gioco
                InizioGioco();
            }

	    }


        //FUNZIONI

        //funzione che acquisisce da tastiera il numero di giocatori
        static int ImmettiNumeroGiocatori()
        {
            System.Console.WriteLine("Immetti numero giocatori (Da 2 a 4):");

			//acquisizione
            string stringa_appoggio = Console.ReadLine();
			//c# acquisisce solo stringhe, convertiamo la stringa in int
            Int32.TryParse(stringa_appoggio, out n_giocatori);

            return n_giocatori;
        }


        //acquisizione dei nomi dei giocatori
        //questa funzione permette all'utente di inserire i nomi dei giocatori
        static int ImmettiNomi(int n_giocatori)
        {
            string nome_immesso;
            int test = 0;


            for (int i = 0; i < n_giocatori; i++)
            {
                Console.WriteLine("Immetti nome giocatore numero: " + (i + 1));
                nome_immesso = Console.ReadLine();
				//istruzione per test
                if (nome_immesso == "test")
                {
                    i = 5;
                    test = 1;
                }
                else
                { 
					//creazioni istanze giocatori 
                    giocatori[i] = new Giocatore();
					//settiamo il nome ad ogni giocatore
					//richiamando setNome
                    giocatori[i].setNome(nome_immesso);
                }

            }

            return test;

        }


        //funzione che ordina i giocatori in base al punteggio del dado
        //tutti i giocatori tirano il dado, e in base al loro punteggio 
        //avranno la posizione di tiro
        static void OrdineTiro()
        {
            Console.WriteLine();
            Console.WriteLine("TUTTI I GIOCATORI TIRANO IL DADO");
            Console.WriteLine("L'ORDINE DI GIOCO VERRA' STABILITO \r\nIN ORDINE DECRESCENTE A SECONDA\r\n DEL PUNTEGGIO TOTALIZZATO ");
            Console.ReadLine();

            //istituisco l'ordine di gioco facendo tirare ad ogni giocatore il dado
            for (int i = 0; i < n_giocatori; i++)
            {
				//istanza dado per richiamare il metodo lancio
                Dado dado_ordine = new Dado();
                int nOrdineUscito;

                //tiro dado
                nOrdineUscito = dado_ordine.Lancio();

                //setto il numero uscito con l'array giocatori
                giocatori[i].setNumeroUscito(nOrdineUscito);
                Console.WriteLine(giocatori[i].getNome() + " ha totalizzato " + nOrdineUscito);
                Console.ReadLine();


            }


            //insertsort
            //ordino l'array giocatori in ordine decrescente
            Giocatore appoggio = new Giocatore();
            for (int i = 1; i < n_giocatori; ++i)
            {
                appoggio = giocatori[i];
                int appoggio_numero = appoggio.getNumeroUscito();
                int j = (i - 1);

                while (j >= 0 && appoggio_numero > giocatori[j].getNumeroUscito())
                {

                    giocatori[j + 1] = giocatori[j];
                    j--;
                }

                giocatori[j + 1] = appoggio;

            }//fine algoritmo insertsort

            Console.WriteLine("ORDINE DI GIOCO");

			//stampa a video dell'ordine di gioco
            for (int i = 0; i < n_giocatori; i++)
            {
                Console.WriteLine(giocatori[i].getNome() + "   " + giocatori[i].getNumeroUscito());
            }

            Console.ReadLine();
        }



        //inizio Gioco
        static void InizioGioco()
        {
			//creo istanza gioco passando per paramertro
			//il numero giocatori e  l'array contemente i giocatori
            new Gioco(n_giocatori, giocatori);
           
        }

       

    }


}