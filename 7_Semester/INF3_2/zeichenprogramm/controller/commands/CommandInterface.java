/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package zeichenprogramm.controller.commands;

/**
 *
 * @author leon_
 */
public interface CommandInterface 
{
    public void execute();
    public void undo();
    public boolean isUndoable();
}
