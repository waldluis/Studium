/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package wuerfel_3.controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import wuerfel_3.model.Zahlengenerator;
import wuerfel_3.view.WuerfelView;

/**
 *
 * @author waldhauserlu78556
 */
public class StartStopController implements ActionListener
{
    private WuerfelView view;
    private Zahlengenerator model;
    
    public StartStopController(WuerfelView view, Zahlengenerator model)
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
    public void actionPerformed(ActionEvent e) 
    {
        if(e.getSource() == view.getBtnStart())
        {
            model.start();
        }
        else
        {
            model.stop();
        }
        
    }
    
}
