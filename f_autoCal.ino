/*
 * calibrate the photoresistors by reading the value when they are on and when they are off then averaging that
 */
void autoCal()
{
  
  int lightArray[laserCount]; // create array for lighted values
  int darkArray[laserCount]; // create array for dark values
  int dummyVar = 0;    // something for the receiverRead to return to

  for (int j = 0; j<laserColumns; j++)
  {
    for (int i = 0; i<laserCount; i++) //shift through lasers and load resistor values into light array 
      {
        digitalWrite(laser[i],HIGH); // fire laser for "cycle" ms
        delay(fireTime);
        dummyVar = receiverRead(j); // read reciever and return 1 or 0
        lightArray[i] = photoresValue; 
        digitalWrite(laser[i],LOW);
        delay(fireTime);
        dummyVar = receiverRead(j);
        darkArray[i] = photoresValue;
      }
      int lightMax = maxValue(lightArray); // find maximum value of light array
      int darkMin = minValue(darkArray); // find max value of dark array
      xCrit[j] = (darkMin + lightMax)/2; // new threshold value is average of max dark array + min light array /2
      String alert = "Calibration complete. New xCrit for column ";
      Serial.println(alert + j + " is:" + xCrit[j] + ", Dark: " + darkMin + ", Light: " + lightMax);
  }
}
int maxValue(int arr[]) 
{
  int mxm = 0;
  for (int i=0; i,i<laserCount; i++) {
    if (arr[i]>mxm) 
      {
      mxm = arr[i];
      }
    }
  return mxm;
}

int minValue(int arr[]) 
{
  int mn = 30000;
  for (int i=0; i<laserCount; i++) 
  {
    if (arr[i]<mn) 
    {
      mn = arr[i];
    }
  }
  return mn;
 }
