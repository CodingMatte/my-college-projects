/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bopbop;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.Random;


public class SparaBolleHostClient extends Thread
{
    
  private int numero;
  private int attesa;
  private int dim_bolla;
  private int max_vel;
  
  BufferedImage img_bollablu;
  BufferedImage img_bollanera;
  BufferedImage img_bollagialla;
  
  private Gioco main;
  private boolean spara;
  
  private ArrayList<Bolla> bolle;
  private Random rnd;
  
  
  public SparaBolleHostClient(BufferedImage imgblu, BufferedImage imgnera, BufferedImage imggialla,int numero, int attesa, Gioco main)
  {
    this.img_bollablu = imgblu;
    this.img_bollanera= imgnera;
    this.img_bollagialla= imggialla;
    this.attesa = attesa;
    this.numero = numero;
    this.main = main;
    this.rnd = new Random();
    this.max_vel = 2;
    this.bolle = new ArrayList();
  }
  
  
  
  @Override
  public void run()
  {
    spara = true;
    while(spara)
    {
      for(int i = 0; i < numero; i++)
      {
        dim_bolla = this.rnd.nextInt(60) + 15;
        bolle.add(new BollaBlu(img_bollablu, 
                              dim_bolla, 
                              dim_bolla, 
                              this.rnd.nextInt(main.getLarghezza()-dim_bolla),
                              -(dim_bolla + 10), 
                              this.rnd.nextInt(max_vel) + 2, 
                              main));
        
        if(i%10==0)
        {
         bolle.add(new BollaNera(img_bollanera, 
                                 dim_bolla, 
                                 dim_bolla, 
                                 this.rnd.nextInt(main.getLarghezza()-dim_bolla),
                                 -(dim_bolla + 10), 
                                 this.rnd.nextInt(max_vel) + 2, 
                                 main));
        }
        
                
       
        bolle.add(new BollaGialla(img_bollagialla, 
                                 dim_bolla, 
                                 dim_bolla, 
                                 this.rnd.nextInt(main.getLarghezza()-dim_bolla),
                                 -(dim_bolla + 10), 
                                 this.rnd.nextInt(max_vel) + 2, 
                                 main));
        
        
        
        
      }
      try
      {
        Thread.sleep(attesa);
      } catch (InterruptedException ex)
      {
        System.out.println("eccezione nello sleep di spara Bolle " + ex);
      }
    }
  }
  
  
  public void disegna(Graphics g)
  {
    for(int i = 0; i < bolle.size(); i++)
    {
      Bolla temp = bolle.get(i);
      temp.disegna(g);
      
    }
  }
  
  public ArrayList getBolle()
  {
    return bolle;
  }
  
}
 

