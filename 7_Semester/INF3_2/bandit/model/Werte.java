/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package bandit.model;

/**
 *
 * @author waldhauserlu78556
 */
public class Werte 
{
    private int wert;
    private int index;
    
    public Werte(int index)
    {
        wert = 0;
        this.index = index; 
    }
    
    public int getWert()
    {
        return wert;
    }
            
    public int getIndex()
    {
        return index;
    }
    
    public void setWert(int wert)
    {
        this.wert = wert;
    }
}
