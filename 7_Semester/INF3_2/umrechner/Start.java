/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */

package umrechner;

/**
 * Builder Class
 * @author localuser
 */
public class Start
{
  public Start()
  {
    Fenster frm = new Fenster();
    frm.registerEvents();
    frm.setVisible(true);
  }

  /**
   * @param args the command line arguments
   */
  public static void main(String[] args) 
  {
    new Start();
  }
}
