/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package zeichenprogramm.model;

import java.awt.Point;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 *
 * @author waldhauserlu78556
 */
public class Figure implements Serializable
{
    private ArrayList<Point> points;
    
    public Figure()
    {
        points = new ArrayList<>();
    }
    
    public void addPoint(Point p)
    {
        points.add(p);
    }
    
    public List<Point> getPoints()
    {
        return Collections.unmodifiableList(points);
    }
    
    public Point getPoint(int i)
    {
      return points.get(i);
    }
}
