/*  
 *   As of 11/17/19 this code is what is running in the pool
 *   
 *   it provides basic freeze protection and relies on a DT11 humidity sensor that is installed in the controller box
 *   it is not smart and doesnt check the temp my any other means.
 *   
 *   
 */
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "DHT.h"

#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 12 

DHT dht(DHTPIN, DHTTYPE);

//Predeclare all subroutines

void allPumpsOff();
void cleanPool();
void pumpOne();
void pumpTwo();
void pumpThree();
void pumpFour();

void overridePump1();
void overridePump2();

void checkSwitches();
void actOnSwitches(int sensorValue1, int sensorValue2);
void resetCycles();

void loadAlarms ();
void MorningAlarm();




// Delcare Constants
const float poolDeltaT = 5.0;
const float ambientDeltaT = 5.0;
const float hysterisisVal = 1.3;
const float poolTempOffset = -30.6; //86 - 118.4
const float ambientTempOffset = 18.0; //  97 - 79
const int  pumpReset = 60; // the reset time after pushing a switch minutes
const byte addresses[][6] = {"1Node", "2Node"};
const int numAlarms = 10;
const float freezePoint = 34.0;




// --------------------------------- Global Variables --------------------------
// Used to control whether this node is sending or receiving

long int ackData[8]; // to hold the two values coming from the slave
int tryTest = 0;
bool switchesClear = true;
int pumpCycleExecuting = 0;
bool lastState[3] =  {false, false, false};
unsigned int nextTime[3] = {0, 0, 0};
int lastSec = 0;
unsigned int alarmsInSeconds[numAlarms];
int subroutineName[numAlarms];
bool enableFreezeProtect = false; 

// ----------------------------- End Global Variables --------------------------




void setup ()
{
  Serial.begin(9600);
  Serial.println("Starting up");

  pinMode (3, INPUT);
  pinMode (4, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(A0,  LOW);  //  power to the heater
  digitalWrite(A1, HIGH);

  //digitalWrite(A3, LOW);  // switch light
  //digitalWrite(A4, LOW);  // switch light
  //digitalWrite(A1, LOW);  // chirp alarm


  // before you do anything else figure out the positions of the manual switches and set the Flip Switches bools accordingling




  // for debug mode
  //setTime(8, 40, 0, 9, 9, 18); // set time to Saturday 8:29:00am 4/25/18
   setTime(0,0,55,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011

  // create the alarms, to trigger at specific times

  loadAlarms();
  allPumpsOff ();
  Serial.print(hour()); Serial.print(":");
  Serial.print(minute()); Serial.print(":");
  Serial.print(second()); Serial.print(" ");
}



void loop()
{
  //  Serial.println(" ****************************** in Loop *************************");
  Alarm.delay(1000);
  checkSwitches();

  
  if (lastSec != second())
  {
    lastSec = second();
    Serial.print("+");
    if (second() == 0)
    {
      Serial.println();
      Serial.print(hour()); Serial.print(":");
      Serial.print(minute()); Serial.print(":");
      Serial.print(second()); Serial.print(" ");
        float f = dht.readTemperature(true);
        if (f < freezePoint ) {
          enableFreezeProtect = true;
          Serial.println ("Freezing condition detected");
          // if the pumps are off, we need to rerun the pump off cycle
          if(pumpCycleExecuting == 0)
            allPumpsOff ();
        }
        else
        {
          enableFreezeProtect = false;
          Serial.println ("Freezing condition not detected");
        }
  Serial.print("Temperature = ");Serial.println(f);
    }
  }
}
