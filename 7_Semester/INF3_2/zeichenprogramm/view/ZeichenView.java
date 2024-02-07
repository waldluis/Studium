/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zeichenprogramm.view;

import java.awt.BasicStroke;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.RenderingHints;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;
import java.awt.print.PageFormat;
import java.awt.print.Printable;
import java.awt.print.PrinterException;
import java.awt.print.PrinterJob;
import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.standard.DialogTypeSelection;
import javax.swing.JComponent;
import javax.swing.JOptionPane;
import zeichenprogramm.model.ZeichenModel;

/**
 *
 * @author waldhauserlu78556
 */
public class ZeichenView extends JComponent implements Printable
{

  private Line2D.Float line;
  private final static Dimension DIM_ONE = new Dimension(1, 1);
  private Rectangle2D.Float pixel;
  private ZeichenModel model;
  private Point p_old;
  private Point p_old2;
  private BasicStroke stiftLine;
  private BasicStroke stiftPixel;
  private static final float DICKE = 3;

  public ZeichenView()
  {
    pixel = new Rectangle2D.Float();
    line = new Line2D.Float();
    p_old = new Point();
    stiftLine = new BasicStroke(DICKE);
    stiftPixel = new BasicStroke(1);

  }

  public void setModel(ZeichenModel model)
  {
    this.model = model;
  }

  /**
   * Draw one Pixel and connect new Pixel with old Pixel with Line if existing
   *
   * @param p
   */
  public void drawPoint(Point p)
  {

    Graphics2D g2 = (Graphics2D) this.getGraphics();
    pixel.setFrame(p, DIM_ONE);
    g2.setStroke(stiftPixel);
    g2.draw(pixel);
    g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

    if(model != null)
    {
    
    if (model.getLastFigure().getPoints().isEmpty())
    {
      p_old = p;
    }

    line.setLine(p, p_old);

    p_old = p;
    g2.setStroke(stiftLine);
    g2.draw(line);

    g2.dispose();
    }
  }

  /**
   * Draw all Figures from Model
   *
   * @param g
   */
  @Override
  public void paintComponent(Graphics g)
  {
    super.paintComponent(g);
    Graphics2D g2 = (Graphics2D) g;
    g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

    if(model != null)
    {

    
      model.getFigures().forEach(f
              ->
      {
            
        f.getPoints().forEach(p
                ->
        {
          if (p == f.getPoint(0))
          {
            p_old2 = p;
          }

          pixel.setFrame(p, DIM_ONE);
          g2.setStroke(stiftPixel);
          g2.draw(pixel);

          line.setLine(p, p_old2);
          p_old2 = p;
          g2.setStroke(stiftLine);
          g2.draw(line);
        });
      });
    }
  }

  public void doPrint()
  {
    HashPrintRequestAttributeSet printSet
            = new HashPrintRequestAttributeSet();
    printSet.add(DialogTypeSelection.NATIVE);
    PrinterJob pj = PrinterJob.getPrinterJob();
    pj.setPrintable(this);
    if (pj.printDialog(printSet))
    {
      try
      {
        pj.print(printSet);
      }
      catch (PrinterException ex)
      {
        JOptionPane.showMessageDialog(this, ex.toString());
      }
    }
  }

  @Override
  public int print(Graphics gp, PageFormat pf, int pageIndex) throws PrinterException
  {
    Graphics2D g2p = (Graphics2D) gp;
    if (pageIndex == 0)
    {
      g2p.translate(pf.getImageableX(), pf.getImageableY());
      g2p.scale(pf.getImageableWidth() / this.getWidth(),
              pf.getImageableHeight() / this.getHeight());
      super.print(g2p);
      return Printable.PAGE_EXISTS;
    }
    else
    {
      return Printable.NO_SUCH_PAGE;
    }
  }

}
