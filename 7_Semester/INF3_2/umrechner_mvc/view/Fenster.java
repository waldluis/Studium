/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package umrechner_mvc.view;

import java.awt.Container;
import java.awt.FlowLayout;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import static javax.swing.WindowConstants.EXIT_ON_CLOSE;

/**
 *
 * @author waldhauserlu78556
 */
public class Fenster extends JFrame
{
    
  private JButton btnToZentimeter;
  private JButton btnToZoll;
  private JTextField tfZoll;
  private JTextField tfZentimeter;
  private JLabel lZoll;
  private JLabel lZentimeter;
    
  public Fenster()
  {
    this.setDefaultCloseOperation(EXIT_ON_CLOSE);
    this.setSize(350, 150);
    
    btnToZentimeter = new JButton(">");
    btnToZoll = new JButton("<");
    tfZoll = new JTextField(20);
    tfZentimeter = new JTextField(20);
    lZoll = new JLabel("Zoll(inch)");
    lZentimeter = new JLabel("Zentimeter(cm)");
    
    tfZoll.setHorizontalAlignment(JTextField.RIGHT);
    tfZentimeter.setHorizontalAlignment(JTextField.RIGHT);
    
    
    Container hauptKiste = this.getContentPane();
    hauptKiste.setLayout(new FlowLayout());
    
    Container boxKisteLeft = new Container();
    boxKisteLeft.setLayout(new BoxLayout(boxKisteLeft, BoxLayout.Y_AXIS));
    boxKisteLeft.add(lZoll);
    boxKisteLeft.add(tfZoll);
    
    Container boxKisteCenter = new Container();
    boxKisteCenter.setLayout(new BoxLayout(boxKisteCenter, BoxLayout.Y_AXIS));
    boxKisteCenter.add(btnToZentimeter);
    boxKisteCenter.add(btnToZoll);
    
    Container boxKisteRight = new Container();
    boxKisteRight.setLayout(new BoxLayout(boxKisteRight, BoxLayout.Y_AXIS));
    boxKisteRight.add(lZentimeter);
    boxKisteRight.add(tfZentimeter);
    
    hauptKiste.add(boxKisteLeft);
    hauptKiste.add(boxKisteCenter);
    hauptKiste.add(boxKisteRight);
    
  }
  
  public JButton getBtnToZentimeter()
    {
        return btnToZentimeter;
    }
  
  public JButton getBtnToZoll()
    {
        return btnToZoll;
    }
  
  public JTextField getTfZoll()
  {
      return tfZoll;
  }
  
  public JTextField getTfZentimeter()
  {
      return tfZentimeter;
  }
}
