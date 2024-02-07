/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

package bandit.controller;

import java.util.concurrent.Flow;
import java.util.concurrent.Flow.Subscriber;
import java.util.concurrent.Flow.Subscription;
import bandit.model.Zahlengenerator;
import bandit.view.BanditView;
import bandit.model.BanditModel;
import bandit.model.Werte;

/**
 *
 * @author le
 */
public class WertAdapter implements Subscriber<Integer>
{
  private BanditView view;
  private BanditModel model;
  private Subscription subscription;
  //private int index; 
  
  public WertAdapter(BanditView view, BanditModel model)
  {
    this.view = view;
    this.model = model;
  }
  
    public void einschreiben() //bei BanditModel
    {
      model.addWertSubscription(this); 
    }

  @Override
  public void onSubscribe(Flow.Subscription subscription)
  {
    this.subscription = subscription;
//    this.subscription.request(6);
    this.subscription.request(1);
  }

  @Override
  public void onNext(Integer item)
  {
    String strWert = String.valueOf(model.getWerte().get(item).getWert());
    if( item == 0)
    {
    view.getLblWert1().setText(strWert);
    }
    if(item == 1)
    {
    view.getLblWert2().setText(strWert); 
    }
    if(item == 2)
    {
    view.getLblWert3().setText(strWert); 
    }
    
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
    System.out.println("FERTIG");
  }
}