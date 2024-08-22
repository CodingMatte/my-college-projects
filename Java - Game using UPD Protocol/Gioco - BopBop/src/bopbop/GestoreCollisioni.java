
package bopbop;


public class GestoreCollisioni
{
  public static boolean controllaCollisioni(Giocatore cesto, Bolla bolla)
  {
    if(cesto.getBordi().intersects(bolla.getBordi()))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}
