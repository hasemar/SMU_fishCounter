/* record data to SD card
 *  Creates 2 log files. One is an instance report showing when a detection was logged.
 *  The other creates a matrix of 1 and 0 to be processed for image recognition.
 */
void recData(int arr[], int n, String lgTime, String initTime, int dir)
{
  File logFile;
  DateTime now = rtc.now();
  String dataString = "";
  if(n == 0) // if there wasn't a blockage before open a new file
  {
    Serial.println("Checking for existing Log file");
    if(SD.exists("LOG.TXT"))
    {
     Serial.println("Log file present. Now logging..."); 
    }
    else
    {
      Serial.println("no LOG.TXT present. Creating file...");
    }
    logFile = SD.open("LOG.TXT",FILE_WRITE);
    if(logFile) // log to SD card a time stamp of when detection occured
    {
      dataString = "object_detected: ";
      logFile.print(dataString);
      logFile.print("\t");
      logFile.print(now.year());
      logFile.print('/');
      logFile.print(now.month());
      logFile.print('/');
      logFile.print(now.day());
      logFile.print("\t");
      logFile.print(now.hour());
      logFile.print(':');
      logFile.print(now.minute());
      logFile.print(':');
      logFile.print(now.second());
      logFile.println();
      logFile.close();
      Serial.println(dataString + " log successful!");
    }
    else
    {
      Serial.println("could not make LOG.TXT entry");
      logFile.close();
    }
  }
  
  //create matrix and file
   dataString = lgTime + ".TXT";
   logFile = SD.open(dataString, FILE_WRITE);
   dataString = "";
   for(int i = 0; i<laserCount; i++) // create comma separated string of thisArray
   {
     dataString += arr[i];
     if(i < laserCount-1)
      {
       dataString += ",";
      }
   }
   if(logFile)
   {
    logFile.println(dataString);
    logFile.close();
    Serial.println("Created object matrix file!");
   }
   else
   {
      Serial.println("no object matrix file created");
      logFile.close();
   }
   logFile.close();
   Serial.print("Debug");
   Serial.print(":");
   Serial.print(dataString);
   Serial.print(":");
   Serial.println(lgTime);
}

