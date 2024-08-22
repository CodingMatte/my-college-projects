/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bopbop;


import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FontFormatException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;



public class MainMenu extends JFrame {

    
    
	int screenWidth = 275;
	int screenHeight = 400;

	int buttonWidth = 100;
	int buttonHeight = 40;

	JButton Play, Host, Connect, Quit;

	public MainMenu() {
		getContentPane().setLayout(null);
        
		// Calling methods
		addButtons();
		addActions();

		// Setting Bounds and Placing Button
        Play.setBounds((screenWidth - buttonWidth) / 2, 5, buttonWidth, buttonHeight);
		Host.setBounds((screenWidth - buttonWidth) / 2, 50, buttonWidth, buttonHeight);
		Connect.setBounds((screenWidth - buttonWidth) / 2, 95, buttonWidth, buttonHeight);
		Quit.setBounds((screenWidth - buttonWidth) / 2, 140, buttonWidth, buttonHeight);
        
        JLabel intro = new JLabel("Leonardo Manoni & Matteo Incicco");
        intro.setBounds((screenWidth - 215)/2, 300, 250, 30);
        
        
        
		// Placing Buttons
		getContentPane().add(Play);
		getContentPane().add(Quit);
		getContentPane().add(Host);
		getContentPane().add(Connect);
        getContentPane().add(intro);
        
		// JFrame Stuff
		pack();
		setVisible(true);
		setLocationRelativeTo(null);
		setSize(screenWidth, screenHeight);
		setTitle("Menù BopBop");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                //setResizable(false);
	} // End constructor

	// Add buttons to the JFrame
	private void addButtons() {
		Play = new JButton("Play SP");
		Host = new JButton("Host");
		Connect = new JButton("Client");
		Quit = new JButton("Quit");
	} // End addButtons

	// Add actions to the buttons
	private void addActions() {
        final int scelta;
		Play.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) 
                        {
                            chiudi();
                            new Gioco(null, null);
                                       }
		});// Play button

		Host.addActionListener(new ActionListener() 
                {
			public void actionPerformed(ActionEvent e) 
                        {
			
                            chiudi();
//                            new Gioco(null, null);
                            ServerUDP udpServer = new ServerUDP();
                           
                            udpServer.start();
				
			}
                });  // Host a server button

		Connect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) 
                        {
                            new PannelloConnessione();
                            chiudi();
                          
			}
		}); // Connect to a server button

		Quit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});// Quit program button
        
        
      
	} // End addActions
    
    
    public void chiudi()
    {
      setVisible(false);
    }
   
    
} // End the class