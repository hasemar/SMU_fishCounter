/*
 * read the level sensor and return the number of lasers that should be used
 */
int levelRead() // reads the capacitance level sensor and returns number of lasers to use
{
  int avgRead;  // intermediate variable
  int maxLevel = analogRead(levelSpan); // tune max capacity so all lasers function when fully submerged
  int scaledCap = 0; // mapped reading for # of lasers
  const int num = 30;   // number of samples
  int samples[num]; // array for averaging sensor reading
  capValue = 0; // start from zero
  
  for(int i = 0; i<num; i++) //gather 30 samples and sum them up
  {
    samples[i] = analogRead(levSnsrPin);
    delay(5);
    capValue += samples[i];
  }
  
  avgRead = capValue/num; // take average
  scaledCap = map(avgRead, 0, maxLevel, 0, maxLasers); // should return # of lasers to use durring sweep
  capValue = analogRead(levSnsrPin);  // for debugging
  
  return scaledCap;  // should output # of lasers to use
}
