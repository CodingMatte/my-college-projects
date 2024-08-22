using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GiocoScaleSerpenti
{
    class WhiteBox
    {
        int test_serpente = -2;
        int test_scala = 52;
        Mappa mappa_test = new Mappa();

        public void test_destinazione()
        {

          Console.WriteLine("MODALITA' TEST:\n" +
                            "In questa modalità verrà testata la funzione che\n" +
                            "valida la destinazione di un giocatore\n" +
                            "\n" + 
                            "Nel caso in cui ci si trovi in una delle\n" +
                            "caselle iniziali, e si prenda una casella serpente\n" +
                            "c'è la possibilità di tornare indietro di più caselle\n" +
                            "di quante ne siano state percorse fin'ora.\n" + 
                            "ESEMPIO: ammettiamo il caso in cui ci troviamo nella\n" +
                            "casella 4, ed in questa vi sia un serpente. Se dal dado\n" +
                            "si estraesse il numero 5 i passi del giocatore dovrebbero\n" +
                            "essere i seguenti : 4 -> 3 -> 2 -> 1 -> 2 -> 3.\n" +
                            "E non: 4 -> 3 -> 2 -> 1 -> 0 -> -1.\n" );

          Console.WriteLine("\nValidazione Serpente iniziale:\n" +
                            "Input destinazione: -2\n" +
                            "Usciti dalla funzione la destinazione\n" +  
                            "corretta dovrebbe essere 2.\n");
        
          test_serpente = mappa_test.validazione_destinazione(test_serpente);

          if (test_serpente == 2)
          {
              Console.WriteLine("\nESITO: ok");
          }
          else
          {
              Console.WriteLine("\nESITO: test non superato");
          }

          Console.WriteLine("\n\nValidazione Scala finale:\n" +
                            "Input destinazione: 52\n" +
                            "Usciti dalla funzione la destinazione\n" +  
                            "corretta dovrebbe essere 46.\n");


          test_scala = mappa_test.validazione_destinazione(test_scala);

          if (test_scala == 46)
          {
              Console.WriteLine("\nESITO: ok");
          }
          else
          {
              Console.WriteLine("\nESITO: test non superato");
          }

          Console.WriteLine("\n\n\nFINE TEST");

          Console.ReadLine();
          
        }

    }
}
