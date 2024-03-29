/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JFrame.java to edit this template
 */
package bandit.view;

/**
 *
 * @author waldhauserlu78556
 */
public class BanditView extends javax.swing.JFrame {

    /**
     * @return the btnStart
     */
    public javax.swing.JButton getBtnStart() {
        return btnStart;
    }

    /**
     * @return the btnStop
     */
    public javax.swing.JButton getBtnStop() {
        return btnStop;
    }

    /**
     * @return the lblWert1
     */
    public javax.swing.JLabel getLblWert1() {
        return lblWert1;
    }

    /**
     * @return the lblWert2
     */
    public javax.swing.JLabel getLblWert2() {
        return lblWert2;
    }

    /**
     * @return the lblWert3
     */
    public javax.swing.JLabel getLblWert3() {
        return lblWert3;
    }

    /**
     * Creates new form BanditView
     */
    public BanditView() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        btnStart = new javax.swing.JButton();
        btnStop = new javax.swing.JButton();
        jPanel2 = new javax.swing.JPanel();
        lblWert1 = new javax.swing.JLabel();
        lblWert2 = new javax.swing.JLabel();
        lblWert3 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        btnStart.setText("Start");
        jPanel1.add(btnStart);

        btnStop.setText("Stop");
        jPanel1.add(btnStop);

        getContentPane().add(jPanel1, java.awt.BorderLayout.PAGE_END);

        lblWert1.setFont(new java.awt.Font("Liberation Sans", 0, 100)); // NOI18N
        lblWert1.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        lblWert1.setText("?");
        jPanel2.add(lblWert1);

        lblWert2.setFont(new java.awt.Font("Liberation Sans", 0, 100)); // NOI18N
        lblWert2.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        lblWert2.setText("?");
        jPanel2.add(lblWert2);

        lblWert3.setFont(new java.awt.Font("Liberation Sans", 0, 100)); // NOI18N
        lblWert3.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        lblWert3.setText("?");
        jPanel2.add(lblWert3);

        getContentPane().add(jPanel2, java.awt.BorderLayout.CENTER);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(BanditView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(BanditView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(BanditView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(BanditView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new BanditView().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnStart;
    private javax.swing.JButton btnStop;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JLabel lblWert1;
    private javax.swing.JLabel lblWert2;
    private javax.swing.JLabel lblWert3;
    // End of variables declaration//GEN-END:variables
}
