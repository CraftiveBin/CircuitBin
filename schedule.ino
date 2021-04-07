
bool data;
long onTime, offTime;
byte SumON, SumOFF; // number of programms on and number of programmes off
void process()      // ! PLEASE DO NOT DISTURB THE PROGRAM SEQUENCE OF PROCESS LOOP !
{
  static byte PrevSeconds = 1; //let it run at initialisation
  if (Second != PrevSeconds)
  {
    for (int i = 0; i < (progMax * 7); i += 7)
    {
      DateTime on(Year, Month, Day, readEEPROM(i), readEEPROM(i + 1), readEEPROM(i + 2));
      DateTime off(Year, Month, Day, readEEPROM(i + 3), readEEPROM(i + 4), readEEPROM(i + 5));

      onTime = on.unixtime();
      offTime = off.unixtime();

      bool temp = pgm_read_byte(&weekPing[(readEEPROM(i + 6))][Week]); // get programmed week from PROGMEM

      if ((onTime <= unixNow) && (temp == 1))
      {
        SumON++;
      }
      if((unixNow < offTime) && (temp == 1))
      {
        SumOFF--;
      }
    }

    if (SumON > 0)
    {
      processOut = HIGH;
    }
    else
    {
      processOut = LOW;
    }

    SumOFF = 0; // always put this at last
    SumON = 0;  // always put this at last*/

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
