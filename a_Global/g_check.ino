/*
 * check to see if a laser is blocked by adding up the feedback array. Returns 1 or zero (1 if there was something blocking)
 */
int check(int arr[][laserColumns], int column)
{
  int elementSum = 0;
  int result = 0; 
  for(int i = 0; i<laserCount; i++) 
  {
    elementSum += arr[i][column]; // adds up all the element values  
  }
  if(elementSum > 0)
  {
    result = 1;
  }
  return result;
}
