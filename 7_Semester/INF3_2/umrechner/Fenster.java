/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

package umrechner;

import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.Locale;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

/**
 *
 * @author localuser
 */
public class Fenster extends JFrame
{
  private JButton btnOben;
  private JButton btnUnten;
  private JTextField tfZoll;
  private JTextField tfZentimeter;
  private JLabel lZoll;
  private JLabel lZentimeter;
  
  
  public Fenster()
  {
    this.setDefaultCloseOperation(EXIT_ON_CLOSE);
    this.setSize(350, 150);
    
    btnOben = new JButton(">");
    btnUnten = new JButton("<");
    tfZoll = new JTextField();
    tfZentimeter = new JTextField();
    lZoll = new JLabel("Zoll(inch)");
    lZentimeter = new JLabel("Zentimeter(cm)");
    
    
    Container hauptKiste = this.getContentPane();
    hauptKiste.setLayout(new FlowLayout());
    
    Container boxKisteLeft = new Container();
    boxKisteLeft.setLayout(new BoxLayout(boxKisteLeft, BoxLayout.Y_AXIS));
    boxKisteLeft.add(lZoll);
    boxKisteLeft.add(tfZoll);
    
    Container boxKisteCenter = new Container();
    boxKisteCenter.setLayout(new BoxLayout(boxKisteCenter, BoxLayout.Y_AXIS));
    boxKisteCenter.add(btnOben);
    boxKisteCenter.add(btnUnten);
    
    Container boxKisteRight = new Container();
    boxKisteRight.setLayout(new BoxLayout(boxKisteRight, BoxLayout.Y_AXIS));
    boxKisteRight.add(lZentimeter);
    boxKisteRight.add(tfZentimeter);
    
    hauptKiste.add(boxKisteLeft);
    hauptKiste.add(boxKisteCenter);
    hauptKiste.add(boxKisteRight);
  }
  
  public void registerEvents()
  {
    tfZoll.addActionListener(this::ZollAction);
    tfZentimeter.addActionListener(this::ZentimeterAction);
    btnOben.addActionListener(this::btnObenAction);
    btnUnten.addActionListener(this::btnUntenAction);
  }

  private void ZollAction(ActionEvent e)
  {
    zollInZentimeter();
  }

  private void ZentimeterAction(ActionEvent e)
  {
    zentimeterInZoll();
  }

  private void btnObenAction(ActionEvent e)
  {
    zollInZentimeter();
  }

  private void btnUntenAction(ActionEvent e)
  {
    zentimeterInZoll();
  }
  
  private void zollInZentimeter()
  {
     NumberFormat nf_in = NumberFormat.getNumberInstance(Locale.GERMANY);
    double zoll = 0;
    try
    {
      zoll = nf_in.parse(tfZoll.getText()).doubleValue();
    }
    catch(ParseException ex)
    {
      JOptionPane.showMessageDialog(this, "Insert number with decimal comma", "Dialog", JOptionPane.ERROR_MESSAGE);
    }
    double zentimeter = zoll * 2.54;
    String output = String.format("%.2f", zentimeter);
    tfZentimeter.setText(output);
  }
  
  private void zentimeterInZoll()
  {
     NumberFormat nf_in = NumberFormat.getNumberInstance(Locale.GERMANY);
    double zentimeter = 0;
    try
    {
      zentimeter = nf_in.parse(tfZentimeter.getText()).doubleValue();
    }
    catch(ParseException ex)
    {
      JOptionPane.showMessageDialog(this, "Insert number with decimal comma", "Dialog", JOptionPane.ERROR_MESSAGE);
    }
    double zoll = zentimeter * 2.54;
    String output = String.format("%.2f", zoll);
    tfZoll.setText(output);
  }
}