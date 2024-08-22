using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GiocoScaleSerpenti
{
	//classe figlia di Casella
    class Vittoria : Casella
    {
        public Vittoria(int num_cas)
        {
            nome = "Vittoria";
            numero_casella = num_cas;
        }
	}
}