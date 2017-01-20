/* Main Loop
 */
void loop() 
{ 
  DateTime now = rtc.now(); // setup class for log
  timer = millis(); // used for timming
  laserCount = levelRead();  // set number of lasers to use
  for(int i = 0; i<laserCount; i++)
    {
      for(int j = 0; j<laserColumns; j++)
      {
        lastArray[i][j] = thisArray[i][j]; // put last laser results into lastArray
      }  
    } 
  if(timer - previousTime >= swpTime)
  {
    previousTime = timer;
    sweep(thisArray);                    // sweep lasers for new results
    for(int j = 0; j<laserColumns; j++)
    {
      lastSweep[j] = thisSweep[j];       // put last presence detection in lastSweep variable (this is a 1x2 array)
      thisSweep[j] = check(thisArray, j);             //check for blocked laser. returns 1 if bockage present, 0 if clear
    }

    if(thisSweep[0]+thisSweep[1] != 0)
      {
         switch(compare(thisSweep,lastSweep))  // identify the current scenario (thisSweep versus lastSweep) in both columns and store time accordingly
         {
           case 0:      // non significant scenario ( object still in counter, or repeat of initiating sweep)
              midTime = now.unixtime(); // just because... for now
              logIt = 0;
              break;
           case 1:      // object entering counter from upstream (start velocity monitoring)
              enterTime = now.unixtime();
              logIt = 0;
             break;
           case 2:     // object in counter from upstream   (stop velocity monitoring)
             entrVel = deltaX / (enterTime - now.unixtime());
             logIt = 0;
             break;
           case 3:      // object exiting counter from upstream (start velocity monitoring)
             exitTime = now.unixtime();
             logIt = 0;
             break;
           case 4:      // object has passed through counter (stop velocity monitoring and figure out if it was a fish)
             extVel = deltaX / (exitTime - now.unixtime());
             objVel = (entrVel + extVel)/2;  // average velocities
             logIt = verify(objVel); // checks object velocity against water velocity and returns a 1 or 0
             if(logIt ==1)
             {
              dir = dnStrm;
             }
             break;
           case 5:      // fish has entered from downstream
             logIt = 1;
             dir = upStrm;
             break;
         }        
         if (logIt == 1) // if the object is moving upstream or if the object has been determined to be a fish from vierify function
         {
           logTime = String(now.unixtime() - sinceUnix); // updates logTime val if previously no blockage
           recData(thisArray, logTime, dir);
         }
         else
         {
          dir = 0;
          recData(thisArray, logTime, dir);
         }
      }
  }
  if(timer - calTime >= calAt) //autocalibration every calAt ms
    {
      calTime = timer;
      autoCal();
    }
}

