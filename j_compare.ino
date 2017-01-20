/*
 * this compares sigificant scenarios with the current scenario and returns a scenario identifier
 * this identifier will be used to determin the velocity of the object passing through the counter
 */
int compare(int tSwp[], int lSwp[])
{
  int upstrmEnt[2][laserColumns] = { {1,0}, {0,0} };  // detected an upstream enterance  (scenario 1)
  int upstrmIn[2][laserColumns] = { {1, 1}, {1,0} }; //  detected object in the counter from upstream (scenario 2)
  int upstrmEx[2][laserColumns] = { {0, 1}, {1,1} }; //  detected object exiting the counter from upstream (senario 3)
  int upstrmGn[2][laserColumns] = { {0, 0}, {0,1} }; //  object has passed through the counter (senario 4)
  int dnstrmEnt[2][laserColumns] = { {0,1}, {0,0} }; // fish entered from downstream
  int instance[2][laserColumns] = { {tSwp[0],tSwp[1]}, {lSwp[0],lSwp[1]} };  // make a matrix for the sweep instances to compare with significant scenarios
  int scenario = 0;  // scenario identifier

  // check the instance array with the significant arrays and return the identified scenario
  if(scenarioSelect(instance, upstrmEnt))
  {
    scenario = 1;
    return scenario;
  }
  else if(scenarioSelect(instance, upstrmIn))
  {
    scenario = 2;
    return scenario;
  }
  else if(scenarioSelect(instance, upstrmEx))
  {
    scenario = 3;
    return scenario;
  }
  else if(scenarioSelect(instance, upstrmGn))
  {
    scenario = 4;
    return scenario;
  }
  else if(scenarioSelect(instance, dnstrmEnt))
  {
    scenario = 5;
    return scenario;
  }
  else
  {
    scenario = 0;
    return scenario;
  }
}

// nested function
int scenarioSelect(int inst[2][laserColumns], int sigInst[2][laserColumns])  // see if the instance matrix matches a significant matrix
{
  int result = 0;
  int trigger = 0;
  for(int i = 0; i<2; i++)                    
  {
    for(int j = 0; j<laserColumns; j++)
    {
      if(inst[i][j] == sigInst[i][j])
      {
        trigger++;
      }
    }
  }
  if(trigger == 4)
  {
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}
