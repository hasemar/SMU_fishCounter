/*
 * fire each laser and read the photoresistor then print what happens
 */
void sweep(int arr[][laserColumns])
{
  int col1 = 0;   // column 1
  int col2 = 1;   // column 2
  for(int i = 0; i<laserCount; i++)
  {
      digitalWrite(laser[i],HIGH); // fire laser for "cycle" ms
      delay(fireTime);   // delay to ensure that the laser is on before the input is read Also dictates cycle time
      arr[i][col1] = receiverRead(col1); // read reciever and return 1 or 0, for the 1st column
      Serial.print(photoresValue);
      arr[i][col2] = receiverRead(col2);  // read reciever and return 1 or 0, for the 1st column
      Serial.print(',');
      Serial.print(photoresValue);
      digitalWrite(laser[i],LOW);
      // debug stuff
      Serial.print(',');
      Serial.print(i);
      Serial.print(',');
      Serial.print(timer);
      Serial.print(',');
      Serial.print(capValue);
      Serial.print(',');
      Serial.print(laserCount);
      Serial.print(',');
      Serial.println(xCrit[col1]);
      Serial.print(',');
      Serial.println(xCrit[col2]);
  }
}

