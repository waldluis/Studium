/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package zeichenprogramm.model;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * 
 * @author waldhauserlu78556
 * Seriazable
 */
public class ZeichenModel 
{
  private ArrayList<Figure> figures;
  private Figure lastFigure;
  
  public ZeichenModel()
  {
    figures = new ArrayList<>();
    lastFigure = new Figure();
    figures.add(lastFigure);
  }
  
  public void addFigure()
  {
     lastFigure = new Figure();
    figures.add(lastFigure);
  }
  
  public Figure getLastFigure()
  {
      return lastFigure;
  }

  public List<Figure> getFigures()
  {

    return Collections.unmodifiableList(figures);
    
  }
  
  public void saveFigures(String filename) throws FileNotFoundException, IOException
  {
    FileOutputStream fos = new FileOutputStream(filename);
    BufferedOutputStream bos = new BufferedOutputStream(fos);
    ObjectOutputStream oos = new ObjectOutputStream(bos);
    oos.writeObject(figures);
    oos.flush(); // wichtig! leert und schreibt damit den Puffer
    oos.close();
  }
  
  public void loadFigures(String filename) throws FileNotFoundException, IOException, ClassNotFoundException
  {
    FileInputStream fis = new FileInputStream(filename);
    BufferedInputStream bis = new BufferedInputStream(fis);
    ObjectInputStream ois = new ObjectInputStream(bis);
    Object obj = ois.readObject();
    if (obj instanceof ArrayList)
    {
      figures = (ArrayList<Figure>)obj;
    }
    ois.close();
  }
  
  
}
