/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package bandit.model;

import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.Flow.Subscriber;
import java.util.concurrent.Flow.Subscription;
import java.util.concurrent.SubmissionPublisher;

/**
 *
 * @author waldhauserlu78556
 */
public class BanditModel implements Subscriber<Integer>
{
    
    private ArrayList<Zahlengenerator> generator;
    private ArrayList<Werte> werte;
    private SubmissionPublisher<Integer> wertPublisher1; // 1 Publisher für den Adapter
    private Subscription subscription; //1 subscriber für alle Zähler
    private int zaehler;
    private int anzahl;
    
    //ArrayList<Subscriber> zahlenSubscriber;
    
    
    public BanditModel(int anzahl)
    {
        this.anzahl = anzahl;
        this.zaehler = 0;
        generator = new ArrayList<>();
        werte = new ArrayList<>();
        wertPublisher1 = new SubmissionPublisher(); 
        
        
        for (int i = 0; i < anzahl; i++)
        {
            generator.add(new Zahlengenerator(i));
            werte.add(new Werte(i));
            this.einschreiben(i); // Abonnieren der Genertoren Publisher
        }
    }
    
     private void einschreiben(int index) // für einschreiben in Publisher
    {
      generator.get(index).addWertSubscription(this);
    }
     
    public void addWertSubscription(Subscriber<Integer> subscriber)
    {
        wertPublisher1.subscribe(subscriber); 
    }

    @Override
    public void onSubscribe(Subscription subscription) 
    {
      this.subscription = subscription;
      this.subscription.request(1);    
    }

    @Override
    public void onNext(Integer item) 
    {
        //index mit einbinden fehlt und Zufälliges zählen klappt nicht
        if(this.zaehler == this.anzahl)
        {
           this.zaehler = 0;
        }
        
        werte.get(zaehler).setWert(item);
        wertPublisher1.submit(this.zaehler);
        this.zaehler++;
        this.subscription.request(1);
        
    }

    @Override
    public void onError(Throwable throwable) 
    {
        System.err.println(throwable);
    }

    @Override
    public void onComplete() 
    {
       System.out.println("Fertig");
    }

  /**
   * @return the generator
   */
  public ArrayList<Zahlengenerator> getGenerator()
  {
    return generator;
  }

  /**
   * @return the werte
   */
  public ArrayList<Werte> getWerte()
  {
    return werte;
  }
}
