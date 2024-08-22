
package bopbop;

// importo i package necessari
import java.net.*;
import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;


public class ServerUDP extends Thread
{    
  public String client;
  int cont=0;
  DatagramSocket s, c;
  DatagramPacket recv, hi, per_client;
  Gioco gioco;
  int port;
  int portCLIENT = 30000;
  String server;
  
  
  //Creazione del pacchetto da inviare al CLIENT
  InetAddress addressCLIENT = null;
  
  public ServerUDP()
  {
    super("Host");
    gioco = new Gioco(null,this);
  }
   
   
  public void run()
  {
    try
    {
      //Attivo la Socket sul Server in ascolto sulla porta 30777
      s = new DatagramSocket(30777);
    } catch (SocketException ex)
    {
      Logger.getLogger(ServerUDP.class.getName()).log(Level.SEVERE, null, ex);
    }
   
    //Informazioni sul Server in ascolto
    InetAddress indirizzo = s.getLocalAddress();
    
    server = null;
    try
    {
      server = InetAddress.getLocalHost().getHostAddress();
    } catch (UnknownHostException ex)
    {
      Logger.getLogger(ServerUDP.class.getName()).log(Level.SEVERE, null, ex);
    }
     
    port = s.getLocalPort();
     
    System.out.println("In ascolto Server UDP: "+ server + " porta: " + port);
    
 
     
   
       // Preparazione delle informazioni da ricevere
       byte[] buf = new byte[65536];
       System.out.println("In attesa di chiamate dai Client... ");
       recv = new DatagramPacket(buf, buf.length);
       
       
       
       
    // ******** per invio CLIENT *********
    // ***********************************
    // ***********************************
    // ***********************************
    // ***********************************
    try
    {
      //Creazione della Socket per l'invio del Datagramma con porta Host 30777
      c = new DatagramSocket();
    } catch (SocketException ex)
    {
      System.out.println("Errore nella creazione del DatagramSocket " + ex);
    }     
    
    
    
    
    // ******** FINE *********** 
    // ******** FINE *********** 
    // ******** FINE *********** 
    // ******** FINE *********** 
    // ******** FINE *********** 
    // ******** FINE *********** 
    
       
       
       
    while (true) 
    {
      try
      {
        s.receive(recv);
      } catch (IOException ex)
      {
        System.out.println("Errore nella ricezione");
      }
       
      
       
      InetAddress address = recv.getAddress();
      
      //Informazioni sul Client che ha effettuato la chiamata
      client = address.getHostName();
      int porta = recv.getPort();
      System.out.println("In chiamata Client: "+ client + " porta: " + porta);
 
      
      //Messaggio ricevuto dal Client
      String messaggio = new String(recv.getData(), recv.getOffset(), recv.getLength());
      System.out.println("Il Client ha scritto: " + messaggio);
       
      
      if(messaggio != null && cont==0)
      {
        // invia un messaggio al client per la sincronizzazione iniziale
        try
        {
          invia_punteggio(0);
        } catch (IOException ex)
        {
          Logger.getLogger(ServerUDP.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        
        // modifico il flag in gioco, necessario per farlo partire
        gioco.parti();
        cont++;
      }
      
      
      try
      {
        gioco.aggiorna_punteggio(messaggio);
      } catch (IOException ex)
      {
        Logger.getLogger(ServerUDP.class.getName()).log(Level.SEVERE, null, ex);
      }
    } 
    
    
    
    
  }

   
  
  
  // ******** per invio CLIENT *********
  // ***********************************
  // ***********************************
  // ***********************************
  // ***********************************
  public void invia_punteggio(int punteggio) throws IOException
  {
    
    
    
    String punteggios = String.valueOf(punteggio);     
    try
    {
      addressCLIENT = InetAddress.getByName(client);
    } catch (UnknownHostException ex)
    {
      System.out.println("Errore nella creazione del IP CLIENT " + ex);
    }
    byte [] msg = {0};
    per_client = new DatagramPacket(msg, msg.length, addressCLIENT, portCLIENT);     
    
    per_client.setData(punteggios.getBytes());
    per_client.setLength(punteggios.length());
    c.send(per_client);   
    
  }    
  
  public String get_ip()
  {
    return server;
  }
  
  public int get_porta()
  {
    return 30777;
  }
}