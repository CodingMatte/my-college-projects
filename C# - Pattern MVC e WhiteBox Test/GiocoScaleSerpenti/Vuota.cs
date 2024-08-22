using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GiocoScaleSerpenti
{	
	//classe figlia di casella
    class Vuota : Casella
    {
		public Vuota(int num_cas)
        {
            nome = "Vuota";
            numero_casella = num_cas;
        }
	}
}
