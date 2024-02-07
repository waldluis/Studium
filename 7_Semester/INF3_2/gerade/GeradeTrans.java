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
import java.awt.geom.AffineTransform;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import javax.swing.JComponent;

/**
 *
 * @author waldhauserlu78556
 */
public class GeradeTrans extends JComponent implements Runnable
{

  private Line2D.Float line;
  private static final float DICKE = 5;
  private BasicStroke stift;
  private ExecutorService eService;
  private Future task;
  private double x2;
  private double y2;
  private double x;
  private double y;
  private double winkel;
  private long time;
  private AffineTransform at;

  public GeradeTrans(long time)
  {
    this.at = new AffineTransform();
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

    x = this.getWidth() / 2;
    y = this.getHeight() / 2;

    double mitteKleiner = Math.min(x, y);
    mitteKleiner -= 5;

    x2 = mitteKleiner;
    y2 = 0;

    line.setLine(0, 0, x2, y2);
    synchronized (this)
    {
      //g2.setTransform(this.at);
      g2.translate(x, y);
      g2.rotate(Math.toRadians(winkel));
    }

    g2.setStroke(stift);
    g2.setPaint(Color.BLACK);
    g2.draw(line);
    //at.setToIdentity();
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
