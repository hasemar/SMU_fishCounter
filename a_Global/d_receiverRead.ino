/*
 * read the photoresistor analog input
 */
int receiverRead(int column) // reads the reciever and turns voltage into a 1 or 0
{
  int result;
  if (column == 0)
  {
     photoresValue = analogRead(photoResPin1)*5;
  }
  else
  {
    photoresValue = analogRead(photoResPin2)*5;
  }
 
  if (photoresValue > xCrit[column])
  {
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}
