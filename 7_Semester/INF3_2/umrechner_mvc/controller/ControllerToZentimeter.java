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
public class ControllerToZentimeter implements ActionListener
{
    private Fenster view;
    private Anwendung model;
    
    public ControllerToZentimeter(Fenster view, Anwendung model)
    {
        this.view = view;
        this.model = model;
    }
    
    public void registerEvents()
    {
        view.getBtnToZentimeter().addActionListener(this);
        view.getTfZoll().addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        NumberFormat nf_in = NumberFormat.getNumberInstance(Locale.GERMANY);
        double zoll = 0;
        try
        {
            zoll = nf_in.parse(view.getTfZoll().getText().replace(".", ",")).doubleValue();
        }
        catch(ParseException ex)
        {
            JOptionPane.showMessageDialog(view, "Insert number with decimal comma", "Dialog", JOptionPane.ERROR_MESSAGE);
        }
        double zentimeter = model.zollToZentimeter(zoll);
        String output = String.format("%.2f", zentimeter);
        view.getTfZentimeter().setText(output);
    }
    
}
