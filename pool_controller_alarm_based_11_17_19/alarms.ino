
void loadAlarms ()
{

  //Serial.println("loading alarms to EEPROM");
  // All off at 12:00:01 AM
  int hourTemp = 0;
  int minuteTemp = 0;
  int secondTemp = 1 ;

  // all off at midnight

  Alarm.alarmRepeat(hourTemp, minuteTemp, secondTemp, allPumpsOff);
  alarmsInSeconds[0] = 1;



  // clean for an hour at 4 am
  hourTemp = 4;
  minuteTemp = 0;
  Alarm.alarmRepeat(hourTemp, minuteTemp, secondTemp, cleanPool);
  alarmsInSeconds[0] = hourTemp * 60 * 60 + minuteTemp * 60 + secondTemp;
  subroutineName[0] = 1;
  minuteTemp = 30;
  Alarm.alarmRepeat(hourTemp + 1  , minuteTemp, secondTemp, allPumpsOff);
  alarmsInSeconds[1] = (hourTemp+1) * 60 * 60 + minuteTemp * 60 + secondTemp;
  subroutineName[1] = 0;

  Serial.println("alarms set");


  // clean for an hour at 8 am
  hourTemp = 8;
  Alarm.alarmRepeat(hourTemp, 30, 0, cleanPool);
  alarmsInSeconds[2] = hourTemp * 60 * 60 + minuteTemp * 60 + secondTemp;
  subroutineName[2] = 1;
 minuteTemp = 30;
 Alarm.alarmRepeat(hourTemp + 1 , minuteTemp, secondTemp, allPumpsOff);
  alarmsInSeconds[3] = (hourTemp+1) * 60 * 60 + minuteTemp * 60 + secondTemp;
  subroutineName[3] = 0;


  // filter low for two hours at 11:59am
  hourTemp = 11;
  minuteTemp = 59;
  secondTemp = 59;
  Alarm.alarmRepeat(hourTemp, minuteTemp, secondTemp, pumpThree);
  subroutineName[4] = 4;
  alarmsInSeconds[4] = hourTemp * 60 * 60 + minuteTemp * 60 + secondTemp;
  Alarm.alarmRepeat(hourTemp + 2 , minuteTemp, secondTemp, pumpThree);
  alarmsInSeconds[5] = (hourTemp+2) * 60 * 60 + minuteTemp * 60 + secondTemp;
  subroutineName[5] = 0;

  // filter low for an hour at 6 pm
  hourTemp = 18;
  minuteTemp = 00;
  secondTemp = 00;
  Alarm.alarmRepeat(hourTemp, minuteTemp, secondTemp, cleanPool);
  subroutineName[6] = 1;
  alarmsInSeconds[6] = hourTemp * 60 * 60 + minuteTemp * 60 + secondTemp;
  Alarm.alarmRepeat(hourTemp + 1 , minuteTemp, secondTemp, allPumpsOff);
  alarmsInSeconds[7] = (hourTemp+1) * 60 * 60 + minuteTemp * 60 + secondTemp;
  subroutineName[7] = 0;

  // filter low for an hour at 6 pm
  hourTemp = 22;
  minuteTemp = 00;
  secondTemp = 00;
  Alarm.alarmRepeat(hourTemp, minuteTemp, secondTemp, cleanPool);
  subroutineName[8] = 1;
  alarmsInSeconds[8] = hourTemp * 60 * 60 + minuteTemp * 60 + secondTemp;
  Alarm.alarmRepeat(hourTemp + 1 , minuteTemp, secondTemp, allPumpsOff);
  alarmsInSeconds[9] = (hourTemp+1) * 60 * 60 + minuteTemp * 60 + secondTemp;
  subroutineName[9] = 0;



}



/*

 *  ********************************
 *  *******************************
 *  *****************************

*/
