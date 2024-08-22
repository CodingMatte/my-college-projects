using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GiocoScaleSerpenti
{
    class Scala : Casella
    {
		//classe figlia di Casella
        public Scala(int num_cas)
        {
            nome = "scala";
            numero_casella = num_cas;
        }
	}
}

