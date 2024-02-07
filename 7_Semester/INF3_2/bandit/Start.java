/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package bandit;

import bandit.controller.StartStopController;
import bandit.controller.WertAdapter;
import bandit.model.BanditModel;
import bandit.view.BanditView;


/**
 *
 * @author waldhauserlu78556
 */
public class Start {

    public Start()
    {
      //einschreiben des Werteadapters beim Banditmodel
       BanditView view = new BanditView();
       BanditModel model = new BanditModel(3);
       StartStopController controller = new StartStopController(view, model);
       WertAdapter adapter = new WertAdapter(view, model);
       adapter.einschreiben();
       controller.registerEvents();
       
        //model.addWertSubscription(adapter);
        view.setVisible(true);
    
    }
    public static void main(String[] args) {
        new Start();
    }
    
}
