/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package umrechner_mvc;

import umrechner_mvc.controller.ControllerToZentimeter;
import umrechner_mvc.controller.ControllerToZoll;
import umrechner_mvc.model.Anwendung;
import umrechner_mvc.view.Fenster;

/**
 *
 * @author waldhauserlu78556
 */
public class Start {
    
    public Start()
    {
        Fenster view = new Fenster();
        Anwendung model = new Anwendung();
        ControllerToZentimeter ctrlZentimeter = new ControllerToZentimeter(view, model);
        ctrlZentimeter.registerEvents();
        ControllerToZoll ctrlZoll = new ControllerToZoll(view, model);
        ctrlZoll.registerEvents();
        view.setVisible(true);
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        new Start();
    }
    
}
