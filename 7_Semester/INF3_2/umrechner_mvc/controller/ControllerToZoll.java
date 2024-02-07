/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package umrechner_mvc.controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.Locale;
import javax.swing.JOptionPane;
import umrechner_mvc.model.Anwendung;
import umrechner_mvc.view.Fenster;

/**
 *
 * @author waldhauserlu78556
 */
public class ControllerToZoll implements ActionListener
{
    private Fenster view;
    private Anwendung model;
    
    public ControllerToZoll(Fenster view, Anwendung model)
    {
        this.view = view;
        this.model = model;
    }
    
    public void registerEvents()
    {
        view.getBtnToZoll().addActionListener(this);
        view.getTfZentimeter().addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        NumberFormat nf_in = NumberFormat.getNumberInstance(Locale.GERMANY);
        double zentimeter = 0;
        try
        {
            zentimeter = nf_in.parse(view.getTfZentimeter().getText().replace(".", ",")).doubleValue();
        }
        catch(ParseException ex)
        {
        JOptionPane.showMessageDialog(view, "Insert number with decimal comma", "Dialog", JOptionPane.ERROR_MESSAGE);
        }
        double zoll = model.zentimeterToZoll(zentimeter);
        String output = nf_in.format( zoll);
        view.getTfZoll().setText(output);
    }
    
    
}
