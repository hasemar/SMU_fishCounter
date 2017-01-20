/*
 * fire each laser and read the photoresistor then print what happens
 */
void sweep(int arr[][laserColumns])
{
  for(int i = 0; i<laserCount; i++)
  {
    for(int j = 0; j<laserColumns; j++)
    {
      digitalWrite(laser[i],HIGH); // fire laser for "cycle" ms
      delay(fireTime);   // need this delay to give the sensor time to detect laser  (could subtract out for velocity calc)
      feedback = receiverRead(j); // read reciever and return 1 or 0, for the jth column
      Serial.print(photoresValue);
      digitalWrite(laser[i],LOW);
      
      Serial.print(',');
      Serial.print(feedback);
      Serial.print(", [");
      Serial.print(i);
      Serial.print(',');
      Serial.print(j);
      Serial.print("] ,");
      Serial.print(timer);
      Serial.print(',');
      Serial.print(capValue);
      Serial.print(',');
      Serial.print(laserCount);
      Serial.print(',');
      Serial.println(xCrit[j]);
    
    arr[i][j] = feedback; // feeds result into each element
    } 
  }
}

