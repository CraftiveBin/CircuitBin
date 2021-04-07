
bool data;
long onTime, offTime;
// byte SumON, SumOFF; // number of programms on and number of programmes off
bool SumON;
void process()      // ! PLEASE DO NOT DISTURB THE PROGRAM SEQUENCE OF PROCESS LOOP !
{
  static byte PrevSeconds = 1; //let it run at initialisation
  if (Second != PrevSeconds)
  {
    SumON = false;
    for (int i = 0; i < (progMax * 7); i += 7)
    {
      DateTime on(Year, Month, Day, readEEPROM(i), readEEPROM(i + 1), readEEPROM(i + 2));
      DateTime off(Year, Month, Day, readEEPROM(i + 3), readEEPROM(i + 4), readEEPROM(i + 5));

      onTime = on.unixtime();
      offTime = off.unixtime();
      
      bool temp = pgm_read_byte(&weekPing[(readEEPROM(i + 6))][Week]); // get programmed week from PROGMEM

      //----------on------------------of-----------
      //<-off-----><-------on----------><----of--->

      //----------of------------------on-----------
      //<-on-----><-------off----------><----on--->

      if ((((onTime < offTime) && (unixNow >= onTime) && (unixNow < offTime)) || 
         ((onTime > offTime) && ((unixNow >= onTime) || (unixNow < offTime)))) && (temp == 1))
      {
        SumON = true;
      }
    }

    if (SumON)
    {
      processOut = HIGH;
    }
    else
    {
      processOut = LOW;
    }

    PrevSeconds = Second;
  }

  if (processOut == 1 && event5 == 0)
  {
    digitalWrite(Station01, HIGH);
    Station = HIGH;
  }
  else if (event5 == 1)
  {
    digitalWrite(Station01, HIGH);
    Station = HIGH;
  }
  else if (event5 == 2)
  {
    digitalWrite(Station01, LOW);
    Station = LOW;
  }
  else
  {
    digitalWrite(Station01, LOW);
    Station = LOW;
  }
}
