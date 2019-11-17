void checkSwitches() {
  int sensorValue1Local = digitalRead(3);
  int sensorValue2Local =  digitalRead(4);
  actOnSwitches( sensorValue1Local, sensorValue2Local);
}

void actOnSwitches(  int sensorValue1, int sensorValue2) {
  /*
     switches have been replaced with momentary switches

     the function of this routine is

     on a detected switch, turn the pump to the alternate state ...

     if running,
      turn it off
      if a timer is running
        turn off the timer
      esle
        set a timer
     else
      turn it on
      if a timer is running
        turn off the timer
      else
        set a timer

     endif

  */

  int myValue = 0;

  String temp = " manual switch= ";
  temp += sensorValue1;
  temp += ", lastState = " ;
  temp += lastState[1];
  if (sensorValue1 == HIGH )
  { // the switch changed position
    if (!lastState[1])
    { // debounce the switch so that it doesnt read a long hold as another command
      lastState[1] = true;
      switchesClear = false;
      if (nextTime[1] != 0) { // we already have an altered state, we need to return to normal
        temp += " timer was running, resetting cycles";
        nextTime[1] = 0;
        resetCycles();
      } else {
        nextTime[1] = hour() * 60 * 60 + minute() * 60 + second() + pumpReset * 60;
        temp += " nextTime = ";
        temp +=  nextTime[1];
        temp += "pumpCycleExecuting =";
        temp += pumpCycleExecuting;

        switch (pumpCycleExecuting) {
          case 0:  // pump is off ... turn it on!
            switchesClear = true; // temporarily clear the button press flag
            pumpOne();
            switchesClear = false;
            break;
          case 1: // pump is on ... turn it off
            switchesClear = true;
            allPumpsOff();
            switchesClear = false;
            break;
          case 2: // pump is on ... turn it off
            switchesClear = true;
            allPumpsOff();
            switchesClear = false;            break;
          case 3: // pump is on ... turn it off
            switchesClear = true;
            allPumpsOff();
            switchesClear = false;           break;
          case 4: // pump is on ... turn it off
            switchesClear = true;
            allPumpsOff();
            switchesClear = false;            break;
          case 5: // pump is on ... turn it off
            allPumpsOff();
        }
      }
    }
  } else {  // reset the pump to normal function
    // set the debounce stat to off
    // don't change the pump cycles
    temp += " last state set to false";
    lastState[1] = false;
  }
  // Serial.println( temp);

  if (sensorValue2 == HIGH ) { // the switch changed position
    if (!lastState[2]) {  // debounce the switch so that it doesnt read a long hold as another command
      lastState[2] = true;
      switchesClear = false;
      if (nextTime[2] != 0) { // we already have an altered state, we need to return to normal
        nextTime[2] = 0;
        resetCycles();
      } else {
        nextTime[2] = hour() * 60 * 60 + minute() * 60 + second() + pumpReset * 60 ;
        switch (pumpCycleExecuting) {
          case 0:  // pump is off ... turn it on!
            switchesClear = true; // temporarily clear the button press flag
            cleanPool();
            switchesClear = false;
            break;
          case 1: // pump is on ... turn it off
            switchesClear = true; // temporarily clear the button press flag
            allPumpsOff();
            switchesClear = false;
            break;
          case 2: // pump is on ... turn it off
          case 3: // pump is on ... turn it off
          case 4: // pump is on ... turn it off
          case 5: // pump is on ... turn it off
            switchesClear = true; // temporarily clear the button press flag
            cleanPool();
            switchesClear = false;
            break;
        }
      }
    }
  } else {  // reset the pump to normal function
    // set the debounce stat to off
    // don't change the pump cycles
    lastState[2] = false;
  }


  if ((nextTime[1] <= hour() * 60 * 60 + minute() * 60 + second()) && (nextTime[1] > 0)) {
    //    Serial.println("=====================================================   switch 1 expired - pump should return to normal cycle");
    resetCycles();
    digitalWrite(A4, LOW); // stop switch from blinking
    nextTime[1] = 0;

  }

  if ((nextTime[2] <= hour() * 60 * 60 + minute() * 60 + second()) && (nextTime[2] > 0)) {
    resetCycles();
    digitalWrite(A3, LOW); // stop switch from blinking
    nextTime[2] = 0;
    //    Serial.println("======================================================   switch 2 expired - cleaneer should return to normal cycle ");

  }

  /*
    // this flashes the switch lites while the pump is in an interrupted state
    if (nextTime[1] > 0 ) {
      bool liteState = digitalRead(10);
      liteState = !liteState;
      digitalWrite(A4, HIGH);
     digitalWrite(6,HIGH);
    }

    if (nextTime[2] > 0) {
      bool liteState = digitalRead(9);
      liteState = !liteState;
      digitalWrite(A3, HIGH);
    }
  */
}



void resetCycles()
{
  //  int hourTemp = 0;
  //  int minuteTemp = 0;
  //  int cycleTemp = 0;
  int  lastCycle;  // removed var currentCycle,
  unsigned int lastTm, myTm, currentTm;
  // tmElements_t  currentTm, lastTm, myTm;
  String temp;
  temp = " ************ Resetting Pump Cycles - Time is:" ; temp += hour() ; temp += ":" ; temp += minute() ; temp += ":" ; temp += second();
  Serial.println (temp);
  Serial.println("resetting cycles");
  switchesClear = true;
  currentTm = hour() * 60 * 60 + minute() * 60 + second();
  lastTm   = 0;
  lastCycle = 0;

Serial.print("numAlarms:"); Serial.println(numAlarms);
  for (int i = 0; i < numAlarms; i++ ) {
    temp = "looking at alarm " ;
    temp += i;
    temp += "  alarmInSeconds = ";
    temp += alarmsInSeconds[i];
    temp += "  <= ? ";
    temp += currentTm;
    Serial.println(temp);
 
    if (alarmsInSeconds[i] <= currentTm) { // the EEPROM location has a time that is possibly the last alarm
    temp = "lastTm =  " ;
    temp += lastTm;
    Serial.println(temp);
    
      if (alarmsInSeconds[i] > lastTm) { //the current timer is closer to the time than the last time
        lastTm = myTm;
        lastCycle = subroutineName[i];
        temp = "assigning subroutine " ;
        temp += lastCycle;
        temp += " index i = ";
        temp += i;
        Serial.println(temp);
      }
    }
    //   return ();
  }
  //Serial.print("Actual Time:"); Serial.print(hour()); Serial.print("-"); Serial.print(minute()); Serial.println ("");
  //Serial.print("Alarm Time:"); Serial.print(lastTm.Hour); Serial.print("-"); Serial.print(lastTm.Minute); Serial.println ("");
  //Serial.print("lastCycle = "); Serial.println(lastCycle);
  switchesClear = true;
  switch (lastCycle) {
    case 0:
      allPumpsOff();
      break;
    case 1:
      cleanPool();
      break;
    case 2:
      pumpOne();
      break;
    case 3:
      pumpTwo();
      break;
    case 4:
      pumpThree();
      break;
    case 5:
      pumpFour();
      break;

      temp = "case :" ; temp += lastCycle ; temp += " - Time is:" ; temp += hour() ; temp += ":" ; temp += minute() ; temp += ":" ; temp += second();
      //    Serial.println(temp);
      //    Serial.println("------------------------- exiting reset ---------------------------");

  }
}
