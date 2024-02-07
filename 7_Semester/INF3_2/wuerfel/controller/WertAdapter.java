/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package wuerfel.controller;

import java.util.concurrent.Flow;
import java.util.concurrent.Flow.Subscriber;
import java.util.concurrent.Flow.Subscription;
import wuerfel.model.Zahlengenerator;
import wuerfel.view.WuerfelView;

/**
 *
 * @author waldhauserlu78556
 */
public class WertAdapter implements Subscriber<Integer>
{
    private WuerfelView view;
    private Zahlengenerator model;
    private Subscription subscription;
    
    public WertAdapter(WuerfelView view, Zahlengenerator model)
    {
        this.view = view;
        this.model = model;
    }

    @Override
    public void onSubscribe(Flow.Subscription subscription) 
    {
        this.subscription = subscription;
        this.subscription.request(1);
    }

    @Override
    public void onNext(Integer item) 
    {
        String strWert = String.valueOf(item);
        view.getLblWert().setText(strWert);
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
    
}
