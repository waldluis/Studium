/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package umrechner_mvc.model;

/**
 *
 * @author waldhauserlu78556
 */
public class Anwendung {
    
      private final static double FAKTOR = 2.54;
      

      public double zentimeterToZoll(double zentimeter)
      {
          return zentimeter / FAKTOR;
      }
      
      public double zollToZentimeter(double zoll)
      {
          return zoll * FAKTOR;
      }
    
}
