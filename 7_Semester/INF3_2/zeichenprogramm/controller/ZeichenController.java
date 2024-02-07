/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package zeichenprogramm.controller;

import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import zeichenprogramm.model.Figure;
import zeichenprogramm.model.ZeichenModel;
import zeichenprogramm.view.ZeichenFrame;
import zeichenprogramm.controller.commands.OpenCommand;
import zeichenprogramm.controller.commands.PrintCommand;
import zeichenprogramm.controller.commands.SaveCommand;
import zeichenprogramm.controller.commands.CommandInvoker;

/**
 * 
 * @author waldhauserlu78556
 */
public class ZeichenController extends MouseAdapter implements MouseMotionListener, ActionListener 
{
  private ZeichenFrame frame;
  private ZeichenModel model;
  private CommandInvoker invoker;
  
  public ZeichenController(ZeichenFrame frame, ZeichenModel model)
  {
    this.frame = frame;
    this.model = model;
    invoker = new CommandInvoker();
  }
  
  public void registerEvents()
  {
    frame.getZeichenView1().addMouseMotionListener(this);
    frame.getZeichenView1().addMouseListener(this);
    frame.getjButtonOpen().addActionListener(this);
    frame.getjButtonPrint().addActionListener(this);
    frame.getjButtonSave().addActionListener(this);
    
  }
  
  public void registerCommands()
  {
    PrintCommand cmdprint = new PrintCommand(frame, model);
    invoker.addCommand(frame.getjButtonPrint(), cmdprint);
    
     OpenCommand cmdopen = new OpenCommand(frame, model);
    invoker.addCommand(frame.getjButtonOpen(), cmdopen);
    
    SaveCommand cmdsave = new SaveCommand(frame,model);
    invoker.addCommand(frame.getjButtonSave(), cmdsave);
   
  }
  
  @Override
  public void mouseReleased(MouseEvent evt)
  {
    
    if(evt.getButton() == MouseEvent.BUTTON1)
      {
        model.addFigure();
      }
  }

  @Override
  public void mouseDragged(MouseEvent evt)
  {
    Point p = evt.getPoint();
    frame.getZeichenView1().drawPoint(p);  
    model.getLastFigure().addPoint(p);
  }

  @Override
  public void mouseMoved(MouseEvent evt)
  {
  }
  
  @Override
  public void actionPerformed(ActionEvent e)
  {
    Object key = e.getSource();
    
    invoker.executeCommand(key);
  }
}
