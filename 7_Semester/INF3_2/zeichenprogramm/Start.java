/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zeichenprogramm;

import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.WindowConstants;
import zeichenprogramm.controller.ZeichenController;
import zeichenprogramm.model.ZeichenModel;
import zeichenprogramm.view.ZeichenView;
import zeichenprogramm.view.ZeichenFrame;


/**
 *
 * @author waldhauserlu78556
 */
public class Start
{

  public Start()
  {
    ZeichenModel model = new ZeichenModel();
    ZeichenFrame frame = new ZeichenFrame();
    
  
    frame.getZeichenView1().setModel(model);
    
    ZeichenController controller = new ZeichenController(frame, model);
    controller.registerEvents();
    controller.registerCommands();

    //JFrame frm = new JFrame();
    //frm.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    //frm.setContentPane(view);
    //frm.setSize(800, 600);
    
    frame.setSize(800, 600);
    frame.setVisible(true);
  
  }

  public static void main(String[] args)
  {
    try
    {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch(Exception e)
    {
      System.err.println(e);
    }
    
    new Start();
  }
}
