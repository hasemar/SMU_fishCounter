/*
 * looks at velocity argument and compares it to water velocity. If the velocity argument is close to the same as the
 * water velocity it returns a 0, otherwise its a one and will trigger a logging event
 */
int verify(float vel)
{
  wtrVel = getStrmVel();   // get the stream velocity
  int result = 0; // output
  float range = 50.0;   // use to adjust range of matching velocity to tune velocity comparison
  if(vel > wtrVel - range && vel < wtrVel + range)
  {
    result = 0;
  }
  else
  {
    result = 1;
  }
  return result;
}

/*
 * checks pitot tube sensor and averages reading, then it calculates the velocity based on pitot tube equation
 */

float getStrmVel()
{
  float avgRead;  // average sensor reading
  int rho = 1000; // kg/m3   density of water
  int maxRange =  103421; // pascals  (max sensor range)
  int scaledPress = 0;  // pascals
  int velocity = 0;     // mm/s velocity
  int num = 30; // number of samples to average over
  int samples[num]; // array for averaging sensor reading
  pressValue = 0; // start from zero
  
  for(int i = 0; i<num; i++) //gather 30 samples and sum them up
  {
    samples[i] = analogRead(pitotSnsrPin);
    pressValue += samples[i];
  }
  
  avgRead = pressValue/num; // take average
  scaledPress = map(avgRead, 0, 1032, 0, maxRange);   // scale average analog value to pascals
  
  velocity = 1000 * sqrt(2*scaledPress/rho);   // apply velocity equation (outputs mm/s)
  pressValue = analogRead(pitotSnsrPin);  // for debugging
  
  return velocity;  // should return the velocity of the water based on the equation v=sqrt(2*dp/rho)
}
