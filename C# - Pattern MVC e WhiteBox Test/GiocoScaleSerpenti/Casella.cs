using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GiocoScaleSerpenti
{
	//classe madre delle caselle:
	//Vuota, Serpente, Partenza, Vittoria e Scala
    abstract class Casella
    {
        protected Random rnd;
        protected string nome;
        protected int numero_casella;
       
     }
}

