/*
 * read the level sensor and return the number of lasers that should be used
 */
int levelRead() // reads the capacitance level sensor and returns number of lasers to use
{
  int avgRead;  // intermediate variable
  int maxLevel = 1023; // maximum sensor value (fully flooded) might change in the field to tune sensor
  int scaledCap = 0; // mapped reading for # of lasers
  int samples[30]; // array for averaging sensor reading
  capValue = 0; // start from zero
  
  for(int i = 0; i<30; i++) //gather 30 samples and sum them up
  {
    samples[i] = analogRead(levSnsrPin);
    capValue += samples[i];
  }
  
  avgRead = capValue/30; // take average
  scaledCap = map(avgRead, 0, maxLevel, 0, maxLasers); // should return # of lasers to use durring sweep
  capValue = analogRead(levSnsrPin);  // for debugging
  
  return scaledCap;  // should output # of lasers to use
}
