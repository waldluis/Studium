/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

package erstesfenster;

import java.awt.Color;
import java.awt.Container;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

/**
 *
 * @author luisw
 */
public class Fenster extends JFrame implements MouseListener, WindowListener
{
  public Fenster(String titel)
  {
    this.setTitle(titel);
    this.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
    this.setSize(1000, 800);
  }
  
  public void registerEvents()
  {
    this.addMouseListener(this);
    this.addWindowListener(this);
  }

  @Override
  public void mouseClicked(MouseEvent e)
  {
  }

  @Override
  public void mousePressed(MouseEvent e)
  {
  }

  @Override
  public void mouseReleased(MouseEvent e)
  {
    Container ding = this.getContentPane();
    float r = (float) Math.random();
    float g = (float) Math.random();
    float b = (float) Math.random();
    Color color = new Color(r,g,b);
    ding.setBackground(color);
  }

  @Override
  public void mouseEntered(MouseEvent e)
  {
  }

  @Override
  public void mouseExited(MouseEvent e)
  {
  }

  @Override
  public void windowOpened(WindowEvent e)
  {
  }

  @Override
  public void windowClosing(WindowEvent e)
  {
    int input = JOptionPane.showConfirmDialog(this, "Schließen", "Confirm", JOptionPane.YES_NO_OPTION);
    if(input == JOptionPane.YES_OPTION)
    {
      System.exit(0);
    }
  }

  @Override
  public void windowClosed(WindowEvent e)
  {
  }

  @Override
  public void windowIconified(WindowEvent e)
  {
  }

  @Override
  public void windowDeiconified(WindowEvent e)
  {
  }

  @Override
  public void windowActivated(WindowEvent e)
  {
  }

  @Override
  public void windowDeactivated(WindowEvent e)
  {
  }
}
