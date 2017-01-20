/*
 * looks at velocity argument and compares it to water velocity. If the velocity argument is close to the same as the
 * water velocity it returns a 0, otherwise its a one and will trigger a logging event
 */
int verify(float vel)
{
  wtrVel = getStrmVel();   // get the stream velocity
  int result = 0; // output
  float range = 5.0;   // use to adjust range of matching velocity to tune velocity comparison
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
  float result;  // intermediate variable for output
  int rho = 1000; // kg/m3   density of water
  int samples[30]; // array for averaging sensor reading
  pressValue = 0; // start from zero
  
  for(int i = 0; i<30; i++) //gather 30 samples and sum them up
  {
    samples[i] = analogRead(pitotSnsrPin);
    pressValue += samples[i];
  }
  
  result = pressValue/30; // take average
  pressValue = analogRead(pitotSnsrPin);  // for debugging
  result = sqrt(2*pressValue/rho);   // apply velocity equation
  
  return result;  // should return the velocity of the water based on the equation v=sqrt(2*dp/rho)
}
