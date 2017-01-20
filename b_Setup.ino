/*
set up serial, RTC and sd card
*/
 
void setup() 
{
  // set all laser pins to outputs
  for (int i = 0; i < laserCount; i++)  // fill laser pin outputs start at 22 and work up by 1
    {
      laser[i] = 22+i;
    }
  for(int i = 0; i<laserCount; i++)
  {
    pinMode(laser[i],OUTPUT);
    // make sure they are all turned off so we dont fry anything
    digitalWrite(laser[i],LOW);
  }
  
  // initialize serial communications at 9600 bps:
  Serial.begin(57600);
  while(!Serial) 
  {
    ; //wait for serial port to connect.
  }
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //needs computer to do this
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("Card initialized, and ready to log data");
  autoCal();
}
