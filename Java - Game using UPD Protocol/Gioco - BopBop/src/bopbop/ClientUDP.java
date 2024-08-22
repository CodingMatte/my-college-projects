package bopbop;

//Importo i package necessari
import java.net.*;
import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;
 
public class ClientUDP extends Thread
{
  String ip, username, host;
  int porta;
  int cont=0;
  DatagramPacket recv, hi;
  DatagramSocket s, c;
  Gioco gioco;
  
  // METODO COSTRUTTORE A CUI PASSO LE STRINGHE
  public ClientUDP(String IP, int PORTA, String USERNAME)
  {
    super("Client");
    this.ip = IP;
    this.porta = PORTA;
    this.username = USERNAME;
  }
  
  public void run()
  {  
    // PARTE NATIVA CLIENT
    // *******************
    
    
    InetAddress addr = null;
    try
    {
      addr = InetAddress.getByName(this.ip);
    } catch (UnknownHostException ex)
    {
      System.out.println("Errore nella creazione di addr con this.ip " + ex);
    }
    
    
//    BufferedReader stdIn= new BufferedReader(new InputStreamReader(System.in));
    byte [] msg = {0};
 
    try
    {
      //Creazione della Socket per l'invio del Datagramma con porta Client dinamica
      s = new DatagramSocket();
    } catch (SocketException ex)
    {
      System.out.println("Errore nella creazione del DatagramSocket " + ex);
    }

    //Creazione del pacchetto da inviare al Server
    hi = new DatagramPacket(msg, msg.length, addr, this.porta);   
       
    // invio subito un messaggio per instaurare una connessione
    // e sincronizzare i giochi
    String ok = "0";
    hi.setData(ok.getBytes());
    hi.setLength(1);
    try
    {
        
      s.send(hi);
      
    } catch (IOException ex)
    {
      System.out.println("Errore nell'invio del PRIMO pacchetto " + ex);
    }
               
//    if(cont == 0)
//    {
//      System.out.println("CONNESSIONE STABILITA");
//      gioco = new Gioco(this,null);
//      cont++;    
//    }
    // * FINE PARTE NATIVA CLIENT *
    // // *******************************************
    // **********************************************
    // **********************************************
    
    
    // **************** PER RICEZIONE DAL SERVER ********************
    // **************************************************************
    // **************************************************************
    // **************************************************************
    // **************************************************************
    try
    {
      //Attivo la Socket sul Server in ascolto sulla porta 30000
      c = new DatagramSocket(30000);
    } catch (SocketException ex)
    {
      Logger.getLogger(ServerUDP.class.getName()).log(Level.SEVERE, null, ex);
    }
    
    
    // Preparazione delle informazioni da ricevere
    
    
    while (true) 
    {
      byte[] buf = new byte[65536];
      System.out.println("In attesa di MESSAGGI DAL SERVER");
      recv = new DatagramPacket(buf, buf.length);
      try
      {
        c.receive(recv); 
      } catch (IOException ex)
      {
        System.out.println("Errore nella ricezione");
      }
       
      if(cont == 0)
      {
        System.out.println("CONNESSIONE STABILITA");
        gioco = new Gioco(this,null);
        cont++;    
      }
      
      InetAddress address = recv.getAddress();
      
      //Informazioni sull'HOST che ha effettuato la chiamata
      host = address.getHostName();
      int porta = recv.getPort();
      System.out.println("In chiamata Host: "+ host + " porta: " + porta);
 
      //Messaggio ricevuto dall'HOST
      String messaggio = (new String(recv.getData()).trim());
      System.out.println("Il Server ha scritto: " + messaggio); 
       
      
      try
      {
        gioco.aggiorna_punteggio(messaggio);
      } catch (IOException ex)
      {
        Logger.getLogger(ClientUDP.class.getName()).log(Level.SEVERE, null, ex);
      }
    }          
    
    // **************** FINE RICEZIONE DAL SERVER ********************
    // **************************************************************
    // **************************************************************
    // **************************************************************
    // **************************************************************
    
  }
  
  
  public void invia_punteggio(int punteggio) throws IOException
  {
    
    String punteggios = String.valueOf(punteggio);
    hi.setData(punteggios.getBytes());
    hi.setLength(punteggios.length());
    s.send(hi);
  }   
}









