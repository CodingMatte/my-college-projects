using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GiocoScaleSerpenti
{
    class Dado
    {
		//variabili globali
        private int massimo;
        private int minimo;
        private int estratto;
        private Random random = new Random();

        // costruttore di dado
        public Dado()
        {
            massimo = 6;
            minimo = 1;
        }

		//metodo che permette di prelevare un numero random dentro certi 
		//valori (minimo e massimo) 
        public int Lancio()
        {
            estratto = random.Next(minimo, massimo);
            return estratto;
        }

    }
}
