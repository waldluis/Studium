/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gerade;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.Line2D;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import javax.swing.JComponent;

/**
 *
 * @author waldhauserlu78556
 */
public class GeradeSinCos extends JComponent implements Runnable
{

  private Line2D.Float line;
  private static final float DICKE = 5;
  private BasicStroke stift;
  private ExecutorService eService;
  private Future task;
  private double x2;
  private double y2;
  private float winkel = 0;
  private long time;

  public GeradeSinCos(long time)
  {
    line = new Line2D.Float();
    stift = new BasicStroke(DICKE);
    task = null;
    eService = Executors.newSingleThreadExecutor();
    this.time = time;
  }

  public void start()
  {
    if (task == null)
    {
      task = eService.submit(this);
    }
  }

  @Override
  public void paintComponent(Graphics g)
  {
    super.paintComponent(g);
    Graphics2D g2 = (Graphics2D) g;
    g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

    float x = this.getWidth() / 2;
    float y = this.getHeight() / 2;

    synchronized (this)
    {
      //Kleinerer Wert von beiden da der sonst an beide Ränder geht
      //Bissl was Abziehen dass der net den Rand berührt
      float mitteKleiner = Math.min(x,y);
      mitteKleiner -= 5;
      
      x2 = x + Math.cos(Math.toRadians(winkel)) * mitteKleiner;
      y2 = y + Math.sin(Math.toRadians(winkel)) * mitteKleiner; 
    }

    line.setLine(x, y, x2, y2);

    g2.setStroke(stift);
    g2.setPaint(Color.BLUE);
    g2.draw(line);
  }

  @Override
  public void run()
  {
    while (true)
    {
      synchronized (this)
      {
        winkel += 1;
        if (winkel >= 360)
        {
          winkel = 0;
        }
      }
      this.repaint();

      try
      {
        Thread.sleep(this.time);
      }
      catch (Exception e)
      {
      }
    }
  }
}
