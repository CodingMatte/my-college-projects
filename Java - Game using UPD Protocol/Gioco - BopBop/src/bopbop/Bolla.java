
package bopbop;

import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.util.logging.Level;
import java.util.logging.Logger;


public class Bolla extends Thread
{
  private int altezza;
  private int larghezza;
  private int x;
  private int y;
  private int velocita;
  private boolean attivo;
  private Gioco main;
  
  BufferedImage img_bolla;
  
  public Bolla(BufferedImage image, int alt, int larg, int x, int y, int velocita, Gioco main)
  {
    this.x = x;
    this.y = y;
    this.altezza = alt;
    this.larghezza = larg;
    this.img_bolla = image;
    this.attivo = true;
    this.velocita = velocita;
    this.start();
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
        Thread.sleep(20);
      } catch (InterruptedException ex)
      {
        Logger.getLogger(Bolla.class.getName()).log(Level.SEVERE, null, ex);
      }
    }
  }

  private void aggiorna()
  {
    y += velocita;
  }

  public void disegna(Graphics g)
  {
    g.drawImage(img_bolla, x, y, larghezza, altezza, main);
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
  
  public Rectangle getBordi()
  {
    return new Rectangle(x, y, larghezza, altezza);
  }
}
