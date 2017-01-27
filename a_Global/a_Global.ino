/*
 * This program compiles but not tested 
 * Changes: 
* Uses Arduino Mega 2560
 */

//#include <SPI.h>
#include<SD.h>
#include <Wire.h>
#include "RTClib.h"

// define all the global variables and function prototypes

RTC_PCF8523 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// phyiscal parameters and setup
const int fireTime = 2;              // time between laser firing
unsigned long timer = 0;
unsigned long previousTime = 0;
const int laserColumns = 2;  // number of vertical laser collumns
int deltaX = 26;         // (mm) distance between columns
const int upStrm = 1; // fish traveling upstream
const int dnStrm = 2; // fish traveling downstream
int dir = 0;    // direction of fish travel

//laser outputs
const int maxLasers = 8; // full number of lasers in a row of detector
int laserCount = maxLasers;       // number of lasers in array based on level sensor
int swpTime = (fireTime*laserCount)+1;           // sweep every swpTime ms
int laser[maxLasers];

// level sensor
const int levSnsrPin = A2; // capacitance level sensor analog input
const int levelSpan = A4;  // span trim pot for level sensor to set maxLevel in levelRead
int capValue = 0;    // capacitance bit value 0 to 1023

// photoresistors
const int photoResPin1 = A1;   // photoresistors analog input  for column 1
const int photoResPin2 = A0; // photoresistors analog input for column 2
int photoresValue = 0;          // photoresistor variable

// velocity
unsigned long enterTime = 0;  // time downstream column was broken
unsigned long exitTime = 0;  //  time upstream column was broken
unsigned long midTime = 0; // time just after or before columns were different
float objVel = 0.0;     // object velocity
float entrVel = 0.0;    // mm/s calculated from deltaX/time for the downstream entertime
float extVel = 0.0;     // mm/s  calculated from deltaX/time for the downstream exittime
float wtrVel = 0.0;     // water velocity  sampled from pitot tube
const int pitotSnsrPin = A3;  // analog input from pitot sensor (for water velocity)
int pressValue = 0;     // pitot sensor variable 0 to 1023

//logging
const int chipSelect = 10;   // for SD card
int thisArray[maxLasers][laserColumns];       // an array of feedback values for each photoresistor
int lastArray[maxLasers][laserColumns];       // an array of swpTime - 1 feed back values for each photoresistor
int thisSweep[laserColumns];       // presence of fish at current sweep (1 or 0)
int lastSweep[laserColumns];          // presence of fish from last sweep (1 or0)
String logTime = "";    // time something was logged
long sinceUnix = 1480550400; // seconds between unix time and 12/1/2016 00:00:00
int logIt = 0;  // tells us when to log something

//autocal
float xCrit[laserColumns] = {3000, 3000};     // light threshold
const int calAt = 30000;      // number of ms between calibration (30 sec for testing) 30min for field
unsigned long calTime = 0;  // last time calibrated

//function prototypes
int receiverRead(int column);       // reads photoresistor and returns 0 or 1 based on column number
void autoCal();                 // calibrates photoresistor threshhold and returns new threshold value
int maxValue(int arr[]);        // finds max value in an array
int minValue(int arr[]) ;       // finds min value in an array 
void sweep(int arr[][laserColumns]); // sweeps through laser array and returns array of 1's and 0's based on presence
int check(int arr[][laserColumns], int column);           // checks to see if a laser has been blocked based on column number
void recData(int thisAr[][laserColumns], String lgTime, int dir ); // creates and logs a matrix of dimension: logPeriod x lasers
int levelRead();                // read level sensor and output # of lasers to use
int compare(int tswp[], int lswp[]);   // compares enter and exit times to get velocity
int scenarioSelect(int inst[2][laserColumns], int sigInst[2][laserColumns]);  // see if the instance matrix matches a significant matrix
float getStrmVel();  // returns stream velocity
int verify(float vel);   // compares stream and object velocity and returns a 1 if it could be a fish

