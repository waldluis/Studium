/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package wuerfel.model;

import java.util.concurrent.Flow.Subscriber;
import java.util.concurrent.SubmissionPublisher;

/**
 *
 * @author waldhauserlu78556
 */
public class Zahlengenerator implements Runnable {

    private int wert;
    private boolean laufend;
    private boolean publish;
    private SubmissionPublisher<Integer> wertPublisher;
    private Thread thd;

    public Zahlengenerator() 
    {
        wert = 1;
        laufend = false;
        publish = false;
        thd = null;
        wertPublisher = new SubmissionPublisher<>();
    }
    
    public void addWertSubscription(Subscriber<Integer> subscriber)
    {
        wertPublisher.subscribe(subscriber);
    }
    
    public void start()
    {
        laufend = true;
        publish = true;
        
        if(thd == null)
        {
            thd = new Thread(this);
            thd.start();
        }
    }

    public void stop() 
    {
        publish = false;
    }

    @Override
    public void run() 
    {
        while (laufend) 
        {
            try 
            {
                Thread.sleep(50);
            } 
            catch(InterruptedException ex)
            {
                System.err.println(ex.toString());
            }
            
            if(wert == 7)
            {
                wert = 1;
            }
            if(publish == true)
                {
                    wertPublisher.submit(wert);
                }
            wert++;
        }
    }
}
