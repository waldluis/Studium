/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

package zeichenprogramm.controller.commands;

import zeichenprogramm.model.ZeichenModel;
import zeichenprogramm.view.ZeichenFrame;
import java.io.File;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

/**
 *
 * @author waldhauserlu78556
 */
public class OpenCommand implements CommandInterface
{

  private ZeichenFrame frame;
  private ZeichenModel model;

  public OpenCommand(ZeichenFrame frame, ZeichenModel model)
  {
    this.frame = frame;
    this.model = model;
  }
  
   @Override
  public void execute()
  {
    int wahl = frame.getFcDatei().showOpenDialog(frame);
    if (wahl == JFileChooser.APPROVE_OPTION)
    {
      String f = frame.getFcDatei().getSelectedFile().getAbsolutePath();

      try
      {
        model.loadFigures(f);
        model.addFigure();
          frame.repaint();
      }
      catch(Exception e)
      {
        JOptionPane.showMessageDialog(frame, "Error with file to open, wrong data format", "Dialog", JOptionPane.ERROR_MESSAGE);
      }

    
    }
  }

  @Override
  public void undo()
  {
  }

  @Override
  public boolean isUndoable()
  {
    return false;
  }


 

}

