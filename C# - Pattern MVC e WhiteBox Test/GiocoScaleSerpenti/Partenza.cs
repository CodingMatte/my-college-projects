using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GiocoScaleSerpenti
{
    class Partenza : Casella
    {
		//classe figlia di Casella
        public Partenza(int num_cas)
        {
            nome = "Partenza";
            numero_casella = num_cas;
        }
	}
}
