/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package wuerfel;

import wuerfel.controller.StartStopController;
import wuerfel.controller.WertAdapter;
import wuerfel.model.Zahlengenerator;
import wuerfel.view.WuerfelView;

/**
 *
 * @author waldhauserlu78556
 */
public class Start {
    
    public Start()
    {
        WuerfelView view = new WuerfelView();
        Zahlengenerator model = new Zahlengenerator();
        StartStopController controller = new StartStopController(view, model);
        WertAdapter adapter = new WertAdapter(view, model);
        controller.registerEvents();
        model.addWertSubscription(adapter);
        view.setVisible(true);
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        new Start();
    }   
}
