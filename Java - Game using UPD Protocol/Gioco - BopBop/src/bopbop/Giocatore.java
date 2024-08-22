
package bopbop;

import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;


public class Giocatore
{
  private int x;
  private int y;
  private int larghezza;
  private int altezza;
  private final int velocità = 10;
  public int punteggio;
  public int num;
  BufferedImage img_cesto_giocatore;
  
  Gioco main;
  
  
  public Giocatore(BufferedImage image, int x, int larghezza, int altezza, Gioco main)
  {
    this.x = x;
    this.altezza = altezza;
    this.larghezza = larghezza;
    this.img_cesto_giocatore = image;
    this.y = 620;
    this.main = main;
    this.punteggio = 0;
  }
  
  public void disegna(Graphics g)
  {
    g.drawImage(img_cesto_giocatore, x, y, larghezza, altezza, main);
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
  
  
  
  public void spostaDestra()
  {
    if(x + larghezza < main.getLarghezza())
    {
      x += velocità;
    }
  }
  
  public void spostaSinistra()
  {
    if(x > 0)
    {
      x -= velocità;
    }
  }
  
  public Rectangle getBordi()
  {
    return new Rectangle(x, y, larghezza, altezza);
  }
}
