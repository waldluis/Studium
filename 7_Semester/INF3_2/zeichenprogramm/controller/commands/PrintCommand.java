/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

package zeichenprogramm.controller.commands;
import zeichenprogramm.model.ZeichenModel;
import zeichenprogramm.view.ZeichenFrame;
/**
 *
 * @author leon_
 */
public class PrintCommand implements CommandInterface
{
  
  private ZeichenFrame frame;
  private ZeichenModel model;
  
  public PrintCommand(ZeichenFrame frame, ZeichenModel model )
  {
    this.frame = frame;
    this.model = model;
  
  }
  
  @Override
  public void execute()
  {
    frame.getZeichenView1().doPrint();
    
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
