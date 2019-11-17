void allPumpsOff ()
{
  String tempString ;

  if (switchesClear) {
    digitalWrite(5, HIGH);
    
    if (enableFreezeProtect)
      digitalWrite(6, LOW); // change back to This needs to be low on freezing conditions
    else
      digitalWrite(6, HIGH);
    
    digitalWrite(7, HIGH); // change back to HIGH once the pool isn't green
    digitalWrite(8, HIGH);
    digitalWrite(A1, HIGH);
    Serial.println(F("shutting off all pumps unless its freezing then run cycle 2"));
  }
  pumpCycleExecuting = 0;
  Serial.println(" all off");
  tempString = "switchesClear =";
  tempString += switchesClear;
  tempString += "  time:";
  tempString +=   hour() ;
  tempString += ':' ;
  tempString += minute();
  tempString += ':' ;
  tempString += second();
  tempString += "  >>>>>>>>> running All off";
  Serial.println(tempString);
}

void cleanPool()
{
  String tempString ;

  if (switchesClear) {
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(A1, LOW);
  } else
    Serial.println("switches were not clear");

  pumpCycleExecuting = 1;
  tempString = "switchesClear =";
  tempString += switchesClear;
  tempString += "  time:";
  tempString +=   hour() ;
  tempString += ':' ;
  tempString += minute();
  tempString += ':' ;
  tempString += second();
  tempString += "  >>>>>>>>> running Clean";
  Serial.println(tempString);;
}

void pumpOne() {
  String tempString ;
  if (switchesClear) {
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(A1, HIGH);
  }
  pumpCycleExecuting = 2;
  tempString = "switchesClear =";
  tempString += switchesClear;
  tempString += "  time:";
  tempString +=   hour() ;
  tempString += ':' ;
  tempString += minute();
  tempString += ':' ;
  tempString += second();
  tempString += "  >>>>>>>>> running pumpOne";
  Serial.println(tempString);
}

void pumpTwo() {
  String tempString ;
  if (switchesClear) {
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(A1, HIGH);
  }
  pumpCycleExecuting = 3;
  tempString = "switchesClear =";
  tempString += switchesClear;
  tempString += "  time:";
  tempString +=   hour() ;
  tempString += ':' ;
  tempString += minute();
  tempString += ':' ;
  tempString += second();
  tempString += "  >>>>>>>>> running pumpTwo";
  Serial.println(tempString);
}

void pumpThree() {
  String tempString ;
  if (switchesClear) {
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(A1, HIGH);
  }
  pumpCycleExecuting = 4;
  tempString = "switchesClear =";
  tempString += switchesClear;
  tempString += "  time:";
  tempString +=   hour() ;
  tempString += ':' ;
  tempString += minute();
  tempString += ':' ;
  tempString += second();
  tempString += "  >>>>>>>>> running pumpThree";
  Serial.println(tempString);

}

void pumpFour() {
  String tempString ;
  if (!switchesClear) {
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(A1, HIGH);
  }
  pumpCycleExecuting = 5;
  tempString = "switchesClear =";
  tempString += switchesClear;
  tempString += "  time:";
  tempString +=   hour() ;
  tempString += ':' ;
  tempString += minute();
  tempString += ':' ;
  tempString += second();
  tempString += "  >>>>>>>>> running pumpFour";
  Serial.println(tempString);
}

void MorningAlarm() {
  Serial.println("Alarm: - Good Morning");
}
