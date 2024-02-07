/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */

package erstesfenster;

import javax.swing.JFrame;

/**
 *
 * @author luisw
 */
public class Start 
{
  public Start()
  {
    Fenster fenster = new Fenster("mein erstes Fenster");
    fenster.registerEvents();
    fenster.setVisible(true);
  }

  public static void main(String[] args) 
  {
    new Start();
  }

}
