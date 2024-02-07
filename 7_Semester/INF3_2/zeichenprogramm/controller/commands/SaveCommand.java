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
 * @author luisw
 */
public class SaveCommand implements CommandInterface
{

  private ZeichenFrame frame;
  private ZeichenModel model;

  public SaveCommand(ZeichenFrame frame, ZeichenModel model)
  {
    this.frame = frame;
    this.model = model;
  }

  @Override
  public void execute()
  {
    int wahl = frame.getFCsvDatei().showSaveDialog(frame);
    if (wahl == JFileChooser.APPROVE_OPTION)
    {
      String f = frame.getFCsvDatei().getSelectedFile().getAbsolutePath();

      try
      {
        model.saveFigures(f);
      }
      catch (Exception e)
      {
        JOptionPane.showMessageDialog(frame, "Error with file to save, wrong data format", "Dialog", JOptionPane.ERROR_MESSAGE);
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
