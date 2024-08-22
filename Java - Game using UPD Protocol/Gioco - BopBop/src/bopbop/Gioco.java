
package bopbop;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferStrategy;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;


public class Gioco extends Canvas implements Runnable, KeyListener, MouseMotionListener
{
  private int fontsize = 20;
  
  private static final int larghezza = 1280;
  private static final int altezza = 720;
  private static final String nome_gioco = "BopBop";
    
  BufferedImage haiperso = null;
  BufferedImage haivinto = null;
  BufferedImage sfondo = null;
  BufferedImage cesto = null;
  BufferedImage bollablu = null;
  BufferedImage bollanera = null;
  BufferedImage bollagialla = null;
  
  private boolean giocoAttivo;
  private Cesto cesto_per_bolle;
  private Giocatore giocatore;
  private SparaBolle spara_bolle;
  private SparaBolleHostClient spara_bolle_host_client;
  

  
  ClientUDP myclient;
  ServerUDP myhost;
  
  int temp = 0;
  int punteggio = 0;
  int punteggio_avversario = 0;
  Boolean partito = false;
  
  public Gioco(ClientUDP myclient, ServerUDP myhost)
  {
    this.myclient = myclient;
    this.myhost = myhost;
    
    caricaRisorse();
    inizia_gioco();
    
    // setto le impostazioni per la finestra di gioco
    JFrame finestra_gioco = new JFrame(nome_gioco);
    Dimension dimensione_finestra = new Dimension(larghezza, altezza);
    finestra_gioco.setPreferredSize(dimensione_finestra);
    finestra_gioco.setMaximumSize(dimensione_finestra);
    finestra_gioco.setResizable(false);
    
    finestra_gioco.add(this);
    finestra_gioco.addKeyListener(this);
    this.addMouseMotionListener(this);
    
    finestra_gioco.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    finestra_gioco.pack();
    finestra_gioco.setVisible(true);
    
    
    Thread thread_gioco = new Thread(this);
    thread_gioco.start();
    
  }
  
  
  private void inizia_gioco()
  {
    giocatore = new Giocatore(cesto, 10, 200, 23, this);
    spara_bolle = new SparaBolle(bollablu,bollanera, 1, 1500, this);
    spara_bolle.start();
    spara_bolle_host_client= new SparaBolleHostClient(bollablu, bollanera, bollagialla,1,1500,this);
    spara_bolle_host_client.start();
    
  }
  
  private void caricaRisorse()
  {
    CaricatoreImmagini loader = new CaricatoreImmagini();
    
    //carico immagini dalla cartella immagini
    haiperso = loader.caricaImmagini("/immagini/haiperso.png");
    haivinto = loader.caricaImmagini("/immagini/haivinto.png");
    sfondo = loader.caricaImmagini("/immagini/sfondo.png");
    cesto = loader.caricaImmagini("/immagini/cesto.png");
    bollablu = loader.caricaImmagini("/immagini/bolla.png");
    bollanera = loader.caricaImmagini("/immagini/bollanera.png");
    bollagialla = loader.caricaImmagini("/immagini/bollagialla.png");
    
    
    System.out.println("Risorse caricate!");
 
  }
  
  
   
  private void disegna_coordinate()
  {
    BufferStrategy buffer = this.getBufferStrategy();
    if(buffer == null)
    {
      createBufferStrategy(2);
      return;
    }
    
    Graphics g = buffer.getDrawGraphics();
    
    g.setFont(new Font("Arial", Font.BOLD, fontsize));
    g.setColor(Color.red);
    
    g.drawImage(sfondo, 0, 0, larghezza, altezza, this);
    g.drawString("IP: " + myhost.get_ip() + " PORTA: " + myhost.get_porta(), 100, 100);
  
    
    g.dispose();
    buffer.show();
  }

  
  
  private void disegna()
  {
    BufferStrategy buffer = this.getBufferStrategy();
    if(buffer == null)
    {
      createBufferStrategy(2);
      return;
    }
    
    Graphics g = buffer.getDrawGraphics();
    g.setFont(new Font("Arial", Font.BOLD, fontsize));
    g.setColor(Color.red);
    
    
    g.drawImage(sfondo, 0, 0, larghezza, altezza, this);
    
    //cesto_per_bolle.disegna(g);
    giocatore.disegna(g);
    spara_bolle.disegna(g);
    
    g.drawString("Punteggio: " + this.punteggio, 50, 50);
    
    g.dispose();
    buffer.show();
  }
  
  private void disegna_client()
  {
    BufferStrategy buffer = this.getBufferStrategy();
    if(buffer == null)
    {
      createBufferStrategy(2);
      return;
    }
    
    Graphics g = buffer.getDrawGraphics();
    g.setFont(new Font("Arial", Font.BOLD, fontsize));
    g.setColor(Color.red);
    
    
    g.drawImage(sfondo, 0, 0, larghezza, altezza, this);
    

    giocatore.disegna(g);
    spara_bolle_host_client.disegna(g);
    
    g.drawString("Punteggio: " + this.punteggio, 50, 50);
    g.drawString("CLIENT", 500, 50);
    // DISEGNO IL PUNTEGGIO AVVERSARIO
    g.drawString("Punteggio avversario "+" " + this.punteggio_avversario, 1000, 50); 
    
    g.dispose();
    buffer.show();
  }

  
  private void disegna_host()
  {
    BufferStrategy buffer = this.getBufferStrategy();
    if(buffer == null)
    {
      createBufferStrategy(2);
      return;
    }
    
    Graphics g = buffer.getDrawGraphics();
    g.setFont(new Font("Arial", Font.BOLD, fontsize));
    g.setColor(Color.red);
    
    
    g.drawImage(sfondo, 0, 0, larghezza, altezza, this);
    
    giocatore.disegna(g);
    spara_bolle_host_client.disegna(g);
    
    g.drawString("Punteggio: " + this.punteggio, 50, 50);
    
    // DISEGNO IL PUNTEGGIO AVVERSARIO
    g.drawString("Punteggio avversario "+" " + this.punteggio_avversario, 1000, 50); 
    
    g.dispose();
    buffer.show();
  }
  
  
  
  private void disegna_vinto()
  {
    BufferStrategy buffer = this.getBufferStrategy();
    if(buffer == null)
    {
      createBufferStrategy(2);
      return;
    }
    
    Graphics g = buffer.getDrawGraphics();
    
    g.drawImage(haivinto, 0, 0, larghezza, altezza, this);
    
    
    g.dispose();
    buffer.show();
  }
  
  
  
  private void disegna_perso()
  {
    BufferStrategy buffer = this.getBufferStrategy();
    if(buffer == null)
    {
      createBufferStrategy(2);
      return;
    }
    
    Graphics g = buffer.getDrawGraphics();
    
    g.drawImage(haiperso, 0, 0, larghezza, altezza, this);
    
    
    g.dispose();
    buffer.show();
  }
  
  private void aggiorna()
  {
    ArrayList<Bolla> bolle = spara_bolle.getBolle();
    for(Bolla b : bolle)
    {
      if (GestoreCollisioni.controllaCollisioni(giocatore, b))
      {
        System.out.println(b.getClass());
        bolle.remove(b);
        //quando rimuove un oggetto ferma tutto il ciclo for
        if(b instanceof BollaNera){
        this.punteggio--;
        }
        
        if(b instanceof BollaBlu){
        this.punteggio++;
        }
        
        
        
        Sounds.SCOPPIA.stop();
        Sounds.SCOPPIA.play();
        
        break;
      }
    }
  }
   
  private void aggiorna_client() throws IOException
  {
    ArrayList<Bolla> bolle = spara_bolle_host_client.getBolle();
    for(Bolla b : bolle)
    {
      if (GestoreCollisioni.controllaCollisioni(giocatore, b))
      {
        bolle.remove(b);
        
        // quando rimuove un oggetto ferma tutto il ciclo for
        if(b instanceof BollaNera)
        {
          this.punteggio --;
          this.myclient.invia_punteggio(this.punteggio);
        }
        
        
        if(b instanceof BollaBlu)
        {
          this.punteggio ++;
          this.myclient.invia_punteggio(this.punteggio);
        }
        
           
        if(b instanceof BollaGialla)
        {
          // invio 8888 così sà che deve detrarre punti
          this.myclient.invia_punteggio(8888); 
        }
           
           

        
       
        Sounds.SCOPPIA.stop();
        Sounds.SCOPPIA.play();
        
        break;
      }
    }
  }
  
  private void aggiorna_host() throws IOException
  {
    ArrayList<Bolla> bolle = spara_bolle_host_client.getBolle();
    for(Bolla b : bolle)
    {
      
      if (GestoreCollisioni.controllaCollisioni(giocatore, b))
      {
        bolle.remove(b);
        
        
        // quando rimuove un oggetto ferma tutto il ciclo for
        if(b instanceof BollaNera)
        {
          this.punteggio --;
          this.myhost.invia_punteggio(this.punteggio);      
        }
        
        if(b instanceof BollaBlu)
        {
          this.punteggio ++;
          this.myhost.invia_punteggio(this.punteggio);
        }
        
        if(b instanceof BollaGialla)
        {
          // invio 8888 così sà che deve detrarre punti
          this.myhost.invia_punteggio(8888);         
        }
        
        
        // invio il punteggo al server tramine una funzione definita nel client
        
        
        
        Sounds.SCOPPIA.stop();
        Sounds.SCOPPIA.play();
        
        break;
      }
    }
  }
   
   
  @Override
  public void run()
  {
    giocoAttivo = true;
    
    // se è diverso da null vuol dire che sto esguendo come host
    if(myhost != null)
    {
      while(giocoAttivo)
      {
        // controllo sul flag, se falso vuol dire che il client non si è connesso e,
        // di conseguenza, visualizzerà soltanto le sue coordinate.
        if (partito == false)
        {
          disegna_coordinate();
        }
        // altrimenti se il flag è vero vuol dire che il client si è sinconizzato e 
        // che può partire il gioco vero e proprio
        else
        {
          if (this.punteggio >= 50)
          {
            // ho vinto quindi stampo la vittoria
            disegna_vinto();
          }
          else if (this.punteggio_avversario >= 50)
          {
            // ho perso quindi stampo la perdita
            disegna_perso();
          }
          else
          {
            try
            {
              aggiorna_host();          
            } catch (IOException ex)
            {
              System.out.println("Errore nell'aggiorna_host" + ex);
            }
            disegna_host();
          }
        }  
      }
    }
    // se è diverso da null vuol dire che sto eseguendo come client
    else if(myclient != null)
    {
      while(giocoAttivo)
      {
        
        if (this.punteggio >= 50)
        {
          // ho vinto quindi stampo la vittoria
          disegna_vinto();
        }
        else if (this.punteggio_avversario >= 50)
        {
          // ho perso quindi stampo la perdita
          disegna_perso();
        }
        else
        {        
          try
          {
            aggiorna_client();
          } catch (IOException ex)
          {
            System.out.println("Errore nell'aggiorna_client" + ex);
          }
          disegna_client();
        }
      }
    }
    // se è diverso da null vuol dire che sto eseguendo in SP
    else
    {
      while(giocoAttivo)
      {
        aggiorna();
        disegna();
      }
    }
    
    
  }

  
  public int getLarghezza()
  {
    return larghezza;
  }
  
  public int getAltezza()
  {
    return altezza;
  }
  
  
  // QUANDO SI PREME UN TASTO si attiva la funzione
  @Override
  public void keyPressed(KeyEvent e)
  {
    int keycode = e.getKeyCode();
    // ci può andare anche if
    switch(keycode)
    {
      case KeyEvent.VK_LEFT:
        giocatore.spostaSinistra();
        break;
        
      case KeyEvent.VK_RIGHT:
        giocatore.spostaDestra();
        break;
      
    }
  }

  // viene riconosciuto quando rilascio il tasto (cioè quando premo e rilascio)
  @Override
  public void keyTyped(KeyEvent e)
  {
    
  }
  
  // viene ricnosciuto SOLO quando si RILASCIA
  @Override
  public void keyReleased(KeyEvent e)
  {
    
  }

  // PER IL MOVIMENTO CON IL MOUSE
  @Override
  public void mouseDragged(MouseEvent e)
  {
    
  }

  
  // questo è quello che interessa a noi
  @Override
  public void mouseMoved(MouseEvent e)
  {
    // troviamo la posizione del mouse 
    int posizione = (e.getPoint().x) - (giocatore.getLarghezza()/2);
    
    if (posizione >= 0 && posizione + giocatore.getLarghezza() <= larghezza)
    {      
      giocatore.setX(posizione);
    }
    
  }
 

  public void aggiorna_punteggio(String nuovo_punteggio) throws IOException
  {
    this.temp = Integer.parseInt(nuovo_punteggio);
    
    // se il messaggio ricevuto è uguale a 8888 allora vuol dire che devo detrarre punti al 
    // mio punteggio, altrimenti aggiorno il punteggio avversario
    if (this.temp == 8888)
    {
      this.punteggio = this.punteggio - 1;
      
      // invio il punteggio aggiornato
      if(this.myhost != null)
      {
        this.myhost.invia_punteggio(this.punteggio);
      }
      else
      {
        this.myclient.invia_punteggio(this.punteggio);
      }
      
    }
    else
    {
      this.punteggio_avversario = Integer.parseInt(nuovo_punteggio);
    }
  }
 
  
  
  public void parti()
  {
    partito = true; 
  }
}
