
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GiocoScaleSerpenti
{
    class Mappa
    {
		//variabile statica, il numero del tabellone è sempre 50   
        const int n_caselle = 50;
       
		Random rnd = new Random();
        
		//inizializzo array di caselle 
		Casella[] caselle = new Casella[50];
        
        //metodo costruttore Mappa
        public Mappa()
        {
            Creazione();
        }

        //Metodo Creazione Mappa
        //Vincolo: dopo una casella Serpente o Scala deve essercene 3 vuote
        public void Creazione()
        {
			//come prima cosa, creiamo l'istanza Partenza nella posizione 0, 
			//e l'istanza Vittoria nella posizione 49
            for (int i = 0; i < n_caselle; i++)
            {
                if (i == 0)
                {
                    caselle[i] = new Partenza(i);
                 
                }
                else
                    if (i == 49)
                    {
                        caselle[i] = new Vittoria(i);
                    }
                    else
                    {
						//a Random inseriamo o la casella Vuota, o la Serpente o la Scala
                        int appoggio;
                        appoggio = rnd.Next(0, 3);
                        if (appoggio == 0)
                        {
                            caselle[i] = new Vuota(i);
                        }
                        else if (appoggio == 1)
                        {
                            caselle[i] = new Serpente(i);
                          
							// creo 3 caselle vuote
                            if (i < 46)
                            {
                                caselle[i + 1] = new Vuota(i + 1);
                                caselle[i + 2] = new Vuota(i + 2);
                                caselle[i + 3] = new Vuota(i + 3);
                                i = i + 3;
                            }
                        }
                        else
                        {
                            caselle[i] = new Scala(i);
                            
                            // creo 3 caselle vuote
                            if (i < 46)
                            {
                                caselle[i + 1] = new Vuota(i + 1);
                                caselle[i + 2] = new Vuota(i + 2);
                                caselle[i + 3] = new Vuota(i + 3);
                              
                                i = i + 3;
                            }

                        }

                    }
	        }
        }

		//metodo che restituisce il tipo di casella.
		//
        public Casella ControlloCaselle(int destinazione)
        {
			//inizializziamo un oggetto casella che ci servirà come appoggio
            Casella controllo;
            
			//in input la funzione acquisce il numero destinazione,
			//avviene il controllo e restituisce il tipo di casella
            controllo=caselle[destinazione];
            return controllo;
        }


	    //metodo che ci permette di validare la destinazione nel momento
		// in cui si supera la casella 49 o la 0
        public int validazione_destinazione(int destinazione)
        {
			//se superiamo la casella 49, dobbiamo calcolare l'avanzo e 
			//sottrarlo dalla casella 49
            if (destinazione >= 50)
            {
                destinazione = 49 - (destinazione - 49);
            }
			//se invece siamo sotto zero, basta cambiare di segno
		    else if (destinazione < 0)
            {
                destinazione = -(destinazione);
            }

            return destinazione;
        }
       


    }
}
