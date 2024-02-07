/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package bandit.util;

import java.io.File;
import java.io.IOException;
import java.time.LocalDateTime;
import java.util.logging.*;

/**
 *
 * @author le
 */
public class OhmLogger
{
  private static Logger lg = null;

  private OhmLogger()
  {
  }

  public static Logger getLogger()
  {
    if (lg == null)
    {
      lg = Logger.getLogger("OhmLogger");
      initLogger();
    }
    return lg;
  }

  private static void initLogger()
  {
    try
    {
      String datei = System.getProperty("user.dir") + File.separator + "log.txt";
      FileHandler fh = new FileHandler(datei);
      fh.setFormatter(new OhmFormatter());
      
      ConsoleHandler ch = new ConsoleHandler();
      ch.setFormatter(new OhmFormatter());

      lg.addHandler(fh);
      lg.addHandler(ch);
      lg.setLevel(Level.ALL);
    }
    catch (IOException ioex)
    {
      System.err.println(ioex);
    }
  }

}

class OhmFormatter extends SimpleFormatter
{

  @Override
  public String format(LogRecord record)
  {
    String logline = "";
    LocalDateTime ldt = LocalDateTime.now();
    logline += ldt.toString();
    logline += " | " + record.getLevel();
    logline += " | " + record.getClass();
    logline += " | " + record.getMessage();
    logline += " |\n";

    return logline;

  }
}
