/*
 * read the level sensor and return the number of lasers that should be used
 */
int levelRead() // reads the capacitance level sensor and returns number of lasers to use
{
  int result;  // intermediate variable
  int maxLevel = 1010; // maximum sensor value (fully flooded)
  int res = maxLevel/maxLasers; // value per laser
  int samples[30]; // array for averaging sensor reading
  capValue = 0; // start from zero
  
  for(int i = 0; i<30; i++) //gather 30 samples and sum them up
  {
    samples[i] = analogRead(levSnsrPin);
    capValue += samples[i];
  }
  
  result = capValue/30; // take average
  capValue = analogRead(levSnsrPin);  // for debugging
  result = result/res;  // devide by resolution (bits/laser) 
  
  return result;  // should output # of lasers to use
}
