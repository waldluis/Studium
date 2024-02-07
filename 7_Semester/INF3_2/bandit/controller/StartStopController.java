/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

package bandit.controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.logging.Logger;
import bandit.model.Zahlengenerator;
import bandit.util.OhmLogger;
import bandit.view.BanditView;
import bandit.model.BanditModel;

/**
 *
 * @author le
 */
public class StartStopController implements ActionListener
{
  private final static Logger lg = OhmLogger.getLogger();
  private BanditView view;
  private BanditModel model;
  
  public StartStopController(BanditView view, BanditModel model)
  {
    this.view = view;
    this.model = model;
  }
  
  public void registerEvents()
  {
    view.getBtnStart().addActionListener(this);
    view.getBtnStop().addActionListener(this);
  }

  @Override
  public void actionPerformed(ActionEvent evt)
  {
    if (evt.getSource() == view.getBtnStart())
    {
      this.model.getGenerator().get(0).start();
      this.model.getGenerator().get(1).start();
      this.model.getGenerator().get(2).start();
      // alle Starten 
      lg.info("Starten");
    }
    else
    {
      this.model.getGenerator().get(0).stop(); 
      this.model.getGenerator().get(1).stop();
      this.model.getGenerator().get(2).stop();// alle Stopen
      lg.info("Stop");
    }
  }
}