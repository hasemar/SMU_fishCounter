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


