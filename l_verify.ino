int verify(float vel)
{
  int result = 0; // output
  float range = 5.0;   // use to adjust range of matching velocity to tune velocity comparison
  if(vel > wtrVelocity - range && vel < wtrVelocity + range)
  {
    result = 0;
  }
  else
  {
    result = 1;
  }
  return result;
}

