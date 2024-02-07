/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package bandit.model;

import java.util.concurrent.Flow.Subscriber;
import java.util.concurrent.SubmissionPublisher;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 *
 * @author waldhauserlu78556
 */
public class Zahlengenerator implements Runnable
{

  private int wert;
  private AtomicBoolean laufend;
  private SubmissionPublisher<Integer> wertPublisher;
  private Thread thd;
  private int index;
  private int time;

  public Zahlengenerator(int index)
  {
    wert = 1;
    this.index = index;
    laufend = new AtomicBoolean(false);
    wertPublisher = new SubmissionPublisher<>();
    thd = new Thread(this);
    thd.start();
    this.time = time;
    
    
  }

  /**
   * Add Subscriber to Integer publisher of wert
   *
   * @param subscriber
   */
  public void addWertSubscription(Subscriber<Integer> subscriber)
  {
    wertPublisher.subscribe(subscriber);
  }

  /**
   * Kritischer Abschnitt 
   * Benachrichtigung zum Weiterlaufen
   */
  public synchronized void start()
  {
    notify();
    laufend.set(true);
  }

  /**
   * Function to stop counting
   */
  public void stop()
  {
    laufend.set(false);
  }

  /**
   * Thread main function Count from 1 to 6 and publish the value Stop if
   * laufend changes to false and set self waiting
   */
  @Override
  public void run()
  {
    //dass Run nie von selbst beendet wird
    while (true)
    {
      while (!laufend.get())
      {
        //Hier kritischer Zustand und nicht gesamte Run, sonst Blockade
        //wartet nach Initalisierung
        synchronized (this)
        {
          try
          {
            //System.err.println("wait");
            wait();
            //System.err.println("running");
          }
          catch (InterruptedException ex)
          {
            System.err.println(ex.toString());
          }
        }
      }

      //Zaehler und Publisher laufen immer
      try
      {
        Thread.sleep(50);
      }
      catch (InterruptedException ex)
      {
        System.err.println(ex.toString());
      }
      if (wert == 7)
      {
        wert = 1;
      }
      wertPublisher.submit(wert);
      wert++;
    }
  }

  /**
   * @return the wert
   */
  public int getWert()
  {
    return wert;
  }

  /**
   * @param wert the wert to set
   */
  public void setWert(int wert)
  {
    this.wert = wert;
  }

  /**
   * @return the index
   */
  public int getIndex()
  {
    return index;
  }
}

