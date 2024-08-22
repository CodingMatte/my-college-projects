
package bopbop;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.util.logging.Level;
import java.util.logging.Logger;


public class Cesto extends Thread
{
  private int x;
  private int y;
  private int larghezza;
  private int altezza;
  private boolean attivo;
  
  BufferedImage img_cesto;
  
  public Cesto(BufferedImage image, int larghezza, int altezza, int x, int y)
  {
    this.x = x;
    this.y = y;
    this.altezza = altezza;
    this.larghezza = larghezza;
    this.img_cesto = image;
    this.attivo = true;
    
  }

  @Override
  public void run()
  {
    attivo = true;
    
    while(attivo)
    {
      aggiorna();
      
      try
      {
        Thread.sleep(10);
      } catch (InterruptedException ex)
      {
        Logger.getLogger(Cesto.class.getName()).log(Level.SEVERE, null, ex);
      }
    }
  }
  
  public void aggiorna()
  {
    // si muove
    x++; 
  }
  
  
  
  public void disegna(Graphics g)
  {
    g.drawImage(img_cesto, x, y, larghezza, altezza, null);
  }
  
  
  public boolean isAttivo()
  {
    return attivo;
  }
  
  public void setAttivo(boolean valore)
  {
    this.attivo = valore;
  }
  
  
  public void setX(int valore)
  {
    this.x = valore;
  }
  
  public void setY(int valore)
  {
    this.y = valore;
  }
  
  public void setLarghezza(int valore)
  {
    this.larghezza = valore;
  }
  
  public void setAltezza(int valore)
  {
    this.altezza = valore;
  }
  
  public int getX()
  {
    return x;
  }
  
  public int getY()
  {
    return y;
  }
  
  public int getLarghezza()
  {
    return larghezza;
  }
  
  public int getAltezza()
  {
    return altezza;
  }
  
}
