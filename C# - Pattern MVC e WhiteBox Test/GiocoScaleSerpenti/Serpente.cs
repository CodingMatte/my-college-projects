using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GiocoScaleSerpenti
{
	//classe figlia di Casella
    class Serpente : Casella
    {
		public Serpente(int num_cas)
        {
            nome = "serpente";
            numero_casella = num_cas;
        }
	}
}
