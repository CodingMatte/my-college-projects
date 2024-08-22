/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bopbop;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.BoxLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;



public class PannelloConnessione extends JFrame 
{
    JPanel Parametri;
    JPanel Nomi;
    JPanel Bottoni;

    
    JTextField TextIP, TextPORTA, TextUSERNAME;
    JButton CONNETTI, ESCI;
    
    

public PannelloConnessione() 
    {
	setLayout(new BorderLayout());
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
     
      
        Parametri = new JPanel();
        Nomi = new JPanel();
        Bottoni = new JPanel();
      
        // aggiungiamo i vari panelli al frame nelle relative posizioni
       add(Nomi, BorderLayout.WEST);
       add(Parametri, BorderLayout.EAST);
       add(Bottoni, BorderLayout.SOUTH);
      
       // li metto uno sotto l'altro
       Nomi.setLayout(new BoxLayout(Nomi, BoxLayout.Y_AXIS));
       Parametri.setLayout(new BoxLayout(Parametri, BoxLayout.Y_AXIS));
      
      JLabel lip=new JLabel("IP");
      JLabel lporta=new JLabel("Porta");
      JLabel luser=new JLabel("Username");
      
      // aggiungo i label
      Nomi.add(lip);
      Nomi.add(lporta);
      Nomi.add(luser);
      int fontSize = 28;
      
      lip.setFont(new Font("TimesRoman", Font.BOLD, fontSize));
      lporta.setFont(new Font("TimesRoman", Font.BOLD, fontSize));
      luser.setFont(new Font("TimesRoman", Font.BOLD, fontSize));
  
      
      // aggiungo i parametri
      TextIP = new JTextField(15);
      TextPORTA = new JTextField(5);
      TextUSERNAME = new JTextField(30);
      Parametri.add(TextIP);
      Parametri.add(TextPORTA);
      Parametri.add(TextUSERNAME);
      
      // aggiungo i bottoni
      CONNETTI = new JButton("Connetti");
      ESCI = new JButton("Esci");
      Bottoni.add(CONNETTI);
      Bottoni.add(ESCI);

      
      addActions();
         
      pack();
      setTitle("Pannello di Connessione");
      setVisible(true);
      
    } // End constructor

	private void addActions() {
       
		CONNETTI.addActionListener(new ActionListener() {
            @Override
			public void actionPerformed(ActionEvent e) 
            {
			  // dichiarazione variabili 
              String IP, USERNAME;
              int PORTA;
              
              
              // assegnamento variabili
              IP = getIndirizzoIP();
              PORTA = getPORTA();
              USERNAME = getUSERNAME();
              
              
              // chiudo il pannello corrente
             
              chiudi();
                         
              // effettuo la connessione con IP e PORTA inseriti
              ClientUDP udpClient = new ClientUDP( IP,  PORTA, USERNAME);
              
              // lo faccio partire
              udpClient.start();
             
              
              
			}
		}); // Connect to a server button

		ESCI.addActionListener(new ActionListener() {
            @Override
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});// Quit program button
        
        
      
	} // End addActions
    
    
    
    
    public void chiudi()
    {
      setVisible(false);
    }
    
    
    
    public String getIndirizzoIP() 
    {
        return TextIP.getText();
    }

    
    public int getPORTA() 
    {
        // converto in intero
        return Integer.parseInt(TextPORTA.getText());
    }
    
    public String getUSERNAME() 
    {
        return TextUSERNAME.getText();
    }
    
    
} // End


