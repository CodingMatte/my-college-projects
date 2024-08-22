
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GiocoScaleSerpenti
{
    class Giocatore
    {
		//variabili globali
        private string nome;
        public int NumeroUscito;
        public int Posizione;

		//costruttore
        public Giocatore()
        {
            Posizione = 0;
        }

        //assegna il nome 
        public void setNome(string nome_immesso)
        {
          nome = nome_immesso ;
        }
        
        //restituisce il nome
        public string getNome()
        {
            return nome;
        }

        //assegna il numero uscito dal dado in fase di ordine dei giocatori 
        public void setNumeroUscito(int num_uscito)
        {
            NumeroUscito = num_uscito;
        }

        //restituisce il numero uscito dal dado in fase di ordine dei giocatori 
        public int getNumeroUscito() 
        {
            return NumeroUscito;
        }

        //assegna la posizione attuale 
        public void setPosizione(int posizione)
        {
          Posizione=posizione;
        }

        //restituisce la posizione attuale
        public int getPosizione()
        {
            return Posizione;
        }


    }
}
