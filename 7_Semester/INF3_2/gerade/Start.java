/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package gerade;

import java.awt.Container;
import javax.swing.JFrame;
import javax.swing.OverlayLayout;
import javax.swing.WindowConstants;

/**
 *
 * @author waldhauserlu78556
 */
public class Start {
    
    public Start()
    {
        JFrame frm = new JFrame();
        frm.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        Container c = frm.getContentPane();
        
        c.setLayout(new OverlayLayout(c));
        
        GeradeSinCos gerade = new GeradeSinCos(50);
        GeradeTrans gerade2 = new GeradeTrans(70);
        c.add(gerade);
        c.add(gerade2);
        gerade.start();
        gerade2.start();
        
        frm.setSize(1000, 800);
        frm.setVisible(true);
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        new Start();
    }
    
}
