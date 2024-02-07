/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

package zeichenprogramm.controller.commands;

import java.util.HashMap;
import java.util.Stack;

/**
 *
 * @author waldhauserlu78556
 * Manager der Kommandos über Polymorphismus
 */
public class CommandInvoker 
{
    private HashMap<Object, CommandInterface> commands;
    private Stack<CommandInterface> undoStack;
    
    public CommandInvoker()
    {
        commands = new HashMap<>();
        undoStack = new Stack<>();
    }
    
    /**
     * Fügt ein Kommando zur HashMap hinzu
     * @param key Eventquelle Objekt
     * @param value Referenz auf das zugehörige Command Objekt
     */
    public void addCommand(Object key, CommandInterface value)
    {
        commands.put(key, value);
    }
    
    /**
     * Undo-Stack löschen
     */
    public void clearUndoStack()
    {
        undoStack.clear();
    }
    
    /**
     * Ausführen der jeweiligen Aktion des Eventquelle Objekts
     * @param key Eventquelle Objekt
     */
    public void executeCommand(Object key)
    {
        CommandInterface command = commands.get(key);
        command.execute();
        if(command.isUndoable())
        {
            undoStack.push(command);
        }
    }
    
    /**
     * Ausführen der Undo-Aktion wenn Undo-Erlaubte Aktionen vorhanden sind
     */
    public void undoCommand()
    {
        if(!undoStack.isEmpty())
        {
            undoStack.pop().undo();
        }
    }
}

